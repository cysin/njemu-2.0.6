/******************************************************************************

	driver.c

	MVS �h���C�o

******************************************************************************/

#include "mvs.h"


/* VBLANK should fire on line 248 */
#define RASTER_COUNTER_START 0x1f0	/* value assumed right after vblank */
#define RASTER_COUNTER_RELOAD 0x0f8	/* value assumed after 0x1ff */
#define RASTER_LINE_RELOAD (0x200 - RASTER_COUNTER_START)

#define SCANLINE_ADJUST 3	/* in theory should be 0, give or take an off-by-one mistake */

#define IRQ2CTRL_AUTOANIM_STOP		0x08
#define IRQ2CTRL_ENABLE				0x10
#define IRQ2CTRL_LOAD_RELATIVE		0x20
#define IRQ2CTRL_AUTOLOAD_VBLANK	0x40
#define IRQ2CTRL_AUTOLOAD_REPEAT	0x80


/******************************************************************************
	�O���[�o���ϐ�
******************************************************************************/

int neogeo_driver_type;
int neogeo_raster_enable;
u16 neogeo_ngh;
u32 neogeo_frame_counter;
u32 neogeo_frame_counter_speed;
int neogeo_selected_vectors;


/******************************************************************************
	���[�J���ϐ�
******************************************************************************/

static int current_rasterline;
static int current_rastercounter;
static int irq2start;
static int irq2control;
static u32 irq2pos_value;
static int vblank_int;
static int scanline_int;
static int scanline_read;
static int raster_enable;

static u32 frame_counter;

static int sound_code;
static int result_code;
static int pending_command;

static int trackball_select;
static int neogeo_sram_unlocked;

static u32 m68k_second_bank;
static u32 z80_bank[4];

static u16 *neogeo_cpu1_second_bank;

static u8 ALIGN_DATA neogeo_game_vectors[0x80];
static u8 *neogeo_vectors[2];

static s32 neogeo_rng = 0x2345;


/*------------------------------------------------------
	Set CPU1 second ROM bank
------------------------------------------------------*/

static void neogeo_set_cpu1_second_bank(u32 offset)
{
	if (m68k_second_bank != offset)
	{
		m68k_second_bank = offset;
		neogeo_cpu1_second_bank = (u16 *)((u32)memory_region_cpu1 + offset - 0x200000);
		C68k_Set_Fetch(&C68K, 0x200000, 0x2fffff, (u32)&memory_region_cpu1[offset]);
	}
}


/*------------------------------------------------------
	Set CPU2 ROM bank
------------------------------------------------------*/

static void neogeo_set_cpu2_bank(int bank, u32 offset)
{
	if (z80_bank[bank] != offset)
	{
		z80_bank[bank] = offset;

		switch (bank)
		{
		case 0: memcpy(&memory_region_cpu2[0x8000], &memory_region_cpu2[offset + 0x10000], 0x4000); break;
		case 1: memcpy(&memory_region_cpu2[0xc000], &memory_region_cpu2[offset + 0x10000], 0x2000); break;
		case 2: memcpy(&memory_region_cpu2[0xe000], &memory_region_cpu2[offset + 0x10000], 0x1000); break;
		case 3: memcpy(&memory_region_cpu2[0xf000], &memory_region_cpu2[offset + 0x10000], 0x0800); break;
		}
	}
}


/*------------------------------------------------------
	Inisialize driver
------------------------------------------------------*/

void neogeo_driver_init(void)
{
	memcpy(neogeo_game_vectors, memory_region_cpu1, 0x80);

	neogeo_vectors[0] = memory_region_user1;
	neogeo_vectors[1] = neogeo_game_vectors;

	m68k_second_bank = 0xffffffff;
	z80_bank[0] = 0xffffffff;
	z80_bank[1] = 0xffffffff;
	z80_bank[2] = 0xffffffff;
	z80_bank[3] = 0xffffffff;

	if (memory_length_cpu1 > 0x100000)
		neogeo_set_cpu1_second_bank(0x100000);
	else
		neogeo_set_cpu1_second_bank(0x000000);

	neogeo_set_cpu2_bank(0, 0x8000);
	neogeo_set_cpu2_bank(1, 0xc000);
	neogeo_set_cpu2_bank(2, 0xe000);
	neogeo_set_cpu2_bank(3, 0xf000);

	m68000_init();
	z80_init();
}


/*------------------------------------------------------
	Reset driver
------------------------------------------------------*/

void neogeo_driver_reset(void)
{
#ifdef ADHOC
	if (adhoc_enable)
	{
		pd4990a.seconds = 0;
		pd4990a.minutes = 0;
		pd4990a.hours   = 0;
		pd4990a.days    = 0;
		pd4990a.month   = 0;
		pd4990a.year    = 0;
		pd4990a.weekday = 0;
	}
	else
#endif
	{
		pspTime today;
		int y, m, d;

		sceRtcGetCurrentClockLocalTime(&today);

		pd4990a.seconds = ((today.seconds / 10) << 4) + (today.seconds % 10);
		pd4990a.minutes = ((today.minutes / 10) << 4) + (today.minutes % 10);
		pd4990a.hours   = ((today.hour    / 10) << 4) + (today.hour    % 10);
		pd4990a.days    = ((today.day     / 10) << 4) + (today.day     % 10);
		pd4990a.month   = today.month;
		pd4990a.year    = (((today.year % 100) / 10) << 4) + (today.year % 10);

		y = today.year;
		m = today.month;
		d = today.day;
		if (m == 1 || m == 2) { y--; m += 12; }
		pd4990a.weekday = (y + (y / 4) - (y / 100) + (y / 400) + ((13 * m + 8) / 5) + d) % 7;
	}

	memset(neogeo_ram, 0, 0x10000);

	memcpy(memory_region_cpu1, neogeo_vectors[0], 0x80);	// bios vector
	neogeo_selected_vectors = 0;

	watchdog_reset_16_w(0, 0, 0);

	irq2start = 1000;
	irq2control = 0;
	irq2pos_value = 0;
	scanline_read = 0;

	current_rasterline = 0;
	current_rastercounter = RASTER_COUNTER_START;

	vblank_int = 0;
	scanline_int = 0;

	sound_code = 0;
	result_code = 0;
	pending_command = 0;

	frame_counter = 0;
	neogeo_frame_counter = 0;
	neogeo_frame_counter_speed = 4;

	neogeo_rng = 0x2345;
	neogeo_sram_unlocked = 0;

	trackball_select = 0;

	neogeo_reset_driver_type();

#if !RELEASE
	if (!strcmp(game_name, "kog"))
	{
		memory_region_cpu1[0x1ffffc/2] = kog_jumper;
	}
#endif

	m68000_reset();
	z80_reset();
}


/*------------------------------------------------------
	Reset driver type
------------------------------------------------------*/

void neogeo_reset_driver_type(void)
{
	raster_enable = neogeo_raster_enable;

	if (neogeo_bios >= UNI_V20 && neogeo_bios <= UNI_V22)
		raster_enable = 1;

	if (raster_enable)
	{
		if (neogeo_ngh == NGH_mosyougi)
			neogeo_driver_type = BUSY;
		else
			neogeo_driver_type = RASTER;
	}
	else
	{
		if (neogeo_ngh == NGH_spinmast)
			neogeo_driver_type = RASTER;
		else
			neogeo_driver_type = NORMAL;
	}

	timer_set_update_handler();
}


/*------------------------------------------------------
	Update interrupt
------------------------------------------------------*/

static void update_interrupts(void)
{
	int level = 0;

	/* determine which interrupt is active */
	if (vblank_int)   level = 1;
	if (scanline_int) level = 2;

	/* either set or clear the appropriate lines */
	if (level)
		m68000_set_irq_line(level, ASSERT_LINE);
	else
		m68000_set_irq_line(7, CLEAR_LINE);
}


/*------------------------------------------------------
	MC68000 VBLANK interrupt (IRQ1)
------------------------------------------------------*/

void neogeo_interrupt(void)
{
	current_rasterline = 0;
	current_rastercounter = RASTER_COUNTER_START;

	/* Add a timer tick to the pd4990a */
	pd4990a_addretrace();

	if (!(irq2control & IRQ2CTRL_AUTOANIM_STOP))
	{
		/* Animation counter */
		if (frame_counter++ > neogeo_frame_counter_speed)	/* fixed animation speed */
		{
			frame_counter = 0;
			neogeo_frame_counter++;
		}
	}

	vblank_int = 1; /* vertical blank */

	update_interrupts();
}


/*------------------------------------------------------
	MC68000 scanline interrupt (IRQ2)
------------------------------------------------------*/

void neogeo_raster_interrupt(int line, int busy)
{
	int do_refresh = 0;

	current_rasterline = line;

	if (current_rasterline == RASTER_LINES) current_rasterline = 0;	/* vblank */

	if (current_rasterline < RASTER_LINE_RELOAD)
		current_rastercounter = RASTER_COUNTER_START + current_rasterline;
	else
		current_rastercounter = RASTER_COUNTER_RELOAD + current_rasterline - RASTER_LINE_RELOAD;

	if (busy)
	{
		if (scanline_read)
		{
			do_refresh = neogeo_raster_enable;
			scanline_read = 0;
		}
	}

	if (irq2control & IRQ2CTRL_ENABLE)
	{
		if (line == irq2start)
		{
			if (!busy) do_refresh = neogeo_raster_enable;

			if (irq2control & IRQ2CTRL_AUTOLOAD_REPEAT)
				irq2start += (irq2pos_value + 3) / 0x180;	/* ridhero gives 0x17d */

			scanline_int = 1;
		}
	}

	if (line == RASTER_LINES)
	{
		if (irq2control & IRQ2CTRL_AUTOLOAD_VBLANK)
			irq2start = (irq2pos_value + 3) / 0x180;	/* ridhero gives 0x17d */
		else
			irq2start = 1000;

		/* Add a timer tick to the pd4990a */
		pd4990a_addretrace();

		if (!(irq2control & IRQ2CTRL_AUTOANIM_STOP))
		{
			/* Animation counter */
			if (frame_counter++ > neogeo_frame_counter_speed)	/* fixed animation speed */
			{
				frame_counter = 0;
				neogeo_frame_counter++;
			}
		}

		vblank_int = 1; /* vertical blank */
	}

	if (do_refresh && !skip_this_frame())
	{
		if (line > RASTER_LINE_RELOAD)	/* avoid unnecessary updates after start of vblank */
			neogeo_partial_screenrefresh((current_rastercounter - 256) - 1 + SCANLINE_ADJUST);
	}

	update_interrupts();
}


/****************************************************************************
	MC68K memory access
****************************************************************************/

/*------------------------------------------------------
	Select BIOS vector (0x3a0003 / 0x3a0013)
------------------------------------------------------*/

INLINE void neogeo_select_vectors(int vector)
{
	memcpy(memory_region_cpu1, neogeo_vectors[vector], 0x80);
	neogeo_selected_vectors = vector;
	blit_set_sprite_clear_flag();
	autoframeskip_reset();
}


/*------------------------------------------------------
	Select palette RAM bank  (0x3a000f / 0x3a001f)
------------------------------------------------------*/

INLINE void neogeo_setpalbank(u32 bank)
{
	if (neogeo_palette_index != bank)
	{
		neogeo_palette_index = bank;
		neogeo_paletteram16 = neogeo_palettebank16[bank];
		video_palette = video_palettebank[bank];
	}
}


/*------------------------------------------------------
	Write data to VRAM ($3c0002)
------------------------------------------------------*/

INLINE WRITE16_HANDLER( neogeo_vidram16_data_w )
{
	COMBINE_DATA(&neogeo_vidram16[neogeo_vidram16_offset]);

	neogeo_vidram16_offset = (neogeo_vidram16_offset & 0x8000)
			| ((neogeo_vidram16_offset + neogeo_vidram16_modulo) & 0x7fff);
}


/*---------------------------------------------------------
	Read video control data ($3c0006)
---------------------------------------------------------*/

INLINE u16 neogeo_control_16_r(void)
{
	int res;

	scanline_read = 1;

	if (neogeo_driver_type == NORMAL)
	{
		current_rasterline = timer_getscanline();

		if (current_rasterline == RASTER_LINES)
			current_rasterline = 0;

		if (current_rasterline < RASTER_LINE_RELOAD)
			current_rastercounter = RASTER_COUNTER_START + current_rasterline;
		else
			current_rastercounter = RASTER_COUNTER_RELOAD + current_rasterline - RASTER_LINE_RELOAD;
	}

	res = ((current_rastercounter << 7) & 0xff80) |	/* raster counter */
		   (neogeo_frame_counter & 0x0007);			/* frame counter */

	return res;
}


/*---------------------------------------------------------
	Write video control data ($3c0006)
---------------------------------------------------------*/

INLINE void neogeo_control_16_w(u16 data)
{
	/* Auto-Anim Speed Control */
	neogeo_frame_counter_speed = (data >> 8) & 0xff;

	irq2control = data & 0xff;
}


/*------------------------------------------------------
	Write IRQ position     (0x3c0008, 0x3c000a)
------------------------------------------------------*/

INLINE void neogeo_irq2pos_16_w(u32 offset, u16 data)
{
	if (neogeo_driver_type == NORMAL) return;

	if (offset)
		irq2pos_value = (irq2pos_value & 0xffff0000) | (u32)data;
	else
		irq2pos_value = (irq2pos_value & 0x0000ffff) | ((u32)data << 16);

	if (irq2control & IRQ2CTRL_LOAD_RELATIVE)
		irq2start = current_rasterline + (irq2pos_value + 0x3b) / 0x180;
}


/*------------------------------------------------------
	Write IRQ acknowledge ($3c000c)
------------------------------------------------------*/

INLINE WRITE16_HANDLER( neogeo_irqack_16_w )
{
	if (ACCESSING_LSB)
	{
		if (data & 4) vblank_int = 0;
		if (data & 2) scanline_int = 0;
		update_interrupts();
	}
}


/****************************************************************************
	M68000 memory handlers
****************************************************************************/

/*------------------------------------------------------
	Set second ROM bank ($2ffff0 - $2fffff)
------------------------------------------------------*/

WRITE16_HANDLER( neogeo_bankswitch_16_w )
{
	if ((offset & (0x2ffff0/2)) == (0x2ffff0/2))
	{
		u32 bankaddress;

		if (memory_length_cpu1 <= 0x100000)
			return;

		data = data & 0x7;
		bankaddress = (data + 1) << 20;
		if (bankaddress >= memory_length_cpu1)
			bankaddress = 0x100000;

		neogeo_set_cpu1_second_bank(bankaddress);
	}
}


/*------------------------------------------------------
	Reset watchdog counter ($300000 - $300001)
------------------------------------------------------*/

TIMER_CALLBACK( watchdog_callback )
{
	if (Loop == LOOP_EXEC) Loop = LOOP_RESET;
}


WRITE16_HANDLER( watchdog_reset_16_w )
{
	timer_set(WATCHDOG_TIMER, 128762, 0, watchdog_callback);
}


/*------------------------------------------------------
	Read controller 2 ($340000 - $340001)
------------------------------------------------------*/

READ16_HANDLER( neogeo_controller2_16_r )
{
	if (neogeo_ngh == NGH_popbounc)
	{
		if (!trackball_select)
			return input_analog_value[1] << 8;
	}

	return neogeo_port_value[1] << 8;
}


/*------------------------------------------------------
	Read controller 3 ($380000 - $380001)
------------------------------------------------------*/

READ16_HANDLER( neogeo_controller3_16_r )
{
#ifdef ADHOC
	if (adhoc_enable)
		return neogeo_port_value[2] << 8;
	else
#endif
		return (neogeo_port_value[2] << 8) & 0x8fff;
}


/*------------------------------------------------------
	Read controller 1 and 4 ($380000 - $380001)
	                        ($380008 - $380009)
------------------------------------------------------*/

READ16_HANDLER( neogeo_controller1and4_16_r )
{
	if (offset & 0x40)
	{
		return neogeo_port_value[5];
	}
	else
	{
		switch (neogeo_ngh)
		{
		case NGH_irrmaze:
			if (trackball_select)
				return (input_analog_value[1] << 8) + neogeo_port_value[3];
			else
				return (input_analog_value[0] << 8) + neogeo_port_value[3];
			break;

		case NGH_popbounc:
			if (!trackball_select)
				return (input_analog_value[0] << 8) + neogeo_port_value[3];
			break;
		}

		return (neogeo_port_value[0] << 8) + neogeo_port_value[3];
	}
}


/*------------------------------------------------------
	Read timer ($320001)
------------------------------------------------------*/

READ16_HANDLER( neogeo_timer16_r )
{
	u16 res;
	int coinflip = pd4990a_testbit_r(0);
	int databit = pd4990a_databit_r(0);

	res = (neogeo_ngh == NGH_vliner) ? 0x3f : neogeo_port_value[4];
	res = res ^ (coinflip << 6) ^ (databit << 7);

	res |= result_code << 8;
	if (pending_command) res &= 0x7fff;

	return res;
}


/*------------------------------------------------------
	Write Z80 communication data ($320001)
------------------------------------------------------*/

TIMER_CALLBACK( neogeo_sound_write )
{
	sound_code = param;
	z80_set_irq_line(IRQ_LINE_NMI, PULSE_LINE);
}


WRITE16_HANDLER( neogeo_z80_w )
{
	pending_command = 1;
	timer_set(SOUNDLATCH_TIMER, TIME_NOW, (data >> 8) & 0xff, neogeo_sound_write);
}


/*------------------------------------------------------
	Write system control switch 1 ($380000 - $3800ff)
------------------------------------------------------*/

WRITE16_HANDLER( neogeo_syscontrol1_16_w )
{
	switch (offset & 0xff/2)
	{
	case 0x00/2: trackball_select = data & 1; break;
	case 0x50/2: pd4990a_control_16_w(0, data, mem_mask); break;
	case 0xd0/2: pd4990a_control_16_w(0, data, mem_mask); break;
	}
}


/*------------------------------------------------------
	Write system control switch 2 ($3a0000 - $3a001f)
------------------------------------------------------*/

WRITE16_HANDLER( neogeo_syscontrol2_16_w )
{
	int flag = (offset >> 3) & 1;

	switch (offset & 7)
	{
	case 1: neogeo_select_vectors(flag); break;
	case 5:
		fix_bank   = flag;
		fix_usage  = gfx_pen_usage[flag];
		fix_memory = (flag) ? memory_region_gfx2 : memory_region_gfx1;
		break;
	case 6: neogeo_sram_unlocked = flag; break;
	case 7: neogeo_setpalbank(flag); break;
	}
}


/*------------------------------------------------------
	Read VRAM register (0x3c0000 - 0x3c000f)
------------------------------------------------------*/

READ16_HANDLER( neogeo_video_16_r )
{
	if (!ACCESSING_MSB) return 0xff;

	switch (offset & 3)
	{
	case 0: return neogeo_vidram16[neogeo_vidram16_offset];
	case 1: return neogeo_vidram16[neogeo_vidram16_offset];
	case 2: return neogeo_vidram16_modulo;
	case 3: return neogeo_control_16_r();
	}
	return 0xffff;
}


/*------------------------------------------------------
	Write VRAM register (0x3c0000 - 0x3c000f)
------------------------------------------------------*/

WRITE16_HANDLER( neogeo_video_16_w )
{
	switch (offset & 7)
	{
	case 0: COMBINE_DATA(&neogeo_vidram16_offset); break;
	case 1: neogeo_vidram16_data_w(0, data, mem_mask); break;
	case 2: COMBINE_DATA(&neogeo_vidram16_modulo); break;
	case 3: neogeo_control_16_w(data); break;
	case 4: neogeo_irq2pos_16_w(0, data); break;
	case 5: neogeo_irq2pos_16_w(1, data); break;
	case 6: neogeo_irqack_16_w(0, data, mem_mask); break;
	case 7: break; /* Unknown, see control_r */
	}
}


/*------------------------------------------------------
	Write to palette RAM (0x400000 - 0x40ffff)
------------------------------------------------------*/

WRITE16_HANDLER( neogeo_paletteram16_w )
{
	u16 color;

	offset &= 0xfff;
	color = COMBINE_DATA(&neogeo_paletteram16[offset]);

	if (offset & 0x0f)
		video_palette[offset] = video_clut16[color & 0x7fff];
}


/*------------------------------------------------------
	Read from memory card ($800000 - $8007ff)
------------------------------------------------------*/

READ16_HANDLER( neogeo_memcard16_r )
{
#ifdef ADHOC
	if (adhoc_enable)
		return ~0;
	else
#endif
		return neogeo_memcard[offset & 0x7ff] | 0xff00;
}


/*------------------------------------------------------
	Write to memory card ($800000 - $8007ff)
------------------------------------------------------*/

WRITE16_HANDLER( neogeo_memcard16_w )
{
#ifdef ADHOC
	if (!adhoc_enable)
#endif
	{
		if (ACCESSING_LSB)
		{
			neogeo_memcard[offset & 0x7ff] = data & 0xff;
		}
	}
}


/*------------------------------------------------------
	Write to 64K SRAM ($d00000 - $d0ffff)
------------------------------------------------------*/

WRITE16_HANDLER( neogeo_sram16_w )
{
	if (neogeo_sram_unlocked)
	{
		COMBINE_DATA(&neogeo_sram16[offset & 0x7fff]);
	}
}


/****************************************************************************
	Z80 port access
****************************************************************************/

/*------------------------------------------------------
	Read Z80 port
------------------------------------------------------*/

u8 neogeo_z80_port_r(u16 port)
{
	switch (port & 0xff)
	{
	case 0x00:
		pending_command = 0;
		return sound_code;

	case 0x04:
		return YM2610_status_port_A_r(0);

	case 0x05:
		return YM2610_read_port_r(0);

	case 0x06:
		return YM2610_status_port_B_r(0);

	case 0x08:
		neogeo_set_cpu2_bank(3, (port & 0x7f00) << 3);
		break;

	case 0x09:
		neogeo_set_cpu2_bank(2, (port & 0x3f00) << 4);
		break;

	case 0x0a:
		neogeo_set_cpu2_bank(1, (port & 0x1f00) << 5);
		break;

	case 0x0b:
		neogeo_set_cpu2_bank(0, (port & 0x0f00) << 6);
		break;
	};

	return 0;
}


/*------------------------------------------------------
	Write Z80 port
------------------------------------------------------*/

void neogeo_z80_port_w(u16 port, u8 data)
{
	switch (port & 0xff)
	{
	case 0x04:
		YM2610_control_port_A_w(0, data);
		break;

	case 0x05:
		YM2610_data_port_A_w(0, data);
		break;

	case 0x06:
		YM2610_control_port_B_w(0, data);
		break;

	case 0x07:
		YM2610_data_port_B_w(0, data);
		break;

	case 0x0c:
		result_code = data;
		break;
	}
}


/******************************************************************************
	�T�E���hIRQ�n���h��
******************************************************************************/

void neogeo_sound_irq(int irq)
{
	z80_set_irq_line(0, irq ? ASSERT_LINE : CLEAR_LINE);
}


/******************************************************************************
	�v���e�N�V����
******************************************************************************/

/*------------------------------------------------------
  Metal Slug X

  todo: emulate, not patch!
------------------------------------------------------*/

void mslugx_install_protection(void)
{
	int i;
	u16 *mem16 = (u16 *)memory_region_cpu1;

	for (i = 0;i < (0x100000/2) - 4;i++)
	{
		if (mem16[i + 0] == 0x0243 &&
			mem16[i + 1] == 0x0001 && 	/* andi.w  #$1, D3 */
			mem16[i + 2] == 0x6600)		/* bne xxxx */
		{
			mem16[i + 2] = 0x4e71;
			mem16[i + 3] = 0x4e71;
		}
	}
	mem16[0x3bdc/2] = 0x4e71;
	mem16[0x3bde/2] = 0x4e71;
	mem16[0x3be0/2] = 0x4e71;
	mem16[0x3c0c/2] = 0x4e71;
	mem16[0x3c0e/2] = 0x4e71;
	mem16[0x3c10/2] = 0x4e71;

	mem16[0x3c36/2] = 0x4e71;
	mem16[0x3c38/2] = 0x4e71;
}


/*------------------------------------------------------
	$200000�������n���h�� (�v���e�N�V�����Ȃ�)
------------------------------------------------------*/

READ16_HANDLER( neogeo_secondbank_16_r )
{
	return neogeo_cpu1_second_bank[offset];
}


WRITE16_HANDLER( neogeo_secondbank_16_w )
{
	neogeo_bankswitch_16_w(offset, data, mem_mask);
}


/*------------------------------------------------------
	Fatal Fury 2
------------------------------------------------------*/

static u32 neogeo_prot_data;

READ16_HANDLER( fatfury2_protection_16_r )
{
	u16 res = (neogeo_prot_data >> 24) & 0xff;

	switch (offset & (0xfffff/2))
	{
	case 0x55550/2:
	case 0xffff0/2:
	case 0x00000/2:
	case 0xff000/2:
	case 0x36000/2:
	case 0x36008/2:
		return res;

	case 0x36004/2:
	case 0x3600c/2:
		return ((res & 0xf0) >> 4) | ((res & 0x0f) << 4);
	}
	return 0xff;
}

WRITE16_HANDLER( fatfury2_protection_16_w )
{
	switch (offset & (0xfffff/2))
	{
	case 0x11112/2: /* data == 0x1111; expects 0xff000000 back */
		neogeo_prot_data = 0xff000000;
		break;

	case 0x33332/2: /* data == 0x3333; expects 0x0000ffff back */
		neogeo_prot_data = 0x0000ffff;
		break;

	case 0x44442/2: /* data == 0x4444; expects 0x00ff0000 back */
		neogeo_prot_data = 0x00ff0000;
		break;

	case 0x55552/2: /* data == 0x5555; read back from 55550, ffff0, 00000, ff000 */
		neogeo_prot_data = 0xff00ff00;
		break;

	case 0x56782/2: /* data == 0x1234; read back from 36000 *or* 36004 */
		neogeo_prot_data = 0xf05a3601;
		break;

	case 0x42812/2: /* data == 0x1824; read back from 36008 *or* 3600c */
		neogeo_prot_data = 0x81422418;
		break;

	case 0x55550/2:
	case 0xffff0/2:
	case 0xff000/2:
	case 0x36000/2:
	case 0x36004/2:
	case 0x36008/2:
	case 0x3600c/2:
		neogeo_prot_data <<= 8;
		break;
	}
}


/*------------------------------------------------------
  King of Fighters 98

  The encrypted set has a rom overlay feature, checked at
  various points in the game
------------------------------------------------------*/

WRITE16_HANDLER( kof98_protection_16_w )
{
	if ((offset & (0x2fffff/2)) == (0x20aaaa/2))
	{
		/* info from razoola */
		u16 *mem16 = (u16 *)memory_region_cpu1;

		switch (data)
		{
		case 0x0090:
			mem16[0x100/2] = 0x00c2;
			mem16[0x102/2] = 0x00fd;
			break;

		case 0x00f0:
			mem16[0x100/2] = 0x4e45;
			mem16[0x102/2] = 0x4f2d;
			break;
		}
	}
	else
	{
		neogeo_bankswitch_16_w(offset, data, mem_mask);
	}
}


/*------------------------------------------------------
  SMA Protection

  thanks to Razoola
------------------------------------------------------*/

/* information about the sma random number generator provided by razoola */
/* this RNG is correct for KOF99, other games might be different */

static u16 sma_random_r(void)
{
	int old = neogeo_rng;

	int newbit = (
			(neogeo_rng >>  2) ^
			(neogeo_rng >>  3) ^
			(neogeo_rng >>  5) ^
			(neogeo_rng >>  6) ^
			(neogeo_rng >>  7) ^
			(neogeo_rng >> 11) ^
			(neogeo_rng >> 12) ^
			(neogeo_rng >> 15)) & 1;

	neogeo_rng = ((neogeo_rng << 1) | newbit) & 0xffff;

	return old;
}


READ16_HANDLER( kof99_protection_16_r )
{
	switch (offset)
	{
	case 0x2fe446/2: return 0x9a37;
	case 0x2ffff8/2: return sma_random_r();
	case 0x2ffffa/2: return sma_random_r();
	}
	return neogeo_cpu1_second_bank[offset];
}

WRITE16_HANDLER( kof99_protection_16_w )
{
	if (offset == 0x2ffff0/2)
	{
		int bankaddress;
		static int bankoffset[64] =
		{
			0x000000, 0x100000, 0x200000, 0x300000,
			0x3cc000, 0x4cc000, 0x3f2000, 0x4f2000,
			0x407800, 0x507800, 0x40d000, 0x50d000,
			0x417800, 0x517800, 0x420800, 0x520800,
			0x424800, 0x524800, 0x429000, 0x529000,
			0x42e800, 0x52e800, 0x431800, 0x531800,
			0x54d000, 0x551000, 0x567000, 0x592800,
			0x588800, 0x581800, 0x599800, 0x594800,
			0x598000,	/* rest not used? */
		};

		/* unscramble bank number */
		data =
			(((data >> 14) & 1) << 0) +
			(((data >>  6) & 1) << 1) +
			(((data >>  8) & 1) << 2) +
			(((data >> 10) & 1) << 3) +
			(((data >> 12) & 1) << 4) +
			(((data >>  5) & 1) << 5);

		bankaddress = 0x100000 + bankoffset[data];

		neogeo_set_cpu1_second_bank(bankaddress);
	}
}


READ16_HANDLER( garou_protection_16_r )
{
	switch (offset)
	{
	case 0x2fe446/2: return 0x9a37;
	case 0x2fffcc/2:
	case 0x2ffff0/2: return sma_random_r();
	}
	return neogeo_cpu1_second_bank[offset];
}

WRITE16_HANDLER( garou_protection_16_w )
{
	if (offset == 0x2fffc0/2)
	{
		/* thanks to Razoola and Mr K for the info */
		int bankaddress;
		static int bankoffset[64] =
		{
			0x000000, 0x100000, 0x200000, 0x300000, // 00
			0x280000, 0x380000, 0x2d0000, 0x3d0000, // 04
			0x2f0000, 0x3f0000, 0x400000, 0x500000, // 08
			0x420000, 0x520000, 0x440000, 0x540000, // 12
			0x498000, 0x598000, 0x4a0000, 0x5a0000, // 16
			0x4a8000, 0x5a8000, 0x4b0000, 0x5b0000, // 20
			0x4b8000, 0x5b8000, 0x4c0000, 0x5c0000, // 24
			0x4c8000, 0x5c8000, 0x4d0000, 0x5d0000, // 28
			0x458000, 0x558000, 0x460000, 0x560000, // 32
			0x468000, 0x568000, 0x470000, 0x570000, // 36
			0x478000, 0x578000, 0x480000, 0x580000, // 40
			0x488000, 0x588000, 0x490000, 0x590000, // 44
			0x5d0000, 0x5d8000, 0x5e0000, 0x5e8000, // 48
			0x5f0000, 0x5f8000, 0x600000, /* rest not used? */
		};

		/* unscramble bank number */
		data =
			(((data >>  5) & 1) << 0) +
			(((data >>  9) & 1) << 1) +
			(((data >>  7) & 1) << 2) +
			(((data >>  6) & 1) << 3) +
			(((data >> 14) & 1) << 4) +
			(((data >> 12) & 1) << 5);

		bankaddress = 0x100000 + bankoffset[data];

		neogeo_set_cpu1_second_bank(bankaddress);
	}
}

WRITE16_HANDLER( garouo_protection_16_w )
{
	if (offset == 0x2fffc0/2)
	{
		/* thanks to Razoola and Mr K for the info */
		int bankaddress;
		static int bankoffset[64] =
		{
			0x000000, 0x100000, 0x200000, 0x300000, // 00
			0x280000, 0x380000, 0x2d0000, 0x3d0000, // 04
			0x2c8000, 0x3c8000, 0x400000, 0x500000, // 08
			0x420000, 0x520000, 0x440000, 0x540000, // 12
			0x598000, 0x698000, 0x5a0000, 0x6a0000, // 16
			0x5a8000, 0x6a8000, 0x5b0000, 0x6b0000, // 20
			0x5b8000, 0x6b8000, 0x5c0000, 0x6c0000, // 24
			0x5c8000, 0x6c8000, 0x5d0000, 0x6d0000, // 28
			0x458000, 0x558000, 0x460000, 0x560000, // 32
			0x468000, 0x568000, 0x470000, 0x570000, // 36
			0x478000, 0x578000, 0x480000, 0x580000, // 40
			0x488000, 0x588000, 0x490000, 0x590000, // 44
			0x5d8000, 0x6d8000, 0x5e0000, 0x6e0000, // 48
			0x5e8000, 0x6e8000, 0x6e8000, 0x000000, // 52
			0x000000, 0x000000, 0x000000, 0x000000, // 56
			0x000000, 0x000000, 0x000000, 0x000000, // 60
		};

		/* unscramble bank number */
		data =
			(((data >>  4) & 1) << 0) +
			(((data >>  8) & 1) << 1) +
			(((data >> 14) & 1) << 2) +
			(((data >>  2) & 1) << 3) +
			(((data >> 11) & 1) << 4) +
			(((data >> 13) & 1) << 5);

		bankaddress = 0x100000 + bankoffset[data];

		neogeo_set_cpu1_second_bank(bankaddress);
	}
}


READ16_HANDLER( mslug3_protection_16_r )
{
	if (offset == 0x2fe466/2)
	{
		return 0x9a37;
	}
	return neogeo_cpu1_second_bank[offset];
}

WRITE16_HANDLER( mslug3_protection_16_w )
{
	if (offset == 0x2fffe4/2)
	{
		/* thanks to Razoola and Mr K for the info */
		int bankaddress;
		static int bankoffset[64] =
		{
			0x000000, 0x020000, 0x040000, 0x060000, // 00
			0x070000, 0x090000, 0x0b0000, 0x0d0000, // 04
			0x0e0000, 0x0f0000, 0x120000, 0x130000, // 08
			0x140000, 0x150000, 0x180000, 0x190000, // 12
			0x1a0000, 0x1b0000, 0x1e0000, 0x1f0000, // 16
			0x200000, 0x210000, 0x240000, 0x250000, // 20
			0x260000, 0x270000, 0x2a0000, 0x2b0000, // 24
			0x2c0000, 0x2d0000, 0x300000, 0x310000, // 28
			0x320000, 0x330000, 0x360000, 0x370000, // 32
			0x380000, 0x390000, 0x3c0000, 0x3d0000, // 36
			0x400000, 0x410000, 0x440000, 0x450000, // 40
			0x460000, 0x470000, 0x4a0000, 0x4b0000, // 44
			0x4c0000, /* rest not used? */
		};

		/* unscramble bank number */
		data =
			(((data >> 14) & 1) << 0) +
			(((data >> 12) & 1) << 1) +
			(((data >> 15) & 1) << 2) +
			(((data >>  6) & 1) << 3) +
			(((data >>  3) & 1) << 4) +
			(((data >>  9) & 1) << 5);

		bankaddress = 0x100000 + bankoffset[data];

		neogeo_set_cpu1_second_bank(bankaddress);
	}
}


READ16_HANDLER( kof2000_protection_16_r )
{
	switch (offset)
	{
	case 0x2fe446/2: return 0x9a37;
	case 0x2fffd8/2:
	case 0x2fffda/2: return sma_random_r();
	}
	return neogeo_cpu1_second_bank[offset];
}

WRITE16_HANDLER( kof2000_protection_16_w )
{
	if (offset == 0x2fffec/2)
	{
		/* thanks to Razoola and Mr K for the info */
		int bankaddress;
		static int bankoffset[64] =
		{
			0x000000, 0x100000, 0x200000, 0x300000, // 00
			0x3f7800, 0x4f7800, 0x3ff800, 0x4ff800, // 04
			0x407800, 0x507800, 0x40f800, 0x50f800, // 08
			0x416800, 0x516800, 0x41d800, 0x51d800, // 12
			0x424000, 0x524000, 0x523800, 0x623800, // 16
			0x526000, 0x626000, 0x528000, 0x628000, // 20
			0x52a000, 0x62a000, 0x52b800, 0x62b800, // 24
			0x52d000, 0x62d000, 0x52e800, 0x62e800, // 28
			0x618000, 0x619000, 0x61a000, 0x61a800, // 32
		};

		/* unscramble bank number */
		data =
			(((data >> 15) & 1) << 0) +
			(((data >> 14) & 1) << 1) +
			(((data >>  7) & 1) << 2) +
			(((data >>  3) & 1) << 3) +
			(((data >> 10) & 1) << 4) +
			(((data >>  5) & 1) << 5);

		bankaddress = 0x100000 + bankoffset[data];

		neogeo_set_cpu1_second_bank(bankaddress);
	}
}


/*------------------------------------------------------
  PVC Protection

  mslug5, svcchaos, kof2003
------------------------------------------------------*/

static u16 CartRAM[0x1000];

static void pvc_w8(u32 offset, u8 data)
{
	*(((u8 *)CartRAM) + offset) = data;
}

static u8 pvc_r8(u32 offset)
{
	return *(((u8 *)CartRAM) + offset);
}

static void pvc_prot1(void)
{
	u8 b1, b2;

	b1 = pvc_r8(0x1fe1);
	b2 = pvc_r8(0x1fe0);

	pvc_w8(0x1fe2, (((b2 >> 0) & 0xf) << 1) | ((b1 >> 4) & 1));
	pvc_w8(0x1fe3, (((b2 >> 4) & 0xf) << 1) | ((b1 >> 5) & 1));
	pvc_w8(0x1fe4, (((b1 >> 0) & 0xf) << 1) | ((b1 >> 6) & 1));
	pvc_w8(0x1fe5, (b1 >> 7));
}

// on writes to e8/e9/ea/eb
static void pvc_prot2(void)
{
	u8 b1, b2, b3, b4;

	b1 = pvc_r8(0x1fe9);
	b2 = pvc_r8(0x1fe8);
	b3 = pvc_r8(0x1feb);
	b4 = pvc_r8(0x1fea);

	pvc_w8(0x1fec, (b2 >> 1) | ((b1 >> 1) << 4));
	pvc_w8(0x1fed, (b4 >> 1) | ((b2 & 1) << 4) | ((b1 & 1) << 5) | ((b4 & 1) << 6) | ((b3 & 1) << 7));
}

static void pvc_write_bankswitch(void)
{
	u32 bankaddress;

	bankaddress = ((CartRAM[0xff8] >> 8) | (CartRAM[0xff9] << 8));

	*(((u8 *)CartRAM) + 0x1ff0)  = 0xa0;
	*(((u8 *)CartRAM) + 0x1ff1) &= 0xfe;
	*(((u8 *)CartRAM) + 0x1ff3) &= 0x7f;

	neogeo_set_cpu1_second_bank(bankaddress + 0x100000);
}

READ16_HANDLER( pvc_protection_16_r )
{
	if ((offset & 0x2fe000/2) == 0x2fe000/2)
	{
		return CartRAM[offset & 0xfff];
	}
	return neogeo_cpu1_second_bank[offset];
}

WRITE16_HANDLER( pvc_protection_16_w )
{
	if ((offset & 0x2fe000/2) == 0x2fe000/2)
	{
		offset &= 0xfff;

		COMBINE_DATA(&CartRAM[offset]);

		if (offset == 0xff0)
			pvc_prot1();
		else if (offset >= 0xff4 && offset <= 0xff5)
			pvc_prot2();
		else if (offset >= 0xff8)
			pvc_write_bankswitch();
	}
}


/*------------------------------------------------------
	Brezzasoft

	���ۂɂ̓v���e�N�g�ł͂Ȃ����v���e�N�g�Ƃ��ď���
------------------------------------------------------*/

u16 *brza_sram = NULL;

READ16_HANDLER( brza_sram_16_r )
{
	if ((offset & 0x2f0000/2) == 0x200000/2)
		return brza_sram[offset & 0xfff];
	return 0xffff;
}

WRITE16_HANDLER( brza_sram_16_w )
{
	if ((offset & 0x2f0000/2) == 0x200000/2)
		COMBINE_DATA(&brza_sram[offset & 0xfff]);
}

READ16_HANDLER( vliner_16_r )
{
	switch (offset & 0x2f0000/2)
	{
	case 0x200000/2: return brza_sram[offset & 0xfff];
	case 0x280000/2: return neogeo_port_value[4];
	case 0x2c0000/2: return 0x0003;
	}
	return 0xffff;
}


/*------------------------------------------------------
	bootleg set
------------------------------------------------------*/

#if !RELEASE

int kog_jumper;

WRITE16_HANDLER( kof10th_protection_16_w )
{
	if (offset < 0x240000/2)
	{
		offset -= 0x200000/2;

		if (!CartRAM[0xffe])
		{
			u16 *prom = (u16 *)memory_region_cpu1;
			COMBINE_DATA(&prom[(0xe0000/2) + (offset & 0xffff)]);
		}
		else
		{
			u8 *srom1 = memory_region_user2;
			u8 *srom2 = memory_region_gfx2;
			u32 tile = offset & ~31;

			srom1[offset] = BITSWAP8(data,7,6,0,4,3,2,1,5);
			memcpy(&srom2[tile], &srom1[tile], 32);
			neogeo_decode_fix(&srom2[tile], 32, &gfx_pen_usage[1][tile >> 5]);
			blit_set_fix_clear_flag();
		}
	}
	else
	{
		offset -= 0x240000/2;

		if (offset >= 0x5f000)
		{
			if (offset == 0x5fff8)
			{
				u32 bankaddress = 0x100000 + ((data & 7) << 20);

				if (bankaddress >= 0x700000)
					bankaddress = 0x100000;

				neogeo_set_cpu1_second_bank(bankaddress);
			}
			else if (offset == 0x5fffc && CartRAM[0xffc] != data)
			{
				u8 *src = memory_region_cpu1;

				memcpy(src + 0x10000, src + ((data & 1) ? 0x810000 : 0x710000), 0xcffff);
			}
			COMBINE_DATA(&CartRAM[offset & 0xfff]);
		}
	}
}

WRITE16_HANDLER( cthd2003_protection_16_w )
{
	if (offset >= 0x2ffff0/2)
	{
		u8 cthd2003_banks[8] = { 1,0,1,0,1,0,3,2 };

		offset -= 0x2ffff0/2;

		if (offset == 0)
		{
			neogeo_set_cpu1_second_bank(0x100000 + (cthd2003_banks[data & 7] << 20));
		}
	}
}

READ16_HANDLER( ms5plus_protection_16_r )
{
	if (offset >= 0x2ffff0/2)
	{
		return 0xa0;
	}
	return neogeo_cpu1_second_bank[offset];
}

WRITE16_HANDLER( ms5plus_protection_16_w )
{
	if (offset == 0x2ffff0/2 && data == 0xa0)
	{
		neogeo_set_cpu1_second_bank(0xa0);
	}
	else if (offset == 0x2ffff4/2)
	{
		data >>= 4;
		neogeo_set_cpu1_second_bank(data << 20);
	}
}

WRITE16_HANDLER( kf2k3bl_protection_16_w)
{
	if (offset >= 0x2fe000/2)
	{
		offset -= 0x2fe000/2;

		data = COMBINE_DATA(&CartRAM[offset]);

		if (offset == 0x1ff0/2 || offset == 0x1ff2/2)
		{
			u8 *cr = (u8 *)CartRAM;
			u32 address = (cr[0x1ff3] << 16) | (cr[0x1ff2] << 8) | cr[0x1ff1];
			u8 prt = cr[0x1ff2];

			cr[0x1ff0] =  0xa0;
			cr[0x1ff1] &= 0xfe;
			cr[0x1ff3] &= 0x7f;
			neogeo_set_cpu1_second_bank(address + 0x100000);

			memory_region_cpu1[0x58196] = prt;
		}
	}
}

WRITE16_HANDLER( kf2k3pl_protection_16_w)
{
	if (offset >= 0x2fe000/2)
	{
		offset -= 0x2fe000/2;

		data = COMBINE_DATA(&CartRAM[offset]);

		if (offset == 0x1ff0/2 || offset == 0x1ff2/2)
		{
			u8 *cr = (u8 *)CartRAM;
			u32 address = (cr[0x1ff3] << 16) | (cr[0x1ff2] << 8) | cr[0x1ff0];
			u8 prt = cr[0x1ff2];

			cr[0x1ff0] &= 0xfe;
			cr[0x1ff3] &= 0x7f;
			neogeo_set_cpu1_second_bank(address + 0x100000);

			memory_region_cpu1[0x58196] = prt;
		}
	}
}

#endif /* RELEASE */


/******************************************************************************
	�Z�[�u/���[�h �X�e�[�g
******************************************************************************/

#ifdef SAVE_STATE

STATE_SAVE( driver )
{
	state_save_long(&neogeo_driver_type, 1);
	state_save_long(&irq2start, 1);
	state_save_long(&irq2control, 1);
	state_save_long(&irq2pos_value, 1);
	state_save_long(&vblank_int, 1);
	state_save_long(&scanline_int, 1);
	state_save_long(&scanline_read, 1);
	state_save_long(&frame_counter, 1);
	state_save_long(&sound_code, 1);
	state_save_long(&result_code, 1);
	state_save_long(&pending_command, 1);
	state_save_long(&neogeo_frame_counter, 1);
	state_save_long(&neogeo_frame_counter_speed, 1);
	state_save_long(&raster_enable, 1);

	state_save_long(&m68k_second_bank, 1);
	state_save_long(z80_bank, 4);
	state_save_long(&trackball_select, 1);
	state_save_long(&neogeo_sram_unlocked, 1);
	state_save_long(&neogeo_selected_vectors, 1);

	state_save_long(&neogeo_rng, 1);
	state_save_long(&neogeo_prot_data, 1);
	state_save_word(&CartRAM, 0x1000);
}

STATE_LOAD( driver )
{
	u32 _m68k_second_bank;
	u32 _z80_bank[4];

	state_load_long(&neogeo_driver_type, 1);
	state_load_long(&irq2start, 1);
	state_load_long(&irq2control, 1);
	state_load_long(&irq2pos_value, 1);
	state_load_long(&vblank_int, 1);
	state_load_long(&scanline_int, 1);
	state_load_long(&scanline_read, 1);
	state_load_long(&frame_counter, 1);
	state_load_long(&sound_code, 1);
	state_load_long(&result_code, 1);
	state_load_long(&pending_command, 1);
	state_load_long(&neogeo_frame_counter, 1);
	state_load_long(&neogeo_frame_counter_speed, 1);
	state_load_long(&raster_enable, 1);

	state_load_long(&_m68k_second_bank, 1);
	state_load_long(_z80_bank, 4);
	state_load_long(&trackball_select, 1);
	state_load_long(&neogeo_sram_unlocked, 1);
	state_load_long(&neogeo_selected_vectors, 1);

	state_load_long(&neogeo_rng, 1);
	state_load_long(&neogeo_prot_data, 1);
	state_load_word(&CartRAM, 0x1000);

	current_rasterline = 0;
	current_rastercounter = RASTER_COUNTER_START;

	neogeo_set_cpu1_second_bank(_m68k_second_bank);
	neogeo_set_cpu2_bank(0, _z80_bank[0]);
	neogeo_set_cpu2_bank(1, _z80_bank[1]);
	neogeo_set_cpu2_bank(2, _z80_bank[2]);
	neogeo_set_cpu2_bank(3, _z80_bank[3]);
	neogeo_select_vectors(neogeo_selected_vectors);
}

#endif /* STATE_SAVE */