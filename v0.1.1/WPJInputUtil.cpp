#include "WPJInputUtil.h"

USING_NS_WPJ

WPJInputUtil *WPJInputUtil::m_pInst = 0;

WPJInputUtil::WPJInputUtil():m_bFirst(true)
{
	memset(m_arKeyPressed, 0, sizeof(m_arKeyPressed));
	
}

WPJInputUtil *WPJInputUtil::GetSharedInst()
{
	if (m_pInst == 0)
		m_pInst = new WPJInputUtil();
	return m_pInst;
}

WPJInputUtil *WPJInputUtil::RegistDisplay(ALLEGRO_DISPLAY *pDisplay)
{
	m_pDisplay = pDisplay;
	return this;
}

WPJInputUtil *WPJInputUtil::UnregistDisplay()
{
	m_pDisplay = NULL;
	return this;
}

bool WPJInputUtil::Init()
{
	int bRet;

	//	init input hardware driver
	bRet = al_is_keyboard_installed() && al_is_mouse_installed();

	//	init event_queue
	m_pEventQueue = al_create_event_queue();
	if (bRet && m_pEventQueue)
	{
		al_register_event_source(m_pEventQueue, al_get_keyboard_event_source());
		al_register_event_source(m_pEventQueue, al_get_mouse_event_source());
		al_register_event_source(m_pEventQueue, al_get_display_event_source(m_pDisplay));
	}

	return bRet;
}

int WPJInputUtil::PeekEvent(ALLEGRO_EVENT &e)
{
	return al_wait_for_event_timed(m_pEventQueue, &e, 0.001f);
}

void WPJInputUtil::AnalysisEvent(ALLEGRO_EVENT &e)
{
	//	key pressed
	if (e.type == ALLEGRO_EVENT_KEY_DOWN)
		m_arKeyPressed[e.keyboard.keycode] = true;
	else if (e.type == ALLEGRO_EVENT_KEY_UP)
		m_arKeyPressed[e.keyboard.keycode] = false;

	//	event trigged
	if (e.type == ALLEGRO_EVENT_KEY_DOWN
		||	e.type == ALLEGRO_EVENT_KEY_UP
		||	e.type == ALLEGRO_EVENT_KEY_CHAR)
	{
		ALLEGRO_EVENT copyE = e;

		WPJEvent *pEvent = new WPJEvent(copyE, e.type);
		m_lTriggedEvents.push_back(pEvent);
	}	
}

bool WPJInputUtil::IsKeyPressed(int keyID)
{
	if (keyID < MAX_INPUT_SIZE)
		return m_arKeyPressed[keyID];
	else
	{
		//WPJLOG("[%s] There is no keyID = %ud, please change MAX_INPUT_SIZE\n", _D_NOW_TIME__, keyID);
		ASSERT(false);
		return false;
	}
}

WPJEvent *WPJInputUtil::NextTriggedEvent()
{
	WPJEvent *bRet = NULL;

	if (m_lTriggedEvents.size() > 0)
	{
		if (m_bFirst)
		{
			m_itNextEvent = m_lTriggedEvents.begin();
			m_bFirst = false;
		}
		else
			m_itNextEvent++;

		if (m_itNextEvent != m_lTriggedEvents.end())
			bRet = pp(m_itNextEvent);
	}
	
	return bRet;
}

void WPJInputUtil::ClearAllTriggedEvents()
{
	foreach_in_list_auto(WPJEvent*, itor, m_lTriggedEvents)
		ptr_safe_del(pp(itor));
	m_lTriggedEvents.clear();

	m_bFirst = true;
}

WPJInputUtil::~WPJInputUtil()
{
	ClearAllTriggedEvents();

	if (al_is_keyboard_installed())
		al_unregister_event_source(m_pEventQueue, al_get_keyboard_event_source());

	if (al_is_mouse_installed())
		al_unregister_event_source(m_pEventQueue, al_get_mouse_event_source());

	al_destroy_event_queue(m_pEventQueue);
}