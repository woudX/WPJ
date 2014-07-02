#ifndef _H_WPJSTDC
#define _H_WPJSTDC

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>

#ifndef __MINGW32__

#define MAX		std::max
#define MIN		std::min

#else

#ifndef MIN
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif

#ifndef MAX
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif

#endif // !__MINGW32__


#endif