#include "WPJALGOManager.h"
#include "WPJLib.h"
#include "WPJInputUtil.h"

USING_NS_WPJ

WPJALGOManager *WPJALGOManager::m_pALGOManager = 0;

WPJALGOManager *WPJALGOManager::GetSharedInst()
{
	if (m_pALGOManager == 0)
		m_pALGOManager = new WPJALGOManager;
	return m_pALGOManager;
}

WPJALGOManager::WPJALGOManager()
:m_obWndName("WPJEngineTest")
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
	m_pDisplay = al_create_display(m_obScreenSize.width * m_fFrameZoomFactor, m_obScreenSize.height * m_fFrameZoomFactor);
	if (!m_pDisplay)
	{
		WPJLOG("[%s] Error in %s(%s) ... Failed to create display\n", _D_NOW_TIME__, __FILE__, __LINE__);
		return false;
	}

	// Initialize allegro input
	WPJInputUtil::GetSharedInst()->RegistDisplay(m_pDisplay)->Init();

	// Initialize window params
	al_set_window_title(m_pDisplay, m_obWndName.c_str());
	al_clear_to_color(al_map_rgb(0,0,0));

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

