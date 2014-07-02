#ifndef _APPMACROS
#define _APPMACROS

#include "WPJLib.h"

/// WPJALGO Params
//////////////////////////////////////////////////////////////////////////

#define	DESIGN_RESOLUTION_800X600	0
#define DESIGN_RESOLUTION_1024X768	1
#define	DESIGN_RESOLUTION_1366X768	2
#define DESIGN_RESOLUTION_CUSTOM	3

//	if you want to change resolution, please modify TARGET_DESIGN_RESOLUTION value
//	and you can set your own resolution by modify DESIGN_RESOLUTION_CUSTOM value
#define TARGET_DESIGN_RESOLUTION	DESIGN_RESOLUTION_1024X768

#if (TARGET_DESIGN_RESOLUTION == DESIGN_RESOLUTION_800X600)
static wpj_engine::WPJSize designResolutionSize = wpj_engine::WPJSize(800, 600);
#elif (TARGET_DESIGN_RESOLUTION == DESIGN_RESOLUTION_1024X768)
static wpj_engine::WPJSize designResolutionSize = wpj_engine::WPJSize(1024, 768);
#elif (TARGET_DESIGN_RESOLUTION == DESIGN_RESOLUTION_1366X768)
static wpj_engine::WPJSize designResolutionSize = wpj_engine::WPJSize(1366, 768);
#elif (TARGET_DESIGN_RESOLUTION == DESIGN_RESOLUTION_CUSTOM)
static wpj_engine::WPJSize designResolutionSize = wpj_engine::WPJSize(2048, 1024);
#endif

#endif
