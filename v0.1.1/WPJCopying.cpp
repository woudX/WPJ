#include "WPJCopying.h"

USING_NS_WPJ;

WPJObject* WPJCopying::DupCopy()
{
	return NULL;
}

WPJObject *WPJCopying::DupCopy(WPJZone *zone)
{
	UN_USED_PARAM(zone);
	WPJLOG("[%s] WPJcopying is not implement\n");
	ASSERT(0);

	return NULL;
}