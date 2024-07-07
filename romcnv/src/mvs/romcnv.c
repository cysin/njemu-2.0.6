/*****************************************************************************

	romcnv.c

	ROM converter for MVSPSP

******************************************************************************/

#include "romcnv.h"

#define MAX_GAMES		512

#define TILE_BLANK		0x00
#define TILE_NOT_BLANK	0x02
#define TILE_OPAQUE		0x01

#define MAX_GFX2ROM		4
#define MAX_GFX3ROM		16
#define MAX_SND1ROM		8

enum
{
	REGION_CPU1 = 0,
	REGION_CPU2,
	REGION_GFX1,
	REGION_GFX2,
	REGION_GFX3,
	REGION_SOUND1,
	REGION_SOUND2,
	REGION_USER1,
	REGION_SKIP
};

enum
{
	TILE_FIX = 0,
	TILE_SPR,
	TILE_TYPE_MAX
};


/******************************************************************************
	グローバル変数
******************************************************************************/

u8 *memory_region_gfx2;
u8 *memory_region_gfx3;
u8 *memory_region_sound1;

u32 memory_length_gfx2;
u32 memory_length_gfx3;
u32 memory_length_sound1;


/******************************************************************************
	ローカル変数
******************************************************************************/

static u32 gfx_total_elements[TILE_TYPE_MAX];
static u8  *gfx_pen_usage[TILE_TYPE_MAX];

static int disable_sound;
static int machine_driver_type;
static int machine_init_type;
static int machine_input_type;
static int machine_screen_type;

static struct rom_t gfx2rom[MAX_GFX2ROM];
static struct rom_t gfx3rom[MAX_GFX3ROM];
static struct rom_t snd1rom[MAX_SND1ROM];

static int num_gfx2rom;
static int num_gfx3rom;
static int num_snd1rom;

static int encrypt_gfx2;
static int encrypt_gfx3;
static int encrypt_snd1;

static char game_names[MAX_GAMES][16];


/******************************************************************************
	MVS用関数
******************************************************************************/

static void neogeo_decode_spr(u8 *mem, u32 length, u8 *usage)
{
	u32 i;

	for (i = 0; i < gfx_total_elements[TILE_SPR]; i++)
	{
		u8 swap[128], *gfxdata;
		u32 x, y, pen, opaque = 0;

		gfxdata = &mem[128 * i];

		memcpy(swap, gfxdata, 128);

		for (y = 0; y < 16; y++)
		{
			u32 dw, data;

			dw = 0;
			for (x = 0; x < 8; x++)
			{
				pen  = ((swap[64 + 4*y + 3] >> x) & 1) << 3;
				pen |= ((swap[64 + 4*y + 1] >> x) & 1) << 2;
				pen |= ((swap[64 + 4*y + 2] >> x) & 1) << 1;
				pen |= ((swap[64 + 4*y + 0] >> x) & 1) << 0;
				opaque += (pen & 0x0f) != 0;
				dw |= pen << 4*x;
			}

			data = ((dw & 0x0000000f) >>  0) | ((dw & 0x000000f0) <<  4)
				 | ((dw & 0x00000f00) <<  8) | ((dw & 0x0000f000) << 12)
				 | ((dw & 0x000f0000) >> 12) | ((dw & 0x00f00000) >>  8)
				 | ((dw & 0x0f000000) >>  4) | ((dw & 0xf0000000) >>  0);

			*(gfxdata++) = data >>  0;
			*(gfxdata++) = data >>  8;
			*(gfxdata++) = data >> 16;
			*(gfxdata++) = data >> 24;

			dw = 0;
			for (x = 0;x < 8;x++)
			{
				pen  = ((swap[4*y + 3] >> x) & 1) << 3;
				pen |= ((swap[4*y + 1] >> x) & 1) << 2;
				pen |= ((swap[4*y + 2] >> x) & 1) << 1;
				pen |= ((swap[4*y + 0] >> x) & 1) << 0;
				opaque += (pen & 0x0f) != 0;
				dw |= pen << 4*x;
			}

			data = ((dw & 0x0000000f) >>  0) | ((dw & 0x000000f0) <<  4)
				 | ((dw & 0x00000f00) <<  8) | ((dw & 0x0000f000) << 12)
				 | ((dw & 0x000f0000) >> 12) | ((dw & 0x00f00000) >>  8)
				 | ((dw & 0x0f000000) >>  4) | ((dw & 0xf0000000) >>  0);

			*(gfxdata++) = data >>  0;
			*(gfxdata++) = data >>  8;
			*(gfxdata++) = data >> 16;
			*(gfxdata++) = data >> 24;
		}

		if (opaque)
			*usage = (opaque == 256) ? TILE_OPAQUE : TILE_NOT_BLANK;
		else
			*usage = TILE_BLANK;
		usage++;
	}
}


static int load_rom_gfx2(void)
{
	if (encrypt_gfx2)
	{
		int i;
		char fname[32], *parent;

		gfx_total_elements[TILE_FIX] = memory_length_gfx2 / 32;

		if ((memory_region_gfx2 = calloc(1, memory_length_gfx2)) == NULL)
		{
			error_memory("REGION_GFX2");
			return 0;
		}
		if ((gfx_pen_usage[TILE_FIX] = calloc(1, gfx_total_elements[TILE_FIX])) == NULL)
		{
			error_memory("PEN_USAGE_GFX2");
			return 0;
		}

		parent = strlen(parent_name) ? parent_name : NULL;

		for (i = 0; i < num_gfx2rom; )
		{
			if (file_open(game_name, parent, gfx2rom[i].crc, fname) == -1)
			{
				error_rom("GFX2");
				return 0;
			}

			printf("Loading \"%s\"\n", fname);

			i = rom_load(gfx2rom, memory_region_gfx2, i, num_gfx2rom);

			file_close();
		}
	}

	return 1;
}


static int load_rom_gfx3(void)
{
	int i;
	char fname[32], *parent;

	gfx_total_elements[TILE_SPR] = memory_length_gfx3 / 128;

	if ((memory_region_gfx3 = calloc(1, memory_length_gfx3)) == NULL)
	{
		error_memory("REGION_GFX3");
		return 0;
	}
	if ((gfx_pen_usage[TILE_SPR] = calloc(1, gfx_total_elements[TILE_SPR])) == NULL)
	{
		error_memory("PEN_USAGE_GFX3");
		return 0;
	}

	parent = strlen(parent_name) ? parent_name : NULL;

	for (i = 0; i < num_gfx3rom; )
	{
		if (file_open(game_name, parent, gfx3rom[i].crc, fname) == -1)
		{
			error_rom("GFX3");
			return 0;
		}

		printf("Loading \"%s\"\n", fname);

		i = rom_load(gfx3rom, memory_region_gfx3, i, num_gfx3rom);

		file_close();
	}

	return 1;
}


static int load_rom_sound1(void)
{
	int i;
	char fname[32], *parent;

	if ((memory_region_sound1 = calloc(1, memory_length_sound1)) == NULL)
	{
		error_memory("REGION_SOUND1");
		return 0;
	}

	parent = strlen(parent_name) ? parent_name : NULL;

	for (i = 0; i < num_snd1rom; )
	{
		if (file_open(game_name, parent, snd1rom[i].crc, fname) == -1)
		{
			error_rom("SOUND1");
			return 0;
		}

		printf("Loading \"%s\"\n", fname);

		i = rom_load(snd1rom, memory_region_sound1, i, num_snd1rom);

		file_close();
	}

	return 1;
}


static int build_game_list(void)
{
	FILE *fp;
	char path[MAX_PATH];
	char buf[256];
	int num_games = 0;

	sprintf(path, "%srominfo.mvs", launchDir);

	if ((fp = fopen(path, "r")) != NULL)
	{
		while (fgets(buf, 255, fp))
		{
			if (buf[0] == '/' && buf[1] == '/')
				continue;

			if (buf[0] != '\t')
			{
				if (str_cmp(buf, "FILENAME(") == 0)
				{
					char *name;

					strtok(buf, " ");
					name = strtok(NULL, " ,");

					strcpy(game_names[num_games++], name);
				}
			}
		}
		fclose(fp);
		return num_games;
	}
	return 0;
}


static int load_rom_info(const char *game_name)
{
	FILE *fp;
	char path[MAX_PATH];
	char buf[256];
	int rom_start = 0;
	int region = 0;

	num_gfx2rom = 0;
	num_gfx3rom = 0;
	num_snd1rom = 0;

	machine_driver_type = 0;
	machine_input_type  = 0;
	machine_init_type   = 0;
	machine_screen_type = 0;

	encrypt_gfx2 = 0;
	encrypt_gfx3 = 0;
	encrypt_snd1 = 0;

	disable_sound = 0;

	sprintf(path, "%srominfo.mvs", launchDir);

	if ((fp = fopen(path, "r")) != NULL)
	{
		while (fgets(buf, 255, fp))
		{
			if (buf[0] == '/' && buf[1] == '/')
				continue;

			if (buf[0] != '\t')
			{
				if (buf[0] == '\r' || buf[0] == '\n')
				{
					// 改行
					continue;
				}
				else if (str_cmp(buf, "FILENAME(") == 0)
				{
					char *name, *parent;
					char *machine, *input, *init, *rotate;

					strtok(buf, " ");
					name    = strtok(NULL, " ,");
					parent  = strtok(NULL, " ,");
					machine = strtok(NULL, " ,");
					input   = strtok(NULL, " ,");
					init    = strtok(NULL, " ,");
					rotate  = strtok(NULL, " ");

					if (strcasecmp(name, game_name) == 0)
					{
						if (str_cmp(parent, "neogeo") == 0)
						{
							parent_name[0] = '\0';
						}
						else if (str_cmp(parent, "pcb") == 0)
						{
							parent_name[0] = '\0';
						}
						else
						{
							strcpy(parent_name, parent);
						}

						sscanf(machine, "%d", &machine_driver_type);
						sscanf(input, "%d", &machine_input_type);
						sscanf(init, "%d", &machine_init_type);
						sscanf(rotate, "%d", &machine_screen_type);
						rom_start = 1;
					}
				}
				else if (rom_start && str_cmp(buf, "END") == 0)
				{
					fclose(fp);
					return 0;
				}
			}
			else if (rom_start)
			{
				if (str_cmp(&buf[1], "REGION(") == 0)
				{
					char *size, *type, *flag;
					int encrypted = 0;

					strtok(&buf[1], " ");
					size = strtok(NULL, " ,");
					type = strtok(NULL, " ,");
					flag = strtok(NULL, " ");

					if (strstr(flag, "SOUND_DISABLE")) disable_sound = 1;
					if (strstr(flag, "ENCRYPTED")) encrypted = 1;

					if (strcmp(type, "GFX2") == 0)
					{
						sscanf(size, "%x", &memory_length_gfx2);
						encrypt_gfx2 = encrypted;
						region = REGION_GFX2;
					}
					else if (strcmp(type, "GFX3") == 0)
					{
						sscanf(size, "%x", &memory_length_gfx3);
						encrypt_gfx3 = encrypted;
						region = REGION_GFX3;
					}
					else if (strcmp(type, "SOUND1") == 0)
					{
						sscanf(size, "%x", &memory_length_sound1);
						encrypt_snd1 = encrypted;
						region = REGION_SOUND1;
					}
					else
					{
						region = REGION_SKIP;
					}
				}
				else if (str_cmp(&buf[1], "ROM(") == 0)
				{
					char *type, *offset, *length, *crc;

					strtok(&buf[1], " ");
					type   = strtok(NULL, " ,");
					offset = strtok(NULL, " ,");
					length = strtok(NULL, " ,");
					crc    = strtok(NULL, " ");

					switch (region)
					{
					case REGION_GFX2:
						sscanf(type, "%x", &gfx2rom[num_gfx2rom].type);
						sscanf(offset, "%x", &gfx2rom[num_gfx2rom].offset);
						sscanf(length, "%x", &gfx2rom[num_gfx2rom].length);
						sscanf(crc, "%x", &gfx2rom[num_gfx2rom].crc);
						gfx2rom[num_gfx2rom].group = 0;
						gfx2rom[num_gfx2rom].skip = 0;
						num_gfx2rom++;
						break;

					case REGION_GFX3:
						sscanf(type, "%x", &gfx3rom[num_gfx3rom].type);
						sscanf(offset, "%x", &gfx3rom[num_gfx3rom].offset);
						sscanf(length, "%x", &gfx3rom[num_gfx3rom].length);
						sscanf(crc, "%x", &gfx3rom[num_gfx3rom].crc);
						gfx3rom[num_gfx3rom].group = 0;
						gfx3rom[num_gfx3rom].skip = 0;
						num_gfx3rom++;
						break;

					case REGION_SOUND1:
						sscanf(type, "%x", &snd1rom[num_snd1rom].type);
						sscanf(offset, "%x", &snd1rom[num_snd1rom].offset);
						sscanf(length, "%x", &snd1rom[num_snd1rom].length);
						sscanf(crc, "%x", &snd1rom[num_snd1rom].crc);
						snd1rom[num_snd1rom].group = 0;
						snd1rom[num_snd1rom].skip = 0;
						num_snd1rom++;
						break;
					}
				}
				else if (str_cmp(&buf[1], "ROMX(") == 0)
				{
					char *type, *offset, *length, *crc;
					char *group, *skip;

					strtok(&buf[1], " ");
					type   = strtok(NULL, " ,");
					offset = strtok(NULL, " ,");
					length = strtok(NULL, " ,");
					crc    = strtok(NULL, " ,");
					group  = strtok(NULL, " ,");
					skip   = strtok(NULL, " ");

					switch (region)
					{
					case REGION_GFX3:
						sscanf(type, "%x", &gfx3rom[num_gfx3rom].type);
						sscanf(offset, "%x", &gfx3rom[num_gfx3rom].offset);
						sscanf(length, "%x", &gfx3rom[num_gfx3rom].length);
						sscanf(crc, "%x", &gfx3rom[num_gfx3rom].crc);
						sscanf(group, "%x", &gfx3rom[num_gfx3rom].group);
						sscanf(skip, "%x", &gfx3rom[num_gfx3rom].skip);
						num_gfx3rom++;
						break;

					case REGION_SOUND1:
						sscanf(type, "%x", &snd1rom[num_snd1rom].type);
						sscanf(offset, "%x", &snd1rom[num_snd1rom].offset);
						sscanf(length, "%x", &snd1rom[num_snd1rom].length);
						sscanf(crc, "%x", &snd1rom[num_snd1rom].crc);
						sscanf(group, "%x", &snd1rom[num_snd1rom].group);
						sscanf(skip, "%x", &snd1rom[num_snd1rom].skip);
						num_snd1rom++;
						break;
					}
				}
			}
		}
		fclose(fp);
		return 2;
	}
	return 3;
}


void free_memory(void)
{
	if (memory_region_gfx2)      free(memory_region_gfx2);
	if (memory_region_gfx3)      free(memory_region_gfx3);
	if (memory_region_sound1)    free(memory_region_sound1);
	if (gfx_pen_usage[TILE_SPR]) free(gfx_pen_usage[TILE_SPR]);
	if (gfx_pen_usage[TILE_FIX]) free(gfx_pen_usage[TILE_FIX]);
}


static int convert_rom(char *game_name)
{
	int i, res;

	printf("Checking ROM file... (%s)\n", game_name);

	memory_region_gfx2   = NULL;
	memory_region_gfx3   = NULL;
	memory_region_sound1 = NULL;

	memory_length_gfx2   = 0;
	memory_length_gfx3   = 0;
	memory_length_sound1 = 0;

	gfx_pen_usage[TILE_FIX] = NULL;
	gfx_pen_usage[TILE_SPR] = NULL;

	if ((res = load_rom_info(game_name)) != 0)
	{
		switch (res)
		{
		case 1: printf("ERROR: This game is not supported.\n"); break;
		case 2: printf("ERROR: ROM not found. (zip file name incorrect)\n"); break;
		case 3: printf("ERROR: rominfo.mvs not found.\n"); break;
		}
		return 0;
	}

	if (strlen(parent_name))
		printf("Clone set (parent: %s)\n", parent_name);

	if (encrypt_snd1 || disable_sound)
	{
		if (load_rom_sound1())
		{
			if (encrypt_snd1)
			{
				switch (machine_init_type)
				{
				case INIT_kof2002:	neo_pcm2_swap(0);		break;
				case INIT_mslug5:	neo_pcm2_swap(2);		break;
				case INIT_svchaosa:	neo_pcm2_swap(3);		break;
				case INIT_samsho5:	neo_pcm2_swap(4);		break;
				case INIT_kof2003:	neo_pcm2_swap(5);		break;
				case INIT_samsh5sp:	neo_pcm2_swap(6);		break;
				case INIT_pnyaa:	neo_pcm2_snk_1999(4);	break;
				case INIT_mslug4:	neo_pcm2_snk_1999(8);	break;
				case INIT_rotd:		neo_pcm2_snk_1999(16);	break;
				case INIT_matrim:	neo_pcm2_swap(1);		break;

				case INIT_ms5pcb:	neo_pcm2_swap(2);		break;
				case INIT_svcpcb:	neo_pcm2_swap(3);		break;
				case INIT_kf2k3pcb:	neo_pcm2_swap(5);		break;

				case INIT_kf2k2pls:	neo_pcm2_swap(0);		break;
				case INIT_kf2k2mp:	neo_pcm2_swap(0);		break;
				case INIT_kf2k2mp2:	neo_pcm2_swap(0);		break;
				case INIT_ms5plus:	neo_pcm2_swap(2);		break;
				case INIT_samsho5b:	neo_pcm2_swap(4);		break;
				case INIT_lans2004:	lans2004_vx_decrypt();	break;

				default: goto error;
				}
			}
		}
		else
		{
			goto error;
		}
	}

	if (encrypt_gfx2 || encrypt_gfx3)
	{
		if (load_rom_gfx2() && load_rom_gfx3())
		{
			switch (machine_init_type)
			{
			case INIT_kof99:	kof99_neogeo_gfx_decrypt(0x00);		break;
			case INIT_kof99n:	kof99_neogeo_gfx_decrypt(0x00);		break;
			case INIT_garou:	kof99_neogeo_gfx_decrypt(0x06);		break;
			case INIT_garouo:	kof99_neogeo_gfx_decrypt(0x06);		break;
			case INIT_mslug3:	kof99_neogeo_gfx_decrypt(0xad);		break;
			case INIT_mslug3n:	kof99_neogeo_gfx_decrypt(0xad);		break;
			case INIT_kof2000:	kof2000_neogeo_gfx_decrypt(0x00);	break;
			case INIT_kof2000n:	kof2000_neogeo_gfx_decrypt(0x00);	break;
			case INIT_zupapa:	kof99_neogeo_gfx_decrypt(0xbd);		break;
			case INIT_sengoku3:	kof99_neogeo_gfx_decrypt(0xfe);		break;
			case INIT_kof2001:	kof2000_neogeo_gfx_decrypt(0x1e);	break;
			case INIT_kof2002:	kof2000_neogeo_gfx_decrypt(0xec);	break;
			case INIT_mslug5:	kof2000_neogeo_gfx_decrypt(0x19);	break;
			case INIT_svchaosa:	kof2000_neogeo_gfx_decrypt(0x57);	break;
			case INIT_samsho5:	kof2000_neogeo_gfx_decrypt(0x0f);	break;
			case INIT_kof2003:	kof2000_neogeo_gfx_decrypt(0x9d);	break;
			case INIT_samsh5sp:	kof2000_neogeo_gfx_decrypt(0x0d);	break;
			case INIT_nitd:		kof99_neogeo_gfx_decrypt(0xff);		break;
			case INIT_s1945p:	kof99_neogeo_gfx_decrypt(0x05);		break;
			case INIT_pnyaa:	kof2000_neogeo_gfx_decrypt(0x2e);	break;
			case INIT_preisle2:	kof99_neogeo_gfx_decrypt(0x9f);		break;
			case INIT_ganryu:	kof99_neogeo_gfx_decrypt(0x07);		break;
			case INIT_bangbead:	kof99_neogeo_gfx_decrypt(0xf8);		break;
			case INIT_mslug4:	kof2000_neogeo_gfx_decrypt(0x31);	break;
			case INIT_rotd:		kof2000_neogeo_gfx_decrypt(0x3f);	break;
			case INIT_matrim:	kof2000_neogeo_gfx_decrypt(0x6a);	break;
			case INIT_jockeygp:	kof2000_neogeo_gfx_decrypt(0xac);	break;

			// Jamma PCB

			case INIT_ms5pcb:
				svcpcb_gfx_decrypt();
				kof2000_neogeo_gfx_decrypt(0x19);
				svcpcb_s1data_decrypt();
				break;

			case INIT_svcpcb:
				svcpcb_gfx_decrypt();
				kof2000_neogeo_gfx_decrypt(0x57);
				svcpcb_s1data_decrypt();
				break;

			case INIT_kf2k3pcb:
				kf2k3pcb_gfx_decrypt();
				kof2000_neogeo_gfx_decrypt(0x9d);
				kf2k3pcb_decrypt_s1data();
				break;

			// bootleg

			case INIT_garoubl:
				neogeo_bootleg_sx_decrypt(2);
				neogeo_bootleg_cx_decrypt();
				break;

			case INIT_kf2k2pls:
				cmc50_neogeo_gfx_decrypt(0xec);
				break;

			case INIT_kf2k2mp:
				neogeo_bootleg_sx_decrypt(2);
				cmc50_neogeo_gfx_decrypt(0xec);
				break;

			case INIT_kf2k2mp2:
				neogeo_bootleg_sx_decrypt(1);
				cmc50_neogeo_gfx_decrypt(0xec);
				break;

			case INIT_ms5plus:
				neogeo_bootleg_sx_decrypt(1);
				cmc50_neogeo_gfx_decrypt(0x19);
				break;

			case INIT_svcboot:
				svcboot_cx_decrypt();
				break;

			case INIT_svcplus:
				neogeo_bootleg_sx_decrypt(1);
				svcboot_cx_decrypt();
				break;

			case INIT_svcplusa:
				svcboot_cx_decrypt();
				break;

			case INIT_svcsplus:
				neogeo_bootleg_sx_decrypt(2);
				svcboot_cx_decrypt();
				break;

			case INIT_samsho5b:
				kof2000_neogeo_gfx_decrypt(0x0f);
				break;

			case INIT_kf2k3bl:
				neogeo_bootleg_sx_decrypt(1);
				break;

			case INIT_kf2k3pl:
				neogeo_bootleg_sx_decrypt(1);
				break;

			case INIT_kf2k3upl:
				neogeo_bootleg_sx_decrypt(2);
				break;

			case INIT_kog:
				neogeo_bootleg_sx_decrypt(1);
				neogeo_bootleg_cx_decrypt();
				break;

			case INIT_cthd2003:
				cthd2003_cx_decrypt();
				break;

			case INIT_ct2k3sp:
				ct2k3sp_sx_decrypt();
				ct2k3sp_cx_decrypt();
				break;

			case INIT_lans2004:
				neogeo_bootleg_sx_decrypt(1);
				neogeo_bootleg_cx_decrypt();
				break;

			case INIT_mslug3b6:
				neogeo_bootleg_sx_decrypt(2);
				cmc42_neogeo_gfx_decrypt(0xad);
				break;

			default: goto error;
			}

			neogeo_decode_spr(memory_region_gfx3, memory_length_gfx3, gfx_pen_usage[TILE_SPR]);
		}
		else
		{
			return 0;
		}
	}
	else
	{
		if (load_rom_gfx3())
		{
			neogeo_decode_spr(memory_region_gfx3, memory_length_gfx3, gfx_pen_usage[TILE_SPR]);
		}
		else
		{
			return 0;
		}
	}

	return 1;

error:
	printf("ERROR: Unknown romset.\n");
	return 0;
}



static int create_raw_cache(char *game_name)
{
	FILE *fp;
	char version[8];
	char fname[MAX_PATH];

	sprintf(version, "MVS_V%d%d\0", VERSION_MAJOR, VERSION_MINOR);

	chdir("cache");

	printf("Create cache file...\n");

	sprintf(fname, "%s_cache", game_name);
	if (chdir(fname) != 0)
	{
#ifdef UNIX
		if (mkdir(fname, 0777) != 0)
#else
		if (mkdir(fname) != 0)
#endif
		{
			printf("ERROR: Could not create folder.\n");
			chdir(launchDir);
			return 0;
		}
		chdir(fname);
	}

	if ((fp = fopen("cache_info", "wb")) == NULL) goto error;
	fwrite(version, 1, 8, fp);
	fwrite(gfx_pen_usage[TILE_SPR], 1, gfx_total_elements[TILE_SPR], fp);
	fclose(fp);

	if ((fp = fopen("crom", "wb")) == NULL) goto error;
	fwrite(memory_region_gfx3, 1, memory_length_gfx3, fp);
	fclose(fp);

	if (encrypt_gfx2)
	{
		if ((fp = fopen("srom", "wb")) == NULL) goto error;
		fwrite(memory_region_gfx2, 1, memory_length_gfx2, fp);
		fclose(fp);
	}

	if (encrypt_snd1 || disable_sound)
	{
		if ((fp = fopen("vrom", "wb")) == NULL) goto error;
		fwrite(memory_region_sound1, 1, memory_length_sound1, fp);
		fclose(fp);
	}

	chdir("..");
	chdir("..");
	return 1;

error:
	remove("cache_info");
	remove("crom");

	if (encrypt_gfx2)
	{
		remove("srom");
	}
	if (encrypt_snd1 || disable_sound)
	{
		remove("vrom");
	}

	chdir("..");

	sprintf(fname, "cache_%s", game_name);
	rmdir(fname);

	printf("ERROR: Could not create file.\n");
	chdir("..");
	return 0;
}


int main(int argc, char *argv[])
{
	char *p, path[MAX_PATH];
	int i, path_found = 0, all = 0, zip = 0, res = 1;
#ifdef WIN32
	int pause = 1;

	check_windows_version();
#endif
	check_byte_order();

	printf("----------------------------------------------\n");
	printf(" ROM converter for NEOGEO Emulator ver." VERSION_STR "\n");
	printf("----------------------------------------------\n\n");

	if (argc > 1)
	{
		for (i = 1; i < argc; i++)
		{
			if (!strcasecmp(argv[i], "-all"))
			{
				all = 1;
			}
#ifdef WIN32
			else if (!strcasecmp(argv[i], "-batch"))
			{
				pause = 0;
			}
			else if (strchr(argv[i], ':') != NULL || strchr(argv[i], DELIMITER) != NULL)
#else
			else if (strchr(argv[i], DELIMITER) != NULL)
#endif
			{
				path_found = i;
			}
		}
	}

#ifndef WIN32
	if (!path_found)
	{
		printf("usage: romcnv_mvs fullpath%cgamename.zip\n", DELIMITER);
		printf("  or   romcnv_mvs fullpath -all\n\n", DELIMITER);
		return 0;
	}
#endif

	if (chdir("cache") != 0)
	{
#ifdef UNIX
		if (mkdir("cache", 0777) != 0)
#else
		if (mkdir("cache") != 0)
#endif
		{
			printf("ERROR: Could not create directory \"cache\".\n");
			goto error;
		}
	}
	else chdir("..");

#ifdef WIN32
	strcpy(launchDir, argv[0]);
	convert_delimiter(launchDir);

	if ((p = strrchr(launchDir, delimiter)) != NULL)
	{
		*(p + 1) = '\0';
	}
	else
	{
		getcwd(launchDir, MAX_PATH);

		convert_delimiter(launchDir);
		if (is_win9x)
			strcat(launchDir, "\\");
		else
			strcat(launchDir, "/");
	}
#else
	getcwd(launchDir, MAX_PATH);
	strcat(launchDir, "/");
#endif

	if (all)
	{
		int total_games;

#ifdef WIN32
		if (!folder_dialog(NULL, zip_dir)) goto error;
		convert_delimiter(zip_dir);

		strcpy(game_dir, zip_dir);

		if (is_win9x)
			strcat(game_dir, "\\");
		else
			strcat(game_dir, "/");
#else
		strcpy(zip_dir, argv[path_found]);
		strcpy(game_dir, zip_dir);
		strcat(game_dir, "/");
#endif

		total_games = build_game_list();

		for (i = 0; i < total_games; i++)
		{
			res = 1;

			strcpy(game_name, game_names[i]);

			printf("\n-------------------------------------------\n");
			printf("  ROM set: %s\n", game_name);
			printf("-------------------------------------------\n\n");

			chdir(launchDir);
			if (!convert_rom(game_name))
			{
				printf("ERROR: Convert failed. - Skip\n\n");
			}
			else
			{
				if (create_raw_cache(game_name))
				{
					printf("Done.\n\n");
				}
			}
			free_memory();
		}

		printf("complete.\n");
		printf("Please copy these files to directory \"/PSP/GAMES/mvspsp/cache\".\n");
	}
	else
	{
#ifdef WIN32
		if (!path_found)
		{
			printf("Please select ROM file.\n");

			if (!file_dialog(NULL, "zip file (*.zip)\0*.zip\0", game_dir, OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY))
				goto error;
		}
		else
		{
			strcpy(path, argv[path_found]);
			strcpy(game_dir, strtok(path, "\""));
		}
		convert_delimiter(game_dir);
#else
		strcpy(game_dir, argv[path_found]);
#endif

		if ((p = strrchr(game_dir, delimiter)) != NULL)
		{
			strcpy(game_name, p + 1);
			strcpy(zip_dir, game_dir);
			*strrchr(zip_dir, delimiter) = '\0';
		}
		else
		{
			strcpy(game_name, game_dir);
			strcpy(zip_dir, "");
		}

		p = game_name;
		while (*p)
		{
			*p = tolower(*p);
			*p++;
		}

		printf("path: %s\n", zip_dir);
		printf("filename: %s\n", game_name);

		if ((p = strrchr(game_name, '.')) == NULL)
		{
			printf("Please input correct path.\n");
			goto error;
		}
		*p = '\0';

		printf("cache folder name: cache%c%s_cache\n", delimiter, game_name);

		chdir(launchDir);
		if (!convert_rom(game_name))
		{
			res = 0;
		}
		else
		{
			res = create_raw_cache(game_name);
		}
#ifdef WIN32
		if (res && pause)
#else
		if (res)
#endif
		{
			printf("complete.\n");
			printf("Please copy \"cache%c%s_cache\" folder to directory \"/PSP/GAMES/mvspsp/cache\".\n", delimiter, game_name);
		}
		free_memory();
	}

error:
#ifdef WIN32
	if (pause)
	{
		printf("Press any key to exit.\n");
		getch();
	}
#endif
	return res;
}
