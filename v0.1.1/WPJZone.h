#ifndef _H_WPJZONE
#define _H_WPJZONE

#include "WPJStdafx.h"
#include "WPJMacros.h"

NS_WPJ_BEGIN

class WPJObject;

class WPJZone
{
public:
	WPJObject *m_pCopyZone;
	WPJZone(WPJObject *pCopyZone) { m_pCopyZone = pCopyZone; }
};

NS_WPJ_END

#endif