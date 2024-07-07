/******************************************************************************

	psp.c

	PSP���C��

******************************************************************************/

#ifndef PSP_MAIN_H
#define PSP_MAIN_H

#ifndef MAX_PATH
#define MAX_PATH 256
#endif

#include "emucfg.h"

#include <psptypes.h>
#include <pspaudio.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <pspgu.h>
#include <pspiofilemgr.h>
#include <pspkernel.h>
#include <psppower.h>
#include <psprtc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <sys/unistd.h>

#include "psp/ui_text.h"
#include "psp/config.h"
#include "psp/filer.h"
#include "psp/input.h"
#include "psp/ticker.h"
#include "psp/ui.h"
#include "psp/ui_draw.h"
#include "psp/ui_menu.h"
#include "psp/video.h"
#include "psp/sound.h"
#include "psp/png.h"
#ifdef ADHOC
#include "psp/adhoc.h"
#endif
#if (EMU_SYSTEM == NCDZ)
#include "psp/mp3.h"
#endif
#if PSP_VIDEO_32BPP
#include "psp/wallpaper.h"
#endif

enum
{
	LOOP_EXIT = 0,
	LOOP_BROWSER,
	LOOP_RESTART,
	LOOP_RESET,
	LOOP_EXEC
};

enum
{
	PSPCLOCK_222 = 0,
	PSPCLOCK_266,
	PSPCLOCK_333,
	PSPCLOCK_MAX
};

extern volatile int Loop;
extern volatile int Sleep;
extern char launchDir[MAX_PATH];
extern int psp_cpuclock;
#ifdef KERNEL_MODE
extern volatile u32 home_button;
#endif

void set_cpu_clock(int value);

#endif /* PSP_MAIN_H */