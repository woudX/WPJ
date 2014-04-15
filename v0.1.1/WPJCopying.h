#ifndef _H_WPJCOPYING
#define _H_WPJCOPYING

#include "WPJMacros.h"

NS_WPJ_BEGIN

class WPJObject;

class WPJCopying
{
	virtual WPJObject* DupCopy();
};

NS_WPJ_END

#endif