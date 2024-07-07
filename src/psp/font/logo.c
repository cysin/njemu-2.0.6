/******************************************************************************

	logo.c

	Emulator logo

******************************************************************************/

#include "psp/psp.h"

#if (EMU_SYSTEM == CPS1)

static const u8 ALIGN_DATA logo_data[14][116] = {
	{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
	{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
	{ 0x00,0xe7,0xef,0xee,0x06,0x00,0x60,0x0f,0x00,0x60,0xdb,0xdd,0x7c,0x00,0x70,0xfe,0xee,0x6e,0x00,0xc4,0xef,0x9f,0x00,0xd7,0x6d,0x00,0x00,0xd1,0x9d,0x00,0x00,0x00,0xe7,0xef,0xee,0x66,0xdb,0xdd,0x7c,0x00,0xf7,0xfe,0x9d,0x00,0x70,0x0d,0x00,0x00,0xb6,0xdd,0xdd,0xad,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf7,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x67,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0x0f,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00 },
	{ 0x70,0xbf,0x00,0xf6,0x07,0x00,0xc0,0x7f,0x00,0x00,0xf6,0x39,0xfe,0x07,0xf7,0x0b,0x60,0x7f,0x40,0xcf,0x01,0xf6,0x0b,0xa0,0xdf,0x00,0x00,0xf9,0x0d,0x00,0x00,0x70,0xbf,0x00,0xf6,0x07,0xf6,0x39,0xfe,0x37,0x8f,0x30,0x9f,0x00,0xf9,0x0f,0x00,0x00,0x60,0x9f,0x00,0xd8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x90,0x0f,0x00,0x00,0x00,0x00,0x49,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0xdf,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00 },
	{ 0xf1,0x0f,0x00,0x90,0x09,0x00,0xf3,0xbf,0x00,0x00,0xf6,0x09,0xf7,0x1d,0xff,0x00,0x00,0x99,0xe0,0x3f,0x00,0xb0,0x7f,0x90,0xff,0x06,0x00,0xff,0x0d,0x00,0x00,0xf1,0x0f,0x00,0x90,0x09,0xf6,0x09,0xf7,0x6d,0x9f,0x00,0x97,0x00,0x90,0x0f,0x00,0x00,0x60,0x9f,0x00,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x90,0x0f,0x00,0x00,0x00,0x30,0x6f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00 },
	{ 0xf7,0x0b,0x00,0x10,0x03,0x00,0xaa,0xff,0x01,0x00,0xf6,0x09,0xf7,0x7c,0xbf,0x00,0x00,0x31,0xf3,0x0e,0x00,0x70,0xbf,0x90,0xfd,0x0d,0x70,0xfd,0x0d,0x00,0x00,0xf7,0x0b,0x00,0x10,0x03,0xf6,0x09,0xf7,0x1c,0xff,0x3c,0x31,0x00,0x90,0x0f,0x00,0x00,0x60,0x9f,0x00,0x0e,0xb1,0xcf,0xff,0xf9,0xdf,0x70,0xad,0xa0,0x7d,0x90,0x0f,0x40,0xef,0x9f,0xf3,0xef,0x0a,0xf8,0xff,0x17,0xfb,0xfe,0x0c,0x00,0x00,0xff,0x6f,0xf9,0xcf,0x60,0x9c,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00 },
	{ 0xf9,0x09,0x00,0x00,0x00,0x10,0x3f,0xf9,0x07,0x00,0xf6,0x7b,0xff,0x97,0x9f,0x00,0x00,0x00,0xf6,0x0d,0x00,0x60,0xdf,0x90,0xd9,0x6f,0xe0,0xf7,0x0d,0x00,0x00,0xf9,0x09,0x00,0x00,0x00,0xf6,0x7b,0xff,0x07,0xf7,0xff,0x09,0x00,0x90,0x0f,0x00,0x00,0x60,0xff,0xed,0x0f,0x81,0xbf,0xf3,0x6f,0xf8,0x06,0xdd,0x00,0x9f,0x90,0x0f,0xd0,0x0d,0xfb,0x60,0x6f,0x60,0x4f,0xd0,0x3f,0xf8,0x4a,0x03,0x00,0x00,0xf7,0x60,0x4f,0xe2,0x7a,0xbf,0x07,0x00,0x00,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00 },
	{ 0xf9,0x09,0x00,0x00,0x00,0x80,0x9f,0xfb,0x0e,0x00,0xf6,0x9d,0x39,0x90,0x9f,0x00,0x00,0x00,0xf6,0x0d,0x00,0x60,0xdf,0x90,0x69,0xcf,0xf6,0xf0,0x0d,0x00,0x00,0xf9,0x09,0x00,0x00,0x00,0xf6,0x9d,0x39,0x00,0x10,0xfa,0xaf,0x00,0x90,0x0f,0x00,0x00,0x60,0x9f,0x10,0x0f,0x60,0x6f,0xd0,0x0d,0xf6,0x06,0xdd,0x00,0x9f,0x90,0x0f,0x70,0x77,0xfe,0x60,0x6f,0xc0,0x0f,0x60,0x9f,0xf6,0x06,0x00,0x00,0x00,0xf7,0xb0,0x0b,0x70,0x7f,0x0f,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
	{ 0xf7,0x0c,0x00,0x00,0x00,0xf0,0x67,0xd6,0x4f,0x00,0xf6,0x09,0x00,0x70,0xcf,0x00,0x00,0x00,0xf0,0x0f,0x00,0x80,0x8f,0x90,0x09,0xfe,0x9d,0xf0,0x0d,0x00,0x00,0xf7,0x0c,0x00,0x00,0x00,0xf6,0x09,0x00,0x40,0x08,0x40,0xff,0x00,0x90,0x0f,0x00,0x00,0x60,0x9f,0x00,0x14,0x63,0x6f,0xd0,0x0d,0xf6,0x06,0xdd,0x00,0x9f,0x90,0x0f,0x70,0xaf,0xfb,0x60,0x6f,0xd0,0x0f,0x10,0x9f,0xf6,0x06,0x00,0x00,0x00,0xf7,0xb0,0x0b,0x70,0x7f,0x0f,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
	{ 0xe0,0x4f,0x00,0x70,0x0a,0xf7,0x00,0x70,0xbf,0x00,0xf6,0x09,0x00,0x00,0xfe,0x04,0x00,0xa7,0xa0,0x8f,0x00,0xf0,0x1f,0x90,0x09,0xf7,0x1f,0xf0,0x0d,0x00,0x00,0xe0,0x4f,0x00,0x70,0x0a,0xf6,0x09,0x00,0x60,0x1f,0x00,0xfa,0x00,0x90,0x0f,0x00,0x00,0x60,0x9f,0x00,0xc0,0x67,0x6f,0xd0,0x0d,0xf6,0x06,0xdd,0x10,0x9f,0x90,0x0f,0xf0,0x0a,0xf9,0x60,0x6f,0xa0,0x6f,0x60,0x6f,0xf6,0x06,0x00,0x00,0x00,0xf7,0x80,0x0f,0xb0,0x7c,0x0f,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xfc },
	{ 0x40,0xff,0x69,0xda,0x61,0xcf,0x03,0x70,0xff,0x37,0xf9,0x4c,0x00,0x00,0xf4,0x9f,0xa6,0x1d,0x00,0xfb,0x79,0xfd,0x04,0xc4,0x4c,0xf0,0x1b,0xf7,0x6f,0x00,0x00,0x40,0xff,0x69,0xda,0x31,0xf9,0x4c,0x00,0x60,0xef,0x77,0x7f,0x00,0xc3,0x7f,0x00,0x00,0xa3,0xef,0x99,0xfd,0x91,0x9f,0xf6,0x6f,0xf9,0x19,0xfb,0xea,0xff,0xc7,0x7f,0xf0,0xbf,0xff,0x4f,0xcf,0x1e,0xef,0xe7,0x1b,0xf9,0x1a,0x00,0x00,0x00,0xf7,0x00,0xfd,0xff,0x72,0x0f,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0x0f,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0xf0,0xff },
	{ 0x00,0x71,0x99,0x07,0x40,0x66,0x03,0x60,0x66,0x36,0x66,0x46,0x00,0x00,0x10,0x97,0x79,0x00,0x00,0x40,0x99,0x17,0x00,0x64,0x46,0x30,0x11,0x66,0x66,0x00,0x00,0x00,0x71,0x99,0x07,0x30,0x66,0x46,0x00,0x30,0x76,0x99,0x06,0x00,0x63,0x66,0x00,0x00,0x63,0x66,0x66,0x46,0x61,0x66,0x66,0x66,0x66,0x16,0x81,0x39,0x49,0x63,0x66,0x40,0x89,0x96,0x04,0x97,0x03,0x81,0x79,0x10,0x66,0x16,0x00,0x00,0x00,0x00,0x00,0x60,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0xf0,0xf0 },
	{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
	{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 }
};

#elif (EMU_SYSTEM == CPS2)

static const u8 ALIGN_DATA logo_data[14][116] = {
	{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
	{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x24,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
	{ 0x00,0xe7,0xef,0xee,0x06,0x00,0x60,0x0f,0x00,0x60,0xdb,0xdd,0x7c,0x00,0x70,0xfe,0xee,0x6e,0x00,0xc4,0xef,0x9f,0x00,0xd7,0x6d,0x00,0x00,0xd1,0x9d,0x00,0x00,0x00,0xe7,0xef,0xee,0x66,0xdb,0xdd,0x7c,0x00,0xf7,0xfe,0x9d,0x20,0xfd,0xff,0x07,0x00,0x00,0xb6,0xdd,0xdd,0xad,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf7,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0x0f,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00 },
	{ 0x70,0xbf,0x00,0xf6,0x07,0x00,0xc0,0x7f,0x00,0x00,0xf6,0x39,0xfe,0x07,0xf7,0x0b,0x60,0x7f,0x40,0xcf,0x01,0xf6,0x0b,0xa0,0xdf,0x00,0x00,0xf9,0x0d,0x00,0x00,0x70,0xbf,0x00,0xf6,0x07,0xf6,0x39,0xfe,0x37,0x8f,0x30,0x9f,0x60,0x2d,0xe3,0x2f,0x00,0x00,0x60,0x9f,0x00,0xd8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x90,0x0f,0x00,0x00,0x00,0x00,0x49,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00 },
	{ 0xf1,0x0f,0x00,0x90,0x09,0x00,0xf3,0xbf,0x00,0x00,0xf6,0x09,0xf7,0x1d,0xff,0x00,0x00,0x99,0xe0,0x3f,0x00,0xb0,0x7f,0x90,0xff,0x06,0x00,0xff,0x0d,0x00,0x00,0xf1,0x0f,0x00,0x90,0x09,0xf6,0x09,0xf7,0x6d,0x9f,0x00,0x97,0x60,0x06,0x70,0x4f,0x00,0x00,0x60,0x9f,0x00,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x90,0x0f,0x00,0x00,0x00,0x30,0x6f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00 },
	{ 0xf7,0x0b,0x00,0x10,0x03,0x00,0xaa,0xff,0x01,0x00,0xf6,0x09,0xf7,0x7c,0xbf,0x00,0x00,0x31,0xf3,0x0e,0x00,0x70,0xbf,0x90,0xfd,0x0d,0x70,0xfd,0x0d,0x00,0x00,0xf7,0x0b,0x00,0x10,0x03,0xf6,0x09,0xf7,0x1c,0xff,0x3c,0x31,0x00,0x00,0x90,0x2f,0x00,0x00,0x60,0x9f,0x00,0x0e,0xb1,0xcf,0xff,0xf9,0xdf,0x70,0xad,0xa0,0x7d,0x90,0x0f,0x40,0xef,0x9f,0xf3,0xef,0x0a,0xf8,0xff,0x17,0xfb,0xfe,0x0c,0x00,0xf0,0xff,0x96,0xff,0x0c,0xc6,0xf9,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00 },
	{ 0xf9,0x09,0x00,0x00,0x00,0x10,0x3f,0xf9,0x07,0x00,0xf6,0x7b,0xff,0x97,0x9f,0x00,0x00,0x00,0xf6,0x0d,0x00,0x60,0xdf,0x90,0xd9,0x6f,0xe0,0xf7,0x0d,0x00,0x00,0xf9,0x09,0x00,0x00,0x00,0xf6,0x7b,0xff,0x07,0xf7,0xff,0x09,0x00,0x00,0xf3,0x08,0x00,0x00,0x60,0xff,0xed,0x0f,0x81,0xbf,0xf3,0x6f,0xf8,0x06,0xdd,0x00,0x9f,0x90,0x0f,0xd0,0x0d,0xfb,0x60,0x6f,0x60,0x4f,0xd0,0x3f,0xf8,0x4a,0x03,0x00,0x70,0x0f,0xf6,0x24,0xae,0xf7,0x7b,0x00,0x00,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00 },
	{ 0xf9,0x09,0x00,0x00,0x00,0x80,0x9f,0xfb,0x0e,0x00,0xf6,0x9d,0x39,0x90,0x9f,0x00,0x00,0x00,0xf6,0x0d,0x00,0x60,0xdf,0x90,0x69,0xcf,0xf6,0xf0,0x0d,0x00,0x00,0xf9,0x09,0x00,0x00,0x00,0xf6,0x9d,0x39,0x00,0x10,0xfa,0xaf,0x00,0x10,0xcc,0x00,0x00,0x00,0x60,0x9f,0x10,0x0f,0x60,0x6f,0xd0,0x0d,0xf6,0x06,0xdd,0x00,0x9f,0x90,0x0f,0x70,0x77,0xfe,0x60,0x6f,0xc0,0x0f,0x60,0x9f,0xf6,0x06,0x00,0x00,0x70,0x0f,0xbb,0x00,0xf7,0xf7,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
	{ 0xf7,0x0c,0x00,0x00,0x00,0xf0,0x67,0xd6,0x4f,0x00,0xf6,0x09,0x00,0x70,0xcf,0x00,0x00,0x00,0xf0,0x0f,0x00,0x80,0x8f,0x90,0x09,0xfe,0x9d,0xf0,0x0d,0x00,0x00,0xf7,0x0c,0x00,0x00,0x00,0xf6,0x09,0x00,0x40,0x08,0x40,0xff,0x00,0xc1,0x1c,0x00,0x00,0x00,0x60,0x9f,0x00,0x14,0x63,0x6f,0xd0,0x0d,0xf6,0x06,0xdd,0x00,0x9f,0x90,0x0f,0x70,0xaf,0xfb,0x60,0x6f,0xd0,0x0f,0x10,0x9f,0xf6,0x06,0x00,0x00,0x70,0x0f,0xbb,0x00,0xf7,0xf7,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
	{ 0xe0,0x4f,0x00,0x70,0x0a,0xf7,0x00,0x70,0xbf,0x00,0xf6,0x09,0x00,0x00,0xfe,0x04,0x00,0xa7,0xa0,0x8f,0x00,0xf0,0x1f,0x90,0x09,0xf7,0x1f,0xf0,0x0d,0x00,0x00,0xe0,0x4f,0x00,0x70,0x0a,0xf6,0x09,0x00,0x60,0x1f,0x00,0xfa,0x00,0xc9,0x01,0x00,0x00,0x00,0x60,0x9f,0x00,0xc0,0x67,0x6f,0xd0,0x0d,0xf6,0x06,0xdd,0x10,0x9f,0x90,0x0f,0xf0,0x0a,0xf9,0x60,0x6f,0xa0,0x6f,0x60,0x6f,0xf6,0x06,0x00,0x00,0x70,0x0f,0xf8,0x00,0xcb,0xf7,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xfc },
	{ 0x40,0xff,0x69,0xda,0x61,0xcf,0x03,0x70,0xff,0x37,0xf9,0x4c,0x00,0x00,0xf4,0x9f,0xa6,0x1d,0x00,0xfb,0x79,0xfd,0x04,0xc4,0x4c,0xf0,0x1b,0xf7,0x6f,0x00,0x00,0x40,0xff,0x69,0xda,0x31,0xf9,0x4c,0x00,0x60,0xef,0x77,0x7f,0x80,0xff,0xff,0xbf,0x00,0x00,0xa3,0xef,0x99,0xfd,0x91,0x9f,0xf6,0x6f,0xf9,0x19,0xfb,0xea,0xff,0xc7,0x7f,0xf0,0xbf,0xff,0x4f,0xcf,0x1e,0xef,0xe7,0x1b,0xf9,0x1a,0x00,0x00,0x70,0x0f,0xd0,0xff,0x2f,0xf7,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0x0f,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0xf0,0xff },
	{ 0x00,0x71,0x99,0x07,0x40,0x66,0x03,0x60,0x66,0x36,0x66,0x46,0x00,0x00,0x10,0x97,0x79,0x00,0x00,0x40,0x99,0x17,0x00,0x64,0x46,0x30,0x11,0x66,0x66,0x00,0x00,0x00,0x71,0x99,0x07,0x30,0x66,0x46,0x00,0x30,0x76,0x99,0x06,0x30,0x44,0x44,0x34,0x00,0x00,0x63,0x66,0x66,0x46,0x61,0x66,0x66,0x66,0x66,0x16,0x81,0x39,0x49,0x63,0x66,0x40,0x89,0x96,0x04,0x97,0x03,0x81,0x79,0x10,0x66,0x16,0x00,0x00,0x00,0x00,0x00,0x76,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0xf0,0xf0 },
	{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
	{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 }
};

#elif (EMU_SYSTEM == MVS)

static const u8 ALIGN_DATA logo_data[14][104] = {
	{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
	{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
	{ 0xc6,0xad,0x00,0x90,0xbd,0x96,0xdd,0xdd,0xdd,0x04,0x40,0xfc,0xfe,0x09,0x00,0x00,0x00,0x70,0xfe,0xfd,0x9d,0x90,0xdd,0xdd,0xdd,0x04,0x40,0xfc,0xfe,0x09,0x00,0x00,0x00,0xb6,0xdd,0xdd,0xad,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf7,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x67,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0x0f,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00 },
	{ 0x10,0xff,0x08,0x00,0x6d,0x00,0xfd,0x00,0xf1,0x06,0xf4,0x1c,0x60,0xbf,0x00,0x00,0x00,0xf8,0x09,0x30,0xce,0x00,0xfd,0x00,0xf1,0x06,0xf4,0x1c,0x60,0xbf,0x00,0x00,0x00,0x60,0x9f,0x00,0xd8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x90,0x0f,0x00,0x00,0x00,0x00,0x49,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0xdf,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00 },
	{ 0x00,0xfd,0x6f,0x00,0x6d,0x00,0xfd,0x00,0x60,0x03,0xfe,0x03,0x00,0xfb,0x07,0x00,0x30,0xdf,0x00,0x00,0xd6,0x00,0xfd,0x00,0x60,0x03,0xfe,0x03,0x00,0xfb,0x07,0x00,0x00,0x60,0x9f,0x00,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x90,0x0f,0x00,0x00,0x00,0x30,0x6f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00 },
	{ 0x00,0x8d,0xff,0x01,0x6d,0x00,0xfd,0x00,0x97,0x30,0xef,0x00,0x00,0xf7,0x0b,0x00,0xa0,0x7f,0x00,0x00,0x00,0x00,0xfd,0x00,0x97,0x30,0xef,0x00,0x00,0xf7,0x0b,0x00,0x00,0x60,0x9f,0x00,0x0e,0xb1,0xcf,0xff,0xf9,0xdf,0x70,0xad,0xa0,0x7d,0x90,0x0f,0x40,0xef,0x9f,0xf3,0xef,0x0a,0xf8,0xff,0x17,0xfb,0xfe,0x0c,0x00,0x00,0xff,0x6f,0xf9,0xcf,0x60,0x9c,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00 },
	{ 0x00,0x6d,0xf7,0x0e,0x6d,0x00,0xfd,0xdd,0x9f,0x60,0xdf,0x00,0x00,0xf6,0x0d,0xb7,0xd4,0x6f,0x00,0xb3,0xdd,0x0a,0xfd,0xdd,0x9f,0x60,0xdf,0x00,0x00,0xf6,0x0d,0x00,0x00,0x60,0xff,0xed,0x0f,0x81,0xbf,0xf3,0x6f,0xf8,0x06,0xdd,0x00,0x9f,0x90,0x0f,0xd0,0x0d,0xfb,0x60,0x6f,0x60,0x4f,0xd0,0x3f,0xf8,0x4a,0x03,0x00,0x00,0xf7,0x60,0x4f,0xe2,0x7a,0xbf,0x07,0x00,0x00,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00 },
	{ 0x00,0x6d,0xa0,0xbf,0x6d,0x00,0xfd,0x00,0x98,0x60,0xdf,0x00,0x00,0xf6,0x0d,0xfb,0xd7,0x7f,0x00,0x10,0xef,0x00,0xfd,0x00,0x98,0x60,0xdf,0x00,0x00,0xf6,0x0d,0x00,0x00,0x60,0x9f,0x10,0x0f,0x60,0x6f,0xd0,0x0d,0xf6,0x06,0xdd,0x00,0x9f,0x90,0x0f,0x70,0x77,0xfe,0x60,0x6f,0xc0,0x0f,0x60,0x9f,0xf6,0x06,0x00,0x00,0x00,0xf7,0xb0,0x0b,0x70,0x7f,0x0f,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
	{ 0x00,0x6d,0x00,0xfd,0x6f,0x00,0xfd,0x00,0x31,0x04,0xff,0x00,0x00,0xf8,0x08,0x00,0x80,0xbf,0x00,0x00,0xdf,0x00,0xfd,0x00,0x31,0x04,0xff,0x00,0x00,0xf8,0x08,0x00,0x00,0x60,0x9f,0x00,0x14,0x63,0x6f,0xd0,0x0d,0xf6,0x06,0xdd,0x00,0x9f,0x90,0x0f,0x70,0xaf,0xfb,0x60,0x6f,0xd0,0x0f,0x10,0x9f,0xf6,0x06,0x00,0x00,0x00,0xf7,0xb0,0x0b,0x70,0x7f,0x0f,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
	{ 0x00,0x6d,0x00,0xf1,0x6f,0x00,0xfd,0x00,0x40,0x0e,0xfa,0x08,0x00,0xff,0x01,0x00,0x10,0xff,0x04,0x00,0xdf,0x00,0xfd,0x00,0x40,0x0e,0xfa,0x08,0x00,0xff,0x01,0x00,0x00,0x60,0x9f,0x00,0xc0,0x67,0x6f,0xd0,0x0d,0xf6,0x06,0xdd,0x10,0x9f,0x90,0x0f,0xf0,0x0a,0xf9,0x60,0x6f,0xa0,0x6f,0x60,0x6f,0xf6,0x06,0x00,0x00,0x00,0xf7,0x80,0x0f,0xb0,0x7c,0x0f,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xfc,0x00,0x00,0x00 },
	{ 0x60,0x9f,0x03,0x40,0x6f,0x70,0xff,0x9a,0xfa,0x08,0xb0,0x9f,0xd7,0x4f,0x00,0x00,0x00,0xf4,0x9f,0x96,0xcf,0x70,0xff,0x9a,0xfa,0x08,0xb0,0x9f,0xd7,0x4f,0x00,0x00,0x00,0xa3,0xef,0x99,0xfd,0x91,0x9f,0xf6,0x6f,0xf9,0x19,0xfb,0xea,0xff,0xc7,0x7f,0xf0,0xbf,0xff,0x4f,0xcf,0x1e,0xef,0xe7,0x1b,0xf9,0x1a,0x00,0x00,0x00,0xf7,0x00,0xfd,0xff,0x72,0x0f,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0x0f,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0xf0,0xff,0x00,0x00,0x00 },
	{ 0x60,0x66,0x03,0x00,0x37,0x60,0x66,0x66,0x66,0x01,0x00,0x94,0x79,0x01,0x00,0x00,0x00,0x00,0x97,0x99,0x04,0x60,0x66,0x66,0x66,0x01,0x00,0x94,0x79,0x01,0x00,0x00,0x00,0x63,0x66,0x66,0x46,0x61,0x66,0x66,0x66,0x66,0x16,0x81,0x39,0x49,0x63,0x66,0x40,0x89,0x96,0x04,0x97,0x03,0x81,0x79,0x10,0x66,0x16,0x00,0x00,0x00,0x00,0x00,0x60,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0xf0,0xf0,0x00,0x00,0x00 },
	{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
	{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 }
};

#elif (EMU_SYSTEM == NCDZ)

static const u8 ALIGN_DATA logo_data[14][116] = {
	{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
	{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
	{ 0xc6,0xad,0x00,0x90,0xbd,0x96,0xdd,0xdd,0xdd,0x04,0x40,0xfc,0xfe,0x09,0x00,0x00,0x00,0x70,0xfe,0xfd,0x9d,0x90,0xdd,0xdd,0xdd,0x04,0x40,0xfc,0xfe,0x09,0x00,0x00,0x00,0x90,0xef,0xcf,0x0f,0xc7,0xdd,0xdd,0x39,0x00,0xd0,0xdd,0xdd,0xad,0x00,0x00,0xb6,0xdd,0xdd,0xad,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf7,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x67,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0x0f,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00 },
	{ 0x10,0xff,0x08,0x00,0x6d,0x00,0xfd,0x00,0xf1,0x06,0xf4,0x1c,0x60,0xbf,0x00,0x00,0x00,0xf8,0x09,0x30,0xce,0x00,0xfd,0x00,0xf1,0x06,0xf4,0x1c,0x60,0xbf,0x00,0x00,0x00,0xfb,0x07,0x80,0x3f,0x90,0x7f,0x70,0xff,0x07,0xf4,0x01,0xf1,0x4f,0x00,0x00,0x60,0x9f,0x00,0xd8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x90,0x0f,0x00,0x00,0x00,0x00,0x49,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0xdf,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00 },
	{ 0x00,0xfd,0x6f,0x00,0x6d,0x00,0xfd,0x00,0x60,0x03,0xfe,0x03,0x00,0xfb,0x07,0x00,0x30,0xdf,0x00,0x00,0xd6,0x00,0xfd,0x00,0x60,0x03,0xfe,0x03,0x00,0xfb,0x07,0x00,0x60,0xcf,0x00,0x00,0x6d,0x90,0x6f,0x00,0xf4,0x1f,0x74,0x00,0xfb,0x09,0x00,0x00,0x60,0x9f,0x00,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x90,0x0f,0x00,0x00,0x00,0x30,0x6f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00 },
	{ 0x00,0x8d,0xff,0x01,0x6d,0x00,0xfd,0x00,0x97,0x30,0xef,0x00,0x00,0xf7,0x0b,0x00,0xa0,0x7f,0x00,0x00,0x00,0x00,0xfd,0x00,0x97,0x30,0xef,0x00,0x00,0xf7,0x0b,0x00,0xb0,0x7f,0x00,0x00,0x13,0x90,0x6f,0x00,0xc0,0x7f,0x00,0x70,0xef,0x00,0x00,0x00,0x60,0x9f,0x00,0x0e,0xb1,0xcf,0xff,0xf9,0xdf,0x70,0xad,0xa0,0x7d,0x90,0x0f,0x40,0xef,0x9f,0xf3,0xef,0x0a,0xf8,0xff,0x17,0xfb,0xfe,0x0c,0x00,0x00,0xff,0x6f,0xf9,0xcf,0x60,0x9c,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00 },
	{ 0x00,0x6d,0xf7,0x0e,0x6d,0x00,0xfd,0xdd,0x9f,0x60,0xdf,0x00,0x00,0xf6,0x0d,0xb7,0xd4,0x6f,0x00,0xb3,0xdd,0x0a,0xfd,0xdd,0x9f,0x60,0xdf,0x00,0x00,0xf6,0x0d,0x00,0xd0,0x6f,0x00,0x00,0x00,0x90,0x6f,0x00,0x90,0x9f,0x00,0xf1,0x4f,0x00,0x00,0x00,0x60,0xff,0xed,0x0f,0x81,0xbf,0xf3,0x6f,0xf8,0x06,0xdd,0x00,0x9f,0x90,0x0f,0xd0,0x0d,0xfb,0x60,0x6f,0x60,0x4f,0xd0,0x3f,0xf8,0x4a,0x03,0x00,0x00,0xf7,0x60,0x4f,0xe2,0x7a,0xbf,0x07,0x00,0x00,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00 },
	{ 0x00,0x6d,0xa0,0xbf,0x6d,0x00,0xfd,0x00,0x98,0x60,0xdf,0x00,0x00,0xf6,0x0d,0xfb,0xd7,0x7f,0x00,0x10,0xef,0x00,0xfd,0x00,0x98,0x60,0xdf,0x00,0x00,0xf6,0x0d,0x00,0xd0,0x6f,0x00,0x00,0x00,0x90,0x6f,0x00,0xa0,0x9f,0x00,0xfd,0x08,0x00,0x00,0x00,0x60,0x9f,0x10,0x0f,0x60,0x6f,0xd0,0x0d,0xf6,0x06,0xdd,0x00,0x9f,0x90,0x0f,0x70,0x77,0xfe,0x60,0x6f,0xc0,0x0f,0x60,0x9f,0xf6,0x06,0x00,0x00,0x00,0xf7,0xb0,0x0b,0x70,0x7f,0x0f,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
	{ 0x00,0x6d,0x00,0xfd,0x6f,0x00,0xfd,0x00,0x31,0x04,0xff,0x00,0x00,0xf8,0x08,0x00,0x80,0xbf,0x00,0x00,0xdf,0x00,0xfd,0x00,0x31,0x04,0xff,0x00,0x00,0xf8,0x08,0x00,0xa0,0x8f,0x00,0x00,0x00,0x90,0x6f,0x00,0xf0,0x4f,0x80,0xdf,0x00,0x40,0x00,0x00,0x60,0x9f,0x00,0x14,0x63,0x6f,0xd0,0x0d,0xf6,0x06,0xdd,0x00,0x9f,0x90,0x0f,0x70,0xaf,0xfb,0x60,0x6f,0xd0,0x0f,0x10,0x9f,0xf6,0x06,0x00,0x00,0x00,0xf7,0xb0,0x0b,0x70,0x7f,0x0f,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
	{ 0x00,0x6d,0x00,0xf1,0x6f,0x00,0xfd,0x00,0x40,0x0e,0xfa,0x08,0x00,0xff,0x01,0x00,0x10,0xff,0x04,0x00,0xdf,0x00,0xfd,0x00,0x40,0x0e,0xfa,0x08,0x00,0xff,0x01,0x00,0x30,0xff,0x01,0x00,0x7b,0x90,0x6f,0x00,0xfb,0x0c,0xf3,0x1f,0x00,0xf1,0x00,0x00,0x60,0x9f,0x00,0xc0,0x67,0x6f,0xd0,0x0d,0xf6,0x06,0xdd,0x10,0x9f,0x90,0x0f,0xf0,0x0a,0xf9,0x60,0x6f,0xa0,0x6f,0x60,0x6f,0xf6,0x06,0x00,0x00,0x00,0xf7,0x80,0x0f,0xb0,0x7c,0x0f,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xfc },
	{ 0x60,0x9f,0x03,0x40,0x6f,0x70,0xff,0x9a,0xfa,0x08,0xb0,0x9f,0xd7,0x4f,0x00,0x00,0x00,0xf4,0x9f,0x96,0xcf,0x70,0xff,0x9a,0xfa,0x08,0xb0,0x9f,0xd7,0x4f,0x00,0x00,0x00,0xf7,0x7f,0xc7,0x0a,0xc4,0xcf,0xe9,0xaf,0x01,0xfe,0x9d,0x99,0xdf,0x00,0x00,0xa3,0xef,0x99,0xfd,0x91,0x9f,0xf6,0x6f,0xf9,0x19,0xfb,0xea,0xff,0xc7,0x7f,0xf0,0xbf,0xff,0x4f,0xcf,0x1e,0xef,0xe7,0x1b,0xf9,0x1a,0x00,0x00,0x00,0xf7,0x00,0xfd,0xff,0x72,0x0f,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0x0f,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0xf0,0xff },
	{ 0x60,0x66,0x03,0x00,0x37,0x60,0x66,0x66,0x66,0x01,0x00,0x94,0x79,0x01,0x00,0x00,0x00,0x00,0x97,0x99,0x04,0x60,0x66,0x66,0x66,0x01,0x00,0x94,0x79,0x01,0x00,0x00,0x00,0x30,0x98,0x49,0x00,0x64,0x66,0x66,0x00,0x00,0x66,0x66,0x66,0x36,0x00,0x00,0x63,0x66,0x66,0x46,0x61,0x66,0x66,0x66,0x66,0x16,0x81,0x39,0x49,0x63,0x66,0x40,0x89,0x96,0x04,0x97,0x03,0x81,0x79,0x10,0x66,0x16,0x00,0x00,0x00,0x00,0x00,0x60,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0xf0,0xf0 },
	{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
	{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 }
};

#endif