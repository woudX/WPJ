#include "WPJAppDelegate.h"

USING_NS_WPJ

WPJAppDelegate *WPJAppDelegate::m_pAppDelegate = 0;

WPJAppDelegate *WPJAppDelegate::GetSharedInst()
{
	if (m_pAppDelegate == 0)
		m_pAppDelegate = new WPJAppDelegate;

	return m_pAppDelegate;
}

WPJAppDelegate::WPJAppDelegate()
{

}

void WPJAppDelegate::SetAnimationInterval(double interval)
{
	LARGE_INTEGER t_obFreq;
	QueryPerformanceFrequency(&t_obFreq);
	m_liAnimationInterval.QuadPart = static_cast<LONGLONG>(t_obFreq.QuadPart * interval);
}

bool WPJAppDelegate::Initialization()
{
	WPJDirector *t_pDirector = WPJDirector::GetSharedInst();
	WPJALGOManager *t_pALGOMgr = t_pDirector->GetALGOManager();

	t_pALGOMgr->SetWndSize(800, 600);
	t_pALGOMgr->SetWndName(HString("²âÊÔ´°¿Ú"));
	t_pALGOMgr->InitALGO();

	SetAnimationInterval(1.0 / 60);
	

	return true;
}

int WPJAppDelegate::Run()
{
	LARGE_INTEGER t_obLILast;
	LARGE_INTEGER t_obLINow;
	ALLEGRO_EVENT e;

	QueryPerformanceCounter(&t_obLILast);

	if (!Initialization())
	{
		WPJLOG("[%s] Error ... WPJAppDelegation init failed!\n", _D_NOW_TIME__);
		return 0;
	}

	while (1) 
	{
		
		if ( WPJALGOManager::GetSharedInst()->WaitForEvent(e))
		{
			// Event Handle
			if (e.type == ALLEGRO_EVENT_KEY_DOWN)
				if (e.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				{
					// Release all
					Exit();
					break;
				}
				else
					WPJLOG("[%s] ´Ó¼üÅÌÊäÈë ... %d\n", _D_NOW_TIME__, e.keyboard.keycode);
		}

		// Calculate if go into mainloop
		QueryPerformanceCounter(&t_obLINow);

		if (t_obLINow.QuadPart - t_obLILast.QuadPart > m_liAnimationInterval.QuadPart)
		{
			t_obLILast.QuadPart = t_obLINow.QuadPart;

			// Run MainLoop
			WPJDirector::GetSharedInst()->MainLoop();
		}
		else
		{
			Sleep(0);
		}	
	}

	return 0;
}

int WPJAppDelegate::Exit()
{
	WPJALGOManager::GetSharedInst()->DestroyALGO();
	delete WPJALGOManager::GetSharedInst();
	delete WPJDirector::GetSharedInst();
	return 0;
}