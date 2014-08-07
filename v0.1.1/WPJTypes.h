#ifndef _H_WPJTYPES
#define _H_WPJTYPES

#include "WPJStdafx.h"
#include "WPJMacros.h"
#include "WPJALGOManager.h"

NS_WPJ_BEGIN

/**
 *	wpColor3B contains rgb value, you can use wpc3() to create a wpColor3B
 */

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

/**
 *	wpColor4B contains rgb and alpha value, you can use wpc4() to create a wpColor4B
 */

class wpColor4B
{
public:
	U_CHAR r;
	U_CHAR g;
	U_CHAR b;
	U_CHAR alpha;

	wpColor4B() { }
	wpColor4B(const U_CHAR _r, const U_CHAR _g, const U_CHAR _b, const U_CHAR _alpha)
		:r(_r),g(_g),b(_b),alpha(_alpha) { }
};

static inline wpColor4B wpc4(const U_CHAR r, const U_CHAR g, const U_CHAR b, const U_CHAR alpha)
{
	wpColor4B c(r, g, b, alpha);
	return c;
}

static inline wpColor4B wpc4(const wpColor3B &rgb, const U_CHAR alpha)
{
	wpColor4B c(rgb.r, rgb.g, rgb.b, alpha);
	return c;
}


/**
 *	wpBlendFunc contains basic opengl blend params, you can use def_blend, new_blend or wpbf3
 *	to get a blendfunc
 */

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