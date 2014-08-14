#include "WPJEventRoute.h"
#include "WPJObject.h"
USING_NS_WPJ

/// WPJEventRoute
//////////////////////////////////////////////////////////////////////////

WPJEventRoute::WPJEventRoute():bFocused(false)
{

}

void WPJEventRoute::RegistEventHandler(SEL_EVENTHANDLER pEventHandler, WPJ_EVENT_TYPE iType, bool bRewrite /* = false */)
{
	std::map<int, SEL_EVENTHANDLER>::iterator itor = m_mpEventRouteMap.find(iType);
	bool bFind = !(itor == m_mpEventRouteMap.end());

	//	Regist event handler
	if (!bFind || bRewrite && bFind)
	{
		m_mpEventRouteMap.insert(std::make_pair(iType, pEventHandler));
	}
}

void WPJEventRoute::UnRegistEvent(WPJ_EVENT_TYPE iType)
{
	m_mpEventRouteMap.erase(iType);
}

void WPJEventRoute::RunEvent(WPJEvent *e, WPJObject *pOwner)
{
	//	this event cannot be run again
	if (!(e->isBubble) && e->runTimes > 0)
		return ;

	std::map<int, SEL_EVENTHANDLER>::iterator itor = m_mpEventRouteMap.find(e->type);
	if (itor != m_mpEventRouteMap.end())
	{
		SEL_EVENTHANDLER pHandler = itor->second;
		(pOwner->*pHandler)(e);

		++(e->runTimes);
	}
}

WPJEventRoute::~WPJEventRoute()
{

}