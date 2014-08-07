#ifndef _H_WPJTYPES
#define _H_WPJTYPES

#include "WPJStdafx.h"
#include "WPJMacros.h"
#include "WPJALGOManager.h"

NS_WPJ_BEGIN

class wpColor3B
{
public:
	U_CHAR r;
	U_CHAR g;
	U_CHAR b;
	
	wpColor3B() {}
	wpColor3B(const U_CHAR _r, const U_CHAR _g, const U_CHAR _b)
		:r(_r),g(_g),b(_b) { }
};

static inline wpColor3B wpc3(const U_CHAR r, const U_CHAR g, const U_CHAR b)
{
	wpColor3B c(r, g, b);
	return c;
}

class wpBlendFunc
{
public:
	U_CHAR func;
	U_CHAR src;
	U_CHAR dest;

	wpBlendFunc() {}
	wpBlendFunc(U_CHAR ucFunc, U_CHAR ucSrc, U_CHAR ucDest)
		:func(ucFunc),src(ucSrc),dest(ucDest) { }
};

#define def_blend wpBlendFunc(AL_FUNC_ADD, AL_SRC_ALPHA, AL_ONE_MINUS_SRC_ALPHA)
#define new_blend(func,src,dest) wpBlendFunc(func, src, dest)
static inline wpBlendFunc wpbf3(const U_CHAR ucFunc, const U_CHAR ucSrc, const U_CHAR ucDest)
{
	wpBlendFunc bf(ucFunc, ucSrc, ucDest);
	return bf;
}


NS_WPJ_END

#endif