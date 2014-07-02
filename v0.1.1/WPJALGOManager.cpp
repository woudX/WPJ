#include "WPJALGOManager.h"

USING_NS_WPJ

WPJALGOManager *WPJALGOManager::m_pALGOManager = 0;

WPJALGOManager *WPJALGOManager::GetSharedInst()
{
	if (m_pALGOManager == 0)
		m_pALGOManager = new WPJALGOManager;
	return m_pALGOManager;
}

WPJALGOManager::WPJALGOManager()
:m_obWndSize(WPJSize(640, 480))
,m_obWndName("WPJEngineTest")
,m_pDisplay(NULL)
{

}

void WPJALGOManager::SetWndName(HString var)
{
	m_obWndName = var;
}

HString &WPJALGOManager::GetWndName()
{
	return m_obWndName;
}

void WPJALGOManager::SetWndSize(WPJSize var)
{
	m_obWndSize = var;
}

void WPJALGOManager::SetWndSize(int width, int height)
{
	m_obWndSize.width = width;
	m_obWndSize.height = height;
}

WPJSize &WPJALGOManager::GetWndSize()
{
	return m_obWndSize;
}

bool WPJALGOManager::InitALGO()
{
	// Intialize allegro system
	if (!al_init()) 
	{
		WPJLOG("[%s] Error in %s(%s) ... Failed to initialize allegro\n", _D_NOW_TIME__, __FILE__, __LINE__);
		return false;
	}
	al_install_mouse();
	al_install_keyboard();
	al_init_primitives_addon();
	al_init_image_addon();

	// Initialize allegro display
	m_pDisplay = al_create_display(m_obWndSize.width, m_obWndSize.height);
	if (!m_pDisplay)
	{
		WPJLOG("[%s] Error in %s(%s) ... Failed to create display\n", _D_NOW_TIME__, __FILE__, __LINE__);
		return false;
	}

	// Initialize window params
	al_set_window_title(m_pDisplay, m_obWndName.c_str());
	al_clear_to_color(al_map_rgb(0,0,0));

	// Initialize Allegro event queue
	m_pEventQueue = al_create_event_queue();
	al_register_event_source(m_pEventQueue, al_get_keyboard_event_source());
	al_register_event_source(m_pEventQueue, al_get_mouse_event_source());
	al_register_event_source(m_pEventQueue, al_get_display_event_source(m_pDisplay));

	// Show
	al_flip_display();

	return true;
}

void WPJALGOManager::DestroyALGO()
{
	al_destroy_display(m_pDisplay);
}

bool WPJALGOManager::IsALGOReady()
{
	return m_pDisplay;
}

bool WPJALGOManager::WaitForEvent(ALLEGRO_EVENT& e)
{
	return al_wait_for_event_timed(m_pEventQueue, &e, 0.001f);
}

WPJALGOManager::~WPJALGOManager()
{

}

