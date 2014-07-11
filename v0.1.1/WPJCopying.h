#ifndef _H_WPJCOPYING
#define _H_WPJCOPYING

#include "WPJMacros.h"
#include "WPJZone.h"

NS_WPJ_BEGIN

class WPJObject;

class WPJCopying
{
	virtual WPJObject* DupCopy();
	virtual WPJObject* DupCopy(WPJZone *zone);
};

NS_WPJ_END

#endif