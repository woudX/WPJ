#include "WPJAppDelegate.h"
#include <random>

#include "WPJTest.h"
#include "WPJIntervalAction.h"
#include "WPJActionManager.h"
#include "WPJSprite.h"
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
	t_pALGOMgr->SetWndName(HString("测试窗口"));

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

	// 初始化精灵1
	WPJMoveTo *moveByAction = WPJMoveTo::Create(5, WPJPoint(300,500));
	WPJSprite *sprite = WPJSprite::Create();
	sprite->InitWithFile("white.png");
	sprite->SetPosition(WPJPoint(100,50));
	sprite->RunAction(moveByAction);

	// 初始化精灵2
	WPJMoveTo *moveByAction_2 = WPJMoveTo::Create(5, WPJPoint(400, -50));
	WPJSprite *sprite_2 = WPJSprite::Create();
	sprite_2->InitWithFile("white.png");
	sprite_2->UpdateDisplayColor(wpColor3B(255,0,0));
	sprite_2->SetCoordinateSystem(WPJ_COORDINATE_RELATIVE);
	sprite_2->SetPosition(WPJPoint(100,50));
	sprite_2->RunAction(moveByAction_2);
	sprite->AddChild(sprite_2);

	/************************************************************************/
	/* Test Area End                                                        */
	/************************************************************************/

	while (1) 
	{
		if ( WPJALGOManager::GetSharedInst()->WaitForEvent(e))
		{
			// Event Handle
			if (e.type == ALLEGRO_EVENT_KEY_DOWN)
				if (e.keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
				{
					// Release all
					Exit();
					break;
				}
				else
					WPJLOG("[%s] 从键盘输入 ... %d\n", _D_NOW_TIME__, e.keyboard.keycode);
		}

		// Calculate if go into mainloop
		QueryPerformanceCounter(&t_obLINow);

		if (t_obLINow.QuadPart - t_obLILast.QuadPart > m_liAnimationInterval.QuadPart)
		{
			t_obLILast.QuadPart = t_obLINow.QuadPart;

			// Run MainLoop
			WPJDirector::GetSharedInst()->MainLoop();

			al_clear_to_color(al_map_rgb_f(0,0,0));
			sprite->Draw();
			sprite_2->Draw();
			al_flip_display();

			// Only For Test
			/*
			if (!moveByAction->IsDone())
				WPJLOG("[%s]Node Position (%f, %f)\n",
					_D_NOW_TIME__,
					sprite->GetPosition().x,
					sprite->GetPosition().y\
				);*/
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