#include "WPJAppDelegate.h"
#include <random>

#include "WPJTest.h"
#include "WPJIntervalAction.h"
#include "WPJActionManager.h"
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

	// Set FPS, default value is 1.0/60
	t_pDirector->SetAnimationInterval(1.0 / 60);

	// User customed init
	if (!ExtendInit())
	{
		WPJLOG("[%s] WPJAppDelegate ... error in ExtendInit\n", _D_NOW_TIME__);
		return false;
	}	
	
	// Init ALGO
	if (!WPJALGOManager::GetSharedInst()->InitALGO())
	{
		WPJLOG("[%s] WPJAppDelegate ... error in InitALGO\n", _D_NOW_TIME__);
		return false;
	}

	// Init Scene
	WPJScene *t_pScene = WPJScene::CreateNewObject();
	t_pDirector->RunWithScene(t_pScene);
	t_pScene->Release();

	return true;
}

bool WPJAppDelegate::ExtendInit()
{
	WPJALGOManager *t_pALGOMgr = WPJALGOManager::GetSharedInst();

	t_pALGOMgr->SetWndSize(800, 600);
	t_pALGOMgr->SetWndName(HString("²âÊÔ´°¿Ú"));

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

	/************************************************************************/
	/* Test Area                                                            */
	/************************************************************************/
	
	WPJNode *node = WPJNodeTest::CreateNewObject();
	node->SetPosition(WPJPoint(10,5));
	WPJMoveTo *moveByAction = WPJMoveTo::Create(5, WPJPoint(20,-10));
	
	node->RunAction(moveByAction);

	/************************************************************************/
	/* Test Area End                                                        */
	/************************************************************************/

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

			// Only For Test
			if (!moveByAction->IsDone())
				WPJLOG("[%s]Node Position (%f, %f)\n",
					_D_NOW_TIME__,
					node->GetPosition().x,
					node->GetPosition().y\
				);

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