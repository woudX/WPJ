#ifndef _H_WPJINPUT_UTIL
#define _H_WPJINPUT_UTIL

#include "WPJStdafx.h"
#include "WPJMacros.h"

#include "WPJEventRoute.h"
#include <allegro5/allegro.h>

NS_WPJ_BEGIN

const unsigned int MAX_INPUT_SIZE = 256;

class WPJInputUtil
{
public:
	static WPJInputUtil *GetSharedInst();

	//	Reg/Unreg Display
	//	This method must be called before Init();
	WPJInputUtil *RegistDisplay(ALLEGRO_DISPLAY *pDisplay);
	WPJInputUtil *UnregistDisplay();

	//	Init input util config
	bool Init();

	/**
	 *	Base Methods
	 */

	//	Get a event from input, return false if e is NULL
	int PeekEvent(ALLEGRO_EVENT &e);
	//	analysis event info for other use
	void AnalysisEvent(ALLEGRO_EVENT &e);


	/**
	 *	Info Interface, with these interfaces you can get some useful infos
	 *	about what has been done, include :
	 *	-	PRESSED_KEY
	 *	-	TRIGGED_EVENT
	 *	-	...
	 */

	//	return a bool, which means if a key pressed
	bool IsKeyPressed(int keyID);

	//	return events by trigged order , return null if there is no event any more
	WPJEvent *NextTriggedEvent();

	//	clear all events
	void ClearAllTriggedEvents();

	~WPJInputUtil();

protected:
	WPJInputUtil();

private:
	static WPJInputUtil *m_pInst;
	ALLEGRO_EVENT_QUEUE *m_pEventQueue;
	ALLEGRO_DISPLAY *m_pDisplay;

	int m_arKeyPressed[MAX_INPUT_SIZE];
	std::list<WPJEvent *> m_lTriggedEvents;
	std::list<WPJEvent *>::iterator m_itNextEvent;
	bool m_bFirst;
};

NS_WPJ_END

#endif // !_H_WPJINPUT_UTIL
