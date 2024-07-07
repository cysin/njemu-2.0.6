/******************************************************************************

	ascii_14.c

	14 pixels ASCII code (ISO-646) fixed pitch font.

	code: 0x20-0x7f

******************************************************************************/

#ifdef COMMAND_LIST

#include "psp/psp.h"

#define NUM_FONTS	0x60

/*------------------------------------------------------
	gryph data
------------------------------------------------------*/

static const u8 ALIGN_DATA ascii_14[] = {
	0xf0,0x08,0xf0,0x08,0xf0,0x08,0xf0,0x08,0xf0,0x08,0xf0,0x08,0xf0,0x08,0xf0,0x08,
	0x80,0x04,0x80,0x06,0xf4,0x0c,0xf4,0x0c,0x60,0x6f,0x6f,0xc0,0xc6,0x06,0x66,0x84,
	0x00,0x00,0x64,0x80,0x00,0x00,0xca,0xf0,0x04,0x00,0x8c,0xf4,0x00,0x40,0xac,0xf8,
	0x04,0xf8,0xff,0xff,0x0f,0x00,0x4f,0xc8,0x00,0x00,0x4f,0xac,0x00,0x40,0x0f,0x8c,
	0x00,0xa4,0x8f,0xcc,0x08,0xc6,0xcf,0xcf,0x0c,0x80,0x0c,0x4f,0x00,0xa0,0x4a,0x0f,
	0x00,0xc0,0x48,0x0f,0x00,0x20,0x00,0x04,0x00,0x00,0xc0,0x02,0x00,0x00,0xfa,0x4c,
	0x00,0xc0,0xfc,0xfa,0x04,0xf4,0xf0,0xa4,0x0a,0xf4,0xf0,0x44,0x06,0xf0,0xf8,0x04,
	0x00,0x20,0xfc,0x2c,0x00,0x00,0xf0,0xfc,0x04,0x20,0xf0,0xa4,0x0c,0xf6,0xf0,0x44,
	0x0f,0xf0,0xf6,0xa4,0x0c,0x80,0xff,0xff,0x04,0x00,0xf0,0x06,0x00,0x00,0x40,0x00,
	0x00,0xf4,0x04,0xc0,0x00,0x8c,0x0c,0xc4,0x00,0x0f,0x0f,0x6a,0x00,0x0f,0x0f,0x0f,
	0x00,0x0c,0x4c,0x0a,0x00,0xca,0xaa,0x86,0x02,0x60,0xf0,0xc8,0x0c,0x00,0xa6,0x4c,
	0x0f,0x00,0x4a,0x4c,0x0f,0x00,0x0f,0x4c,0x0f,0x60,0x0a,0xa8,0x0f,0x80,0x04,0xc0,
	0x06,0xa0,0xcf,0x00,0x00,0xf2,0xf8,0x06,0x00,0xf4,0xc4,0x08,0x00,0xf2,0xc4,0x06,
	0x00,0xc4,0xff,0x00,0x00,0x84,0x6f,0x00,0x00,0xf4,0xcc,0xf8,0x00,0xf6,0xf0,0xff,
	0x00,0xf8,0x60,0xff,0x00,0xf6,0x22,0xcf,0x00,0xc0,0xff,0xfc,0x06,0x00,0x44,0x40,
	0x02,0xf8,0x04,0xf6,0x02,0xc0,0x00,0x40,0x00,0x00,0xf0,0x08,0x00,0xcc,0x00,0x40,
	0x2f,0x00,0xa0,0x0a,0x00,0xf0,0x04,0x00,0xf0,0x00,0x00,0xf4,0x00,0x00,0xf0,0x00,
	0x00,0xf0,0x04,0x00,0xa0,0x0a,0x00,0x40,0x2f,0x00,0x00,0xcc,0x00,0x00,0xf0,0x08,
	0xc8,0x00,0xc0,0x0a,0x40,0x4f,0x00,0xac,0x00,0xf6,0x00,0xf4,0x00,0xf4,0x00,0xf4,
	0x00,0xf6,0x00,0xac,0x40,0x4f,0xc0,0x0a,0xc8,0x00,0x00,0x40,0x00,0x00,0x00,0xf0,
	0x08,0x00,0xc0,0xf8,0xc8,0x08,0xf4,0xff,0xff,0x08,0x00,0xfc,0x8f,0x00,0xf4,0xff,
	0xff,0x08,0xc0,0xf8,0xc8,0x08,0x00,0xf0,0x08,0x00,0x00,0x40,0x00,0x00,0x00,0x40,
	0x00,0x00,0x00,0xf0,0x08,0x00,0x00,0xf0,0x08,0x00,0xc6,0xfc,0xcc,0x0c,0xc6,0xfc,
	0xcc,0x0c,0x00,0xf0,0x08,0x00,0x00,0xf0,0x08,0x00,0x00,0x40,0x00,0x00,0xc6,0x02,
	0xf8,0x02,0xc0,0x00,0x62,0x00,0xf4,0xff,0x0f,0x84,0x88,0x08,0x80,0x04,0xf4,0x08,
	0x40,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x40,0x0f,0x00,0x00,0xc0,0x08,0x00,0x00,
	0xf2,0x00,0x00,0x00,0xaa,0x00,0x00,0x00,0x0f,0x00,0x00,0xa0,0x0a,0x00,0x00,0xf0,
	0x04,0x00,0x00,0xc8,0x00,0x00,0x00,0x4f,0x00,0x00,0x60,0x0c,0x00,0x00,0xc0,0x06,
	0x00,0x00,0xc6,0x00,0x00,0x00,0x44,0x00,0x00,0x00,0x00,0xf6,0x6f,0x00,0x60,0xaf,
	0xfa,0x06,0xc0,0x0c,0xc0,0x0c,0xc4,0x06,0x60,0x0c,0xf4,0x06,0x60,0x0f,0xf4,0x06,
	0x60,0x0f,0xf4,0x06,0x60,0x0f,0xc0,0x06,0x60,0x0c,0xc0,0x0c,0xc0,0x0c,0x60,0xaf,
	0xfa,0x06,0x00,0xf6,0x6f,0x00,0x00,0xc6,0xa4,0xcf,0xc6,0xcf,0x00,0xcc,0x00,0xcc,
	0x00,0xcc,0x00,0xcc,0x00,0xcc,0x00,0xcc,0x00,0xcc,0x00,0xcc,0x00,0x22,0x00,0xfa,
	0x8f,0x00,0x80,0x4f,0xf6,0x06,0xf0,0x08,0xc0,0x0a,0xf0,0x06,0xc0,0x0a,0x00,0x00,
	0xf2,0x06,0x00,0x00,0xcc,0x00,0x00,0xc0,0x2f,0x00,0x00,0xfa,0x06,0x00,0x40,0x6f,
	0x00,0x00,0xc0,0x0c,0x00,0x00,0xf4,0xff,0xff,0x08,0x40,0x44,0x44,0x00,0x00,0xfc,
	0x8f,0x00,0xa0,0x4f,0xf8,0x04,0xf0,0x06,0xf0,0x08,0x80,0x00,0xf0,0x06,0x00,0x80,
	0xfc,0x00,0x00,0xf0,0xaf,0x00,0x00,0x40,0xf8,0x06,0x80,0x00,0xc0,0x0c,0xf2,0x04,
	0xc0,0x0c,0xc0,0x0a,0xf2,0x08,0x40,0xff,0xcf,0x00,0x00,0x40,0x04,0x00,0x00,0x40,
	0xcf,0x00,0x00,0xa0,0xcf,0x00,0x00,0xf0,0xcf,0x00,0x00,0xca,0xcc,0x00,0x00,0x6f,
	0xcc,0x00,0x80,0x0c,0xcc,0x00,0xf0,0x08,0xcc,0x00,0xf4,0xff,0xff,0x0c,0x80,0x88,
	0xcc,0x06,0x00,0x00,0xcc,0x00,0x00,0x00,0xcc,0x00,0x00,0x00,0x22,0x00,0xfc,0xff,
	0x4f,0xcc,0x88,0x08,0x8f,0x00,0x00,0x8f,0x00,0x00,0xcf,0xff,0x08,0xcf,0x84,0x6f,
	0x04,0x00,0xac,0x00,0x00,0xcc,0x4f,0x00,0xac,0xac,0x40,0x6f,0xf2,0xff,0x0c,0x00,
	0x24,0x00,0x00,0xf8,0x8f,0x00,0x80,0x8f,0xfa,0x04,0xc0,0x08,0xa0,0x06,0xf0,0x24,
	0x00,0x00,0xf4,0xfc,0xaf,0x00,0xf4,0x4f,0xf6,0x06,0xf4,0x08,0xc0,0x0c,0xf4,0x04,
	0x80,0x0c,0xf0,0x08,0xa0,0x0c,0xc0,0x0c,0xf6,0x06,0x20,0xff,0xcf,0x00,0x00,0x40,
	0x04,0x00,0xff,0xff,0x8f,0x88,0x88,0x8f,0x00,0x20,0x2f,0x00,0x80,0x0f,0x00,0xc0,
	0x0a,0x00,0xf0,0x06,0x00,0xf6,0x00,0x00,0xca,0x00,0x00,0x6f,0x00,0x40,0x2f,0x00,
	0x80,0x0c,0x00,0x20,0x02,0x00,0x20,0xfc,0x8f,0x00,0xc0,0x8f,0xfa,0x04,0xf0,0x08,
	0xf0,0x08,0xf0,0x08,0xf0,0x08,0x80,0x8f,0xfc,0x00,0x20,0xff,0xaf,0x00,0xc0,0x0c,
	0xf4,0x06,0xf2,0x04,0xc0,0x0c,0xf4,0x04,0xc0,0x0c,0xf0,0x0c,0xf4,0x08,0x60,0xff,
	0xcf,0x00,0x00,0x40,0x04,0x00,0x00,0xfc,0x4f,0x00,0xc0,0x8c,0xfa,0x00,0xf0,0x04,
	0xf0,0x06,0xf4,0x04,0xc0,0x0c,0xf4,0x04,0xc0,0x0c,0xf0,0x0a,0xf4,0x0c,0x60,0xff,
	0xff,0x0c,0x00,0x84,0xa6,0x0c,0x80,0x02,0xf0,0x08,0xc0,0x0c,0xf8,0x04,0x20,0xff,
	0xaf,0x00,0x00,0x40,0x02,0x00,0xc6,0x02,0xf8,0x04,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0xf8,0x04,0xc6,0x02,0xc6,0x02,0xf8,0x04,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0xf8,0x04,0xf6,0x04,0xf0,0x00,0x60,0x00,0x00,0x00,0x0a,0x00,0xc0,0x2f,
	0x00,0xfc,0x02,0xc0,0x2f,0x00,0xfa,0x06,0x00,0xc0,0x2f,0x00,0x00,0xfc,0x02,0x00,
	0xc0,0x2f,0x00,0x00,0x0a,0xc2,0xcc,0xcc,0x0c,0xc2,0xcc,0xcc,0x0c,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xf4,0xff,0xff,0x0f,0x80,0x88,0x88,0x08,0x66,0x00,0x00,
	0xfa,0x06,0x00,0xa0,0x6f,0x00,0x00,0xfa,0x06,0x00,0xc0,0x2f,0x00,0xfa,0x06,0xa0,
	0x6f,0x00,0xfa,0x06,0x00,0x66,0x00,0x00,0x00,0x40,0x04,0x00,0x20,0xff,0xcf,0x02,
	0xc0,0x0a,0xc0,0x0a,0xf2,0x00,0x60,0x0f,0xf4,0x00,0x80,0x0c,0x00,0x00,0xf2,0x08,
	0x00,0x20,0xaf,0x00,0x00,0xa0,0x0c,0x00,0x00,0xc0,0x08,0x00,0x00,0x80,0x04,0x00,
	0x00,0x80,0x04,0x00,0x00,0xf0,0x08,0x00,0x00,0xf0,0x08,0x00,0x00,0xc8,0x0a,0x00,
	0xa0,0x4a,0xc8,0x00,0xc4,0x00,0xa0,0x06,0x6a,0xfc,0x8f,0x0a,0x8c,0x0c,0x8c,0x0c,
	0x8c,0x0c,0x8c,0x0c,0x8c,0x0c,0x8c,0x0c,0x8c,0x0c,0x8c,0x0c,0x8c,0x0c,0x8c,0x0c,
	0x8c,0x4c,0xcc,0x0a,0x88,0xf8,0xc8,0x02,0xf2,0x02,0xc0,0x06,0x60,0x8f,0xcc,0x00,
	0x00,0x84,0x06,0x00,0x00,0xf8,0x06,0x00,0x00,0xfc,0x0a,0x00,0x00,0xff,0x0c,0x00,
	0x00,0xcf,0x0f,0x00,0x60,0x6f,0x4f,0x00,0x80,0x0f,0x8f,0x00,0xc0,0x0c,0xac,0x00,
	0xf0,0xcf,0xcf,0x00,0xf4,0x46,0xf8,0x00,0xf6,0x02,0xf4,0x04,0xfa,0x00,0xf0,0x08,
	0x42,0x00,0x40,0x02,0xf4,0xff,0x6c,0x00,0xf4,0x46,0xfc,0x04,0xf4,0x04,0xf0,0x08,
	0xf4,0x04,0xf2,0x08,0xf4,0xcc,0xff,0x00,0xf4,0xcc,0xff,0x02,0xf4,0x04,0xc0,0x0a,
	0xf4,0x04,0x80,0x0f,0xf4,0x04,0xa0,0x0f,0xf4,0x04,0xf6,0x0a,0xf4,0xff,0xcf,0x00,
	0x40,0x44,0x02,0x00,0x00,0xf8,0x2c,0x00,0x60,0xaf,0xfc,0x00,0xc0,0x0a,0xf0,0x06,
	0xf2,0x04,0xc0,0x0c,0xf4,0x04,0x20,0x02,0xf4,0x04,0x00,0x00,0xf4,0x04,0x20,0x02,
	0xf4,0x04,0xc0,0x0c,0xf0,0x08,0xf0,0x08,0x80,0x4f,0xfa,0x02,0x00,0xfc,0x6f,0x00,
	0x00,0x40,0x04,0x00,0xf4,0xff,0x0a,0x00,0xf4,0x86,0xcf,0x00,0xf4,0x04,0xf6,0x04,
	0xf4,0x04,0xf0,0x08,0xf4,0x04,0xf0,0x08,0xf4,0x04,0xf0,0x08,0xf4,0x04,0xf0,0x08,
	0xf4,0x04,0xf0,0x08,0xf4,0x04,0xf6,0x02,0xf4,0x86,0xcf,0x00,0xf4,0xff,0x0a,0x00,
	0xf4,0xff,0xff,0x00,0xf4,0x8a,0x88,0x00,0xf4,0x04,0x00,0x00,0xf4,0x04,0x00,0x00,
	0xf4,0x8a,0x48,0x00,0xf4,0xff,0x8f,0x00,0xf4,0x04,0x00,0x00,0xf4,0x04,0x00,0x00,
	0xf4,0x04,0x00,0x00,0xf4,0x04,0x00,0x00,0xf4,0xff,0xff,0x04,0x40,0x44,0x44,0x00,
	0xf4,0xff,0xcf,0xf4,0x8a,0x68,0xf4,0x04,0x00,0xf4,0x04,0x00,0xf4,0x8a,0x04,0xf4,
	0xff,0x08,0xf4,0x04,0x00,0xf4,0x04,0x00,0xf4,0x04,0x00,0xf4,0x04,0x00,0xf4,0x04,
	0x00,0x40,0x00,0x00,0x00,0xfa,0xaf,0x00,0x80,0x8f,0xf8,0x08,0xf0,0x0a,0xa0,0x0f,
	0xf4,0x04,0x40,0x0f,0xf4,0x04,0x00,0x00,0xf2,0x04,0xfc,0x0f,0xf4,0x04,0x62,0x0f,
	0xf4,0x04,0x40,0x0f,0xf0,0x0a,0x80,0x0f,0x80,0x8f,0xf0,0x0f,0x00,0xfa,0x8f,0x0f,
	0x00,0x20,0x04,0x04,0xf4,0x04,0xf0,0x08,0xf4,0x04,0xf0,0x08,0xf4,0x04,0xf0,0x08,
	0xf4,0x04,0xf0,0x08,0xf4,0x8a,0xf8,0x08,0xf4,0xcc,0xfc,0x08,0xf4,0x04,0xf0,0x08,
	0xf4,0x04,0xf0,0x08,0xf4,0x04,0xf0,0x08,0xf4,0x04,0xf0,0x08,0xf4,0x04,0xf0,0x08,
	0x40,0x00,0x40,0x00,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,
	0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0x40,0x00,0x00,0x00,0xf4,0x00,
	0x00,0xf4,0x00,0x00,0xf4,0x00,0x00,0xf4,0x00,0x00,0xf4,0x00,0x00,0xf4,0x40,0x00,
	0xf4,0xf8,0x00,0xf4,0xf6,0x00,0xf6,0xf2,0x4a,0xcc,0xa0,0xff,0x6f,0x00,0x42,0x00,
	0xf4,0x00,0xf2,0x0a,0xf4,0x00,0xcf,0x00,0xf4,0xc0,0x0c,0x00,0xf4,0xfa,0x02,0x00,
	0xf4,0x8f,0x00,0x00,0xf4,0xfc,0x00,0x00,0xf4,0xf0,0x0a,0x00,0xf4,0x80,0x2f,0x00,
	0xf4,0x00,0xcc,0x00,0xf4,0x00,0xf6,0x04,0xf4,0x00,0xc0,0x0c,0x40,0x00,0x00,0x04,
	0xf4,0x04,0x00,0x00,0xf4,0x04,0x00,0x00,0xf4,0x04,0x00,0x00,0xf4,0x04,0x00,0x00,
	0xf4,0x04,0x00,0x00,0xf4,0x04,0x00,0x00,0xf4,0x04,0x00,0x00,0xf4,0x04,0x00,0x00,
	0xf4,0x04,0x00,0x00,0xf4,0x04,0x00,0x00,0xf4,0xff,0xff,0x0c,0x40,0x44,0x44,0x02,
	0xf4,0x4f,0x40,0x0f,0xf4,0x8f,0x80,0x0f,0xf4,0xaf,0xa0,0x0f,0xf4,0xcf,0xc0,0x0f,
	0xf4,0xff,0xf0,0x0f,0xf4,0xff,0xf8,0x0f,0xf4,0xfc,0xfc,0x0f,0xf4,0xfc,0xcf,0x0f,
	0xf4,0xcc,0xcf,0x0f,0xf4,0x8c,0xaf,0x0f,0xf4,0x4c,0x8f,0x0f,0x40,0x02,0x04,0x04,
	0xf2,0x04,0x00,0x0f,0xf2,0x08,0x40,0x0f,0xf2,0x4c,0x40,0x0f,0xf2,0xaf,0x20,0x0f,
	0xf2,0xfa,0x46,0x0f,0xf2,0xf4,0x4c,0x0f,0xf2,0xc4,0x4f,0x0f,0xf2,0x64,0xaf,0x0f,
	0xf2,0x04,0xfa,0x0f,0xf2,0x04,0xc4,0x0f,0xf2,0x04,0x80,0x0f,0x42,0x00,0x40,0x04,
	0x00,0xfa,0xaf,0x00,0xa0,0x8c,0xc8,0x0a,0xf2,0x08,0x80,0x0f,0xf2,0x04,0x40,0x0f,
	0xf2,0x04,0x40,0x0f,0xf2,0x04,0x40,0x0f,0xf2,0x04,0x40,0x0f,0xf2,0x04,0x40,0x0f,
	0xf2,0x08,0x80,0x0f,0xa0,0x8c,0xc8,0x0a,0x00,0xfa,0xaf,0x00,0x00,0x20,0x00,0x00,
	0xf4,0xff,0xaf,0x02,0xf4,0x8a,0xf8,0x0c,0xf4,0x04,0x60,0x0f,0xf4,0x04,0x40,0x0f,
	0xf4,0x04,0xa0,0x0f,0xf4,0xcc,0xfc,0x08,0xf4,0x8a,0x68,0x00,0xf4,0x04,0x00,0x00,
	0xf4,0x04,0x00,0x00,0xf4,0x04,0x00,0x00,0xf4,0x04,0x00,0x00,0x40,0x00,0x00,0x00,
	0x40,0xfc,0xcf,0x00,0x80,0x0f,0xf0,0x08,0xf0,0x08,0x80,0x0f,0xf2,0x04,0x40,0x0f,
	0xf4,0x04,0x40,0x0f,0xf4,0x04,0x40,0x0f,0xf4,0x04,0x40,0x0f,0xf4,0x64,0x6c,0x0f,
	0xf0,0x28,0xff,0x0f,0x80,0x0f,0xf8,0x0c,0x00,0xfc,0xcf,0x0f,0x00,0x40,0x02,0x04,
	0xf4,0xff,0x4c,0x00,0xf4,0x88,0xfc,0x04,0xf4,0x00,0xf0,0x08,0xf4,0x00,0xf0,0x08,
	0xf4,0x00,0xf6,0x06,0xf4,0xff,0xcf,0x00,0xf4,0xc8,0x0c,0x00,0xf4,0x40,0x4f,0x00,
	0xf4,0x00,0xcc,0x00,0xf4,0x00,0xf4,0x04,0xf4,0x00,0xc0,0x0c,0x40,0x00,0x00,0x04,
	0x00,0xfa,0x8f,0x00,0xc0,0x8f,0xfa,0x08,0xf4,0x04,0xa0,0x0c,0xf2,0x0a,0x60,0x0c,
	0xa0,0xcf,0x04,0x00,0x00,0xc6,0xaf,0x00,0x00,0x00,0xf8,0x08,0xf6,0x04,0x80,0x0f,
	0xf4,0x04,0x60,0x0f,0xf0,0x4c,0xc4,0x0f,0x40,0xff,0xff,0x02,0x00,0x40,0x04,0x00,
	0xf4,0xff,0xff,0x0f,0x80,0xc8,0x8c,0x08,0x00,0xc0,0x0c,0x00,0x00,0xc0,0x0c,0x00,
	0x00,0xc0,0x0c,0x00,0x00,0xc0,0x0c,0x00,0x00,0xc0,0x0c,0x00,0x00,0xc0,0x0c,0x00,
	0x00,0xc0,0x0c,0x00,0x00,0xc0,0x0c,0x00,0x00,0xc0,0x0c,0x00,0x00,0x20,0x02,0x00,
	0x04,0x00,0x00,0x00,0xf4,0x08,0x80,0x0f,0xf4,0x08,0x80,0x0f,0xf4,0x08,0x80,0x0f,
	0xf4,0x08,0x80,0x0f,0xf4,0x08,0x80,0x0f,0xf4,0x08,0x80,0x0f,0xf4,0x08,0x80,0x0f,
	0xf4,0x08,0x80,0x0f,0xf4,0x08,0xa0,0x0f,0x84,0x6f,0xf6,0x0a,0x00,0xfc,0xcf,0x00,
	0x00,0x20,0x04,0x00,0xf6,0x04,0xf4,0x06,0xf4,0x06,0xf6,0x04,0xf0,0x08,0xf8,0x00,
	0xc0,0x0c,0xcc,0x00,0xa0,0x0f,0xaf,0x00,0x60,0x4f,0x6f,0x00,0x40,0x8f,0x4f,0x00,
	0x00,0xff,0x0f,0x00,0x00,0xfc,0x0c,0x00,0x00,0xfa,0x0a,0x00,0x00,0xf6,0x06,0x00,
	0x00,0x40,0x00,0x00,0xac,0xf4,0xa4,0x0c,0xcc,0xf6,0xc6,0x0c,0xca,0xf8,0xc8,0x0a,
	0xf8,0xfa,0xfa,0x08,0xf6,0xfc,0xfc,0x06,0xf4,0xff,0xff,0x04,0xf0,0xff,0xff,0x02,
	0xf0,0x8f,0xff,0x00,0xc0,0x8f,0xff,0x00,0xc0,0x0f,0xcf,0x00,0xa0,0x0f,0xaf,0x00,
	0x00,0x04,0x02,0x00,0xcc,0x00,0xf0,0x0a,0xf4,0x06,0xf6,0x04,0xc0,0x0c,0xcc,0x00,
	0x40,0xcf,0x4f,0x00,0x00,0xfc,0x0c,0x00,0x00,0xf8,0x08,0x00,0x00,0xff,0x0f,0x00,
	0x80,0x4f,0x8f,0x00,0xf0,0x0a,0xfa,0x00,0xf8,0x00,0xf0,0x08,0xaf,0x00,0xa0,0x0f,
	0x04,0x00,0x00,0x04,0xac,0x00,0xa0,0x0f,0xf6,0x00,0xf0,0x08,0xc0,0x0a,0xf8,0x00,
	0x60,0x0f,0x8f,0x00,0x00,0xcf,0x0f,0x00,0x00,0xf8,0x08,0x00,0x00,0xf4,0x04,0x00,
	0x00,0xf4,0x04,0x00,0x00,0xf4,0x04,0x00,0x00,0xf4,0x04,0x00,0x00,0xf4,0x04,0x00,
	0x00,0x40,0x00,0x00,0xc0,0xff,0xff,0x0f,0x60,0x88,0xc8,0x0f,0x00,0x00,0xf0,0x08,
	0x00,0x00,0xca,0x00,0x00,0x40,0x6f,0x00,0x00,0xc0,0x0c,0x00,0x00,0xf4,0x04,0x00,
	0x00,0xcc,0x00,0x00,0x60,0x4f,0x00,0x00,0xc0,0x0a,0x00,0x00,0xf4,0xff,0xff,0x0f,
	0x40,0x44,0x44,0x04,0xf4,0xff,0x08,0xf4,0x8a,0x04,0xf4,0x04,0x00,0xf4,0x04,0x00,
	0xf4,0x04,0x00,0xf4,0x04,0x00,0xf4,0x04,0x00,0xf4,0x04,0x00,0xf4,0x04,0x00,0xf4,
	0x04,0x00,0xf4,0x04,0x00,0xf4,0x04,0x00,0xf4,0xcc,0x06,0xc2,0xcc,0x06,0x08,0x00,
	0x00,0x00,0x4f,0x00,0x00,0x00,0xc8,0x00,0x00,0x00,0xf0,0x02,0x00,0x00,0xa0,0x0a,
	0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0xaa,0x00,0x00,0x00,0xf4,0x00,0x00,0x00,0xc0,
	0x08,0x00,0x00,0x40,0x0f,0x00,0x00,0x00,0x6c,0x00,0x00,0x00,0xc6,0x00,0x00,0x00,
	0xc0,0x06,0x00,0x00,0x40,0x04,0xfc,0xff,0x86,0xfc,0x00,0xf8,0x00,0xf8,0x00,0xf8,
	0x00,0xf8,0x00,0xf8,0x00,0xf8,0x00,0xf8,0x00,0xf8,0x00,0xf8,0x00,0xf8,0xc8,0xfc,
	0xc8,0xcc,0x00,0xa0,0x00,0x00,0x00,0xfc,0x0c,0x00,0xc0,0x0c,0xcc,0x00,0xca,0x00,
	0xc0,0x0a,0xcc,0xcc,0x06,0xf6,0x06,0x20,0x2f,0x00,0xc2,0x20,0xfc,0x0a,0xf0,0x8f,
	0xaf,0xf4,0x06,0xf8,0x00,0xc8,0xff,0xc0,0x8f,0xfc,0xf4,0x04,0xf8,0xf4,0x06,0xfc,
	0xc0,0xff,0xfc,0x00,0x24,0x40,0xf4,0x04,0x00,0x00,0xf4,0x04,0x00,0x00,0xf4,0x04,
	0x00,0x00,0xf4,0xfa,0x6f,0x00,0xf4,0x8f,0xfc,0x00,0xf4,0x06,0xf4,0x04,0xf4,0x04,
	0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x0c,0xfa,0x00,0xf4,0xfc,
	0x8f,0x00,0x40,0x40,0x02,0x00,0x00,0xfc,0x0a,0xc0,0x8f,0x8f,0xf2,0x04,0xcc,0xf4,
	0x04,0x22,0xf6,0x04,0x42,0xf4,0x04,0xcc,0xf0,0x2a,0xaf,0x60,0xff,0x2f,0x00,0x42,
	0x00,0x00,0x00,0xf4,0x04,0x00,0x00,0xf4,0x04,0x00,0x00,0xf4,0x04,0x40,0xcc,0xf6,
	0x04,0xf0,0x8c,0xff,0x04,0xf4,0x04,0xf6,0x04,0xf6,0x04,0xf4,0x04,0xf6,0x04,0xf4,
	0x04,0xf4,0x04,0xf6,0x04,0xf0,0x0a,0xfc,0x04,0xa0,0xff,0xfc,0x04,0x00,0x24,0x40,
	0x00,0x20,0xfc,0x08,0xc0,0x8c,0x6f,0xf2,0x04,0xca,0xf6,0xcc,0xcc,0xf6,0x8a,0x68,
	0xf4,0x04,0x66,0xf0,0x0a,0xaf,0x60,0xff,0x0f,0x00,0x40,0x00,0x00,0xfc,0x0f,0x80,
	0x8f,0x08,0x80,0x0f,0x00,0xf4,0xff,0x0f,0xc0,0x8f,0x08,0x80,0x0f,0x00,0x80,0x0f,
	0x00,0x80,0x0f,0x00,0x80,0x0f,0x00,0x80,0x0f,0x00,0x80,0x0f,0x00,0x00,0x04,0x00,
	0x20,0xfc,0xc8,0x0c,0xc0,0x8c,0xaf,0x02,0xf0,0x08,0xac,0x00,0xc0,0x6c,0x6f,0x00,
	0xc0,0xfc,0x0c,0x00,0xf4,0x04,0x00,0x00,0xc0,0xff,0xaf,0x00,0xf4,0x40,0xf4,0x06,
	0xf4,0x8a,0xf8,0x06,0x80,0xfc,0x8c,0x00,0xf4,0x04,0x00,0x00,0xf4,0x04,0x00,0x00,
	0xf4,0x04,0x00,0x00,0xf4,0xc6,0x2c,0x00,0xf4,0x8f,0xfc,0x00,0xf4,0x08,0xf4,0x02,
	0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,
	0xf4,0x04,0xf4,0x04,0x40,0x00,0x40,0x00,0xf4,0x04,0xf4,0x04,0x00,0x00,0xf4,0x04,
	0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0x40,0x00,
	0x00,0xf4,0x04,0x00,0xf4,0x04,0x00,0x40,0x00,0x00,0xf4,0x04,0x00,0xf4,0x04,0x00,
	0xf4,0x04,0x00,0xf4,0x04,0x00,0xf4,0x04,0x00,0xf4,0x04,0x00,0xf4,0x04,0x00,0xf4,
	0x04,0x00,0xc8,0x00,0xc6,0x4c,0x00,0xf4,0x04,0x00,0x00,0xf4,0x04,0x00,0x00,0xf4,
	0x04,0x00,0x00,0xf4,0x04,0xf6,0x06,0xf4,0x44,0x6f,0x00,0xf4,0xf6,0x0a,0x00,0xf4,
	0xff,0x00,0x00,0xf4,0xfc,0x08,0x00,0xf4,0x84,0x2f,0x00,0xf4,0x04,0xcf,0x00,0xf4,
	0x04,0xf6,0x04,0x40,0x00,0x40,0x02,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,
	0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0x40,0x00,0xf4,
	0x8a,0x6a,0x00,0xf4,0xac,0xaf,0x06,0xf4,0xf8,0xf8,0x06,0xf4,0xf4,0xf4,0x06,0xf4,
	0xf4,0xf4,0x06,0xf4,0xf4,0xf4,0x06,0xf4,0xf4,0xf4,0x06,0xf4,0xf4,0xf4,0x06,0x40,
	0x40,0x40,0x00,0xf4,0xc6,0x6c,0x00,0xf4,0xaf,0xfc,0x00,0xf4,0x06,0xf4,0x04,0xf4,
	0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,
	0x04,0xf4,0x04,0x40,0x00,0x40,0x00,0x00,0xa8,0x08,0x00,0x80,0xcf,0x8f,0x00,0xf0,
	0x08,0xf8,0x00,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x08,0xf8,0x04,0x60,
	0xcf,0x6f,0x00,0x00,0xc8,0x08,0x00,0x00,0x40,0x00,0x00,0xf4,0xca,0x2c,0x00,0xf4,
	0x8f,0xcf,0x00,0xf4,0x06,0xf6,0x04,0xf4,0x04,0xf4,0x06,0xf4,0x04,0xf4,0x08,0xf4,
	0x04,0xf4,0x04,0xf4,0x4c,0xfa,0x00,0xf4,0xfc,0x6f,0x00,0xf4,0x24,0x02,0x00,0xf4,
	0x04,0x00,0x00,0x20,0xfc,0xfa,0x04,0xc0,0x8f,0xff,0x04,0xf4,0x06,0xf6,0x04,0xf6,
	0x04,0xf4,0x04,0xf6,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf0,0x4c,0xfc,0x04,0x60,
	0xff,0xfc,0x04,0x00,0x22,0xf4,0x04,0x00,0x00,0xf4,0x04,0xf4,0xc8,0x08,0xf4,0x8f,
	0x04,0xf4,0x04,0x00,0xf4,0x04,0x00,0xf4,0x04,0x00,0xf4,0x04,0x00,0xf4,0x04,0x00,
	0xf4,0x04,0x00,0x40,0x00,0x00,0x40,0xfc,0x0a,0xf0,0x8c,0x8f,0xf4,0x04,0xa8,0xf0,
	0x8f,0x00,0x00,0xc8,0x8f,0xc4,0x02,0xfa,0xf2,0x0a,0xfa,0xa0,0xff,0x6f,0x00,0x42,
	0x02,0x00,0x04,0x00,0x40,0x4f,0x00,0x40,0x4f,0x00,0xc2,0xcf,0x02,0xa0,0xaf,0x00,
	0x40,0x4f,0x00,0x40,0x4f,0x00,0x40,0x4f,0x00,0x40,0x4f,0x00,0x40,0x4f,0x00,0x20,
	0xff,0x04,0x00,0x42,0x00,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,
	0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf0,0x4c,0xfc,
	0x04,0xa0,0xff,0xfc,0x04,0x00,0x22,0x40,0x00,0xf4,0x00,0xf0,0x04,0xf0,0x06,0xf6,
	0x00,0xc0,0x0a,0xca,0x00,0x80,0x0c,0x8c,0x00,0x20,0x4f,0x2f,0x00,0x00,0xcf,0x0f,
	0x00,0x00,0xfa,0x0a,0x00,0x00,0xf6,0x06,0x00,0x00,0x40,0x00,0x00,0x88,0xf4,0x84,
	0x08,0xa8,0xf8,0xc6,0x06,0xc6,0xfa,0xf8,0x06,0xf6,0xfc,0xfc,0x04,0xf4,0xcf,0xff,
	0x02,0xf0,0x8f,0xff,0x00,0xc0,0x2f,0xcf,0x00,0xa0,0x0f,0x8f,0x00,0x00,0x02,0x02,
	0x00,0x8f,0x80,0x0f,0xfa,0xf0,0x0a,0xf0,0xfc,0x00,0xa0,0xaf,0x00,0xa0,0xaf,0x00,
	0xf0,0xfc,0x00,0xfa,0xf0,0x0a,0x8f,0x80,0x0f,0x04,0x00,0x04,0x6f,0x00,0x6f,0xac,
	0x40,0x0f,0xc8,0xa0,0x0c,0xf4,0xc2,0x08,0xf0,0xf8,0x04,0xa0,0xff,0x00,0x60,0xcf,
	0x00,0x00,0x6f,0x00,0x86,0x2f,0x00,0xfc,0x08,0x00,0xc0,0xff,0xcf,0x60,0x88,0x8f,
	0x00,0x80,0x0c,0x00,0xf0,0x06,0x00,0xcc,0x00,0x40,0x4f,0x00,0xc0,0x0a,0x00,0xf4,
	0xff,0xcf,0x40,0x44,0x24,0x60,0x6c,0xf0,0x0a,0xf0,0x08,0xf0,0x08,0xf0,0x08,0xf0,
	0x08,0xf8,0x04,0xf6,0x06,0xf0,0x08,0xf0,0x08,0xf0,0x08,0xf0,0x08,0xf0,0x0a,0x40,
	0x6c,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,
	0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xf4,0x04,0xc6,0x06,0xa2,
	0x0f,0x80,0x0f,0x80,0x0f,0x80,0x0f,0x80,0x0f,0x40,0x8f,0x60,0x6f,0x80,0x0f,0x80,
	0x0f,0x80,0x0f,0x80,0x0f,0xa2,0x0f,0xc6,0x04,0xa2,0x2a,0xa0,0x88,0xf8,0x8f,0x00,
	0x40,0x06,0x80,0x48,0xf4,0x8f,0xf4,0x8f,0x40,0x04,0x00,0x00,0x00,0x00,0x00,0x00
};

static const int ALIGN_DATA ascii_14_pos[NUM_FONTS] = {
	0x000000,0x000000,0x000018,0x000021,0x000059,0x000091,0x0000c1,0x0000f1,0x0000f9,0x000120,0x00013a,0x00015e,0x00017e,0x000186,0x00018c,0x000192,
	0x0001ca,0x0001f6,0x00020e,0x00023e,0x00026e,0x00029e,0x0002c2,0x0002f2,0x000316,0x000346,0x000376,0x000386,0x00039a,0x0003b5,0x0003cd,0x0003e8,
	0x00041c,0x000454,0x000484,0x0004b4,0x0004e4,0x000510,0x000540,0x000564,0x000594,0x0005c4,0x0005dc,0x000600,0x000630,0x000660,0x000690,0x0006c0,
	0x0006f0,0x000720,0x000750,0x000780,0x0007b0,0x0007e0,0x000814,0x000844,0x000874,0x0008a4,0x0008d4,0x000904,0x00092e,0x000966,0x000982,0x000992,
	0x000995,0x00099b,0x0009b6,0x0009e6,0x000a01,0x000a31,0x000a4c,0x000a70,0x000a98,0x000ac8,0x000ae0,0x000b07,0x000b37,0x000b4f,0x000b73,0x000b97,
	0x000bbb,0x000be3,0x000c0b,0x000c26,0x000c41,0x000c65,0x000c89,0x000cad,0x000cd1,0x000cec,0x000d0a,0x000d25,0x000d41,0x000d5d,0x000d79,0x000d82

};

static const s8 ALIGN_DATA ascii_14_width[NUM_FONTS] = {
	 0, 4, 6, 8, 8, 8, 8, 4, 6, 4, 8, 8, 4, 6, 4, 8,
	 8, 4, 8, 8, 8, 6, 8, 6, 8, 8, 4, 4, 6, 8, 6, 8,
	 8, 8, 8, 8, 8, 8, 6, 8, 8, 4, 6, 8, 8, 8, 8, 8,
	 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 6, 8, 4, 8, 6,
	 4, 6, 8, 6, 8, 6, 6, 8, 8, 4, 6, 8, 4, 8, 8, 8,
	 8, 8, 6, 6, 6, 8, 8, 8, 6, 6, 6, 4, 4, 4, 6, 4
};

static const s8 ALIGN_DATA ascii_14_height[NUM_FONTS] = {
	 0,12, 3,14,14,12,12, 4,13,13, 9, 8, 4, 2, 3,14,
	11,12,12,12,12,12,12,12,12,12, 8,10, 9, 6, 9,13,
	14,12,12,12,11,12,12,12,12,12,12,12,12,12,12,12,
	12,12,12,12,12,13,12,12,12,12,12,14,14,14, 4, 1,
	 3, 9,12, 9,12, 9,12,10,12,12,13,12,12, 9, 9, 9,
	10,10, 9, 9,12, 9, 9, 9, 9,10, 9,14,14,14, 3, 4
};

static const s8 ALIGN_DATA ascii_14_skipx[NUM_FONTS] = {
	 6, 2, 0, 0, 0, 0, 0, 2, 1, 1, 0, 0, 2, 1, 2, 0,
	 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 2, 2, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1,
	 1, 0, 0, 0, 0, 0, 1, 0, 0, 2, 1, 0, 2, 0, 0, 0,
	 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 2, 1, 0, 1
};

static const s8 ALIGN_DATA ascii_14_skipy[NUM_FONTS] = {
	14, 1, 0, 0, 0, 1, 1, 0, 1, 1, 2, 3,10, 6,10, 0,
	 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 2, 4, 2, 0,
	 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0,13,
	 0, 4, 1, 4, 1, 4, 1, 4, 1, 1, 1, 1, 1, 4, 4, 4,
	 4, 4, 4, 4, 1, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 5
};


/*------------------------------------------------------
	functions
------------------------------------------------------*/

int ascii_14_get_gryph(struct font_t *font, u16 code)
{
	if (code < NUM_FONTS)
	{
		font->data   = &ascii_14[ascii_14_pos[code]];
		font->width  = ascii_14_width[code];
		font->height = ascii_14_height[code];
		font->pitch  = 7;
		font->skipx  = ascii_14_skipx[code];
		font->skipy  = ascii_14_skipy[code];
		return 1;
	}
	return 0;
}

#endif
