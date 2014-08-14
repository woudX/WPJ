#ifndef _H_WPJEVENTROUTE
#define _H_WPJEVENTROUTE

#include "WPJStdafx.h"
#include "WPJMacros.h"

#include "WPJObject.h"
#include <allegro5/allegro.h>

NS_WPJ_BEGIN
typedef unsigned int WPJ_EVENT_TYPE;

class WPJEvent
{
public:
	WPJEvent():isBubble(true) { }
	WPJEvent(ALLEGRO_EVENT &obE, int iType):isBubble(true),runTimes(0)
	{
		e = obE;
		type = iType;
	}
	WPJEvent(int iType):isBubble(true),runTimes(0)
	{
		type = iType;
	}

	void ForbidBubble() { isBubble = false; }

	ALLEGRO_EVENT e;	//	Event source
	bool isBubble;		//	Default true, when false this event can't bubble
	int runTimes;		//	Record use times
	int type;			//	Event type
};

//	Create a event
static inline WPJEvent new_event(ALLEGRO_EVENT &e, int type)
{
	return WPJEvent(e, type);
}



/**
 *	--- Notice --- Not Used Now!!!!!!!!!!!!
 *	WPJEventHandler save the method handler and it's owner
 */

class WPJEventHandler
{
public:
	WPJEventHandler() { }
	WPJEventHandler(SEL_EVENTHANDLER eventHandler, WPJObject *object)
		:pEventHandler(eventHandler),pEventOwner(object) { }

	SEL_EVENTHANDLER pEventHandler;
	WPJObject *pEventOwner;
};

static inline WPJEventHandler new_event_handler(SEL_EVENTHANDLER eventHandler, WPJObject *object)
{
	WPJEventHandler eh(eventHandler, object);
	return eh;
}

/**
 *	WPJEventRoute save the route info about event, when keyboard or mouse event
 *	occured, these route event will be called automatically
 */

class WPJEventRoute
{
public:
	WPJEventRoute();

	//	Regist a event handler with type, you can see WPJ_EVENT_TYPE to check
	//	types that are supported by WPJ
	void RegistEventHandler(SEL_EVENTHANDLER pEventHandler, WPJ_EVENT_TYPE iType, bool bRewrite = false);
	void UnRegistEvent(WPJ_EVENT_TYPE iType);
	void RunEvent(WPJEvent *e, WPJObject *pOwner);

	bool bFocused;	//	can be focused

	virtual ~WPJEventRoute();
protected:
	std::map<int, SEL_EVENTHANDLER> m_mpEventRouteMap;	//	Route map
	
};

NS_WPJ_END

#endif // !_H_WPJEVENTROUTE
