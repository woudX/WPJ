#include "WPJAppDelegate.h"
#include "WPJGarbageCollection.h"
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

void WPJAppDelegate::SetAnimationInterval(double dValue)
{
	LARGE_INTEGER t_obFreq;
	QueryPerformanceFrequency(&t_obFreq);
	m_liAnimationInterval.QuadPart = static_cast<LONGLONG>(t_obFreq.QuadPart * dValue);
}

bool WPJAppDelegate::ApplicationDidFinishLaunching()
{
	return Initialization();
}

bool WPJAppDelegate::Initialization()
{
	WPJDirector *t_pDirector = WPJDirector::GetSharedInst();
	WPJALGOManager *t_pALGOManager = WPJALGOManager::GetSharedInst();
	t_pALGOManager->SetDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, wResolutionShowAll);

	// Set FPS, default value is 1.0 / 60
	t_pDirector->SetAnimationInterval(1.0 / 60);

	// User customed init
	if (!ExtendInit())
	{
		WPJLOG("[%s] WPJAppDelegate ... error in ExtendInit\n", _D_NOW_TIME__);
		return false;
	}	
	
	// Init ALGO
	// Set application resolution and policy 
	
	if (!t_pALGOManager->InitALGO())
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

	t_pALGOMgr->SetWndName(
		HString::CreateWithFormat(
			"Test Window ---- now resolution[%d x %d] ---- design [%d x %d] --- zoom : %.2f",
			(int)(t_pALGOMgr->GetFrameSize().width * t_pALGOMgr->GetFrameZoomFactor()),
			(int)(t_pALGOMgr->GetFrameSize().height * t_pALGOMgr->GetFrameZoomFactor()),
			(int)(t_pALGOMgr->GetDesignResolutionSize().width),
			(int)(t_pALGOMgr->GetDesignResolutionSize().height),
			(float)(t_pALGOMgr->GetFrameZoomFactor()))
		);

	return true;
}

int WPJAppDelegate::Run()
{
	LARGE_INTEGER t_obLILast;
	LARGE_INTEGER t_obLINow;
	ALLEGRO_EVENT e;

	QueryPerformanceCounter(&t_obLILast);

	if (!ApplicationDidFinishLaunching())
	{
		WPJLOG("[%s] Error ... WPJAppDelegation init failed!\n", _D_NOW_TIME__);
		return 0;
	}

	/************************************************************************/
	/* Test Area                                                            */
	/************************************************************************/
	WPJDirector *pDirector = WPJDirector::GetSharedInst();
	WPJPoint origin = pDirector->GetViewOriginPoint();
	WPJSize size = pDirector->GetViewSize();

	// 初始化精灵-白
	WPJMoveTo *moveByAction = WPJMoveTo::Create(5, WPJPoint(WPJDirector::GetSharedInst()->GetViewSize().width - 75,WPJDirector::GetSharedInst()->GetViewSize().height - 75));
	WPJSprite *sprite = WPJSprite::Create();
	sprite->InitWithFile("white.png");
	sprite->SetPosition(75, 75);
	sprite->RunAction(moveByAction);

	// 初始化精灵-黄
	
	WPJRotateBy *rotateByAction = WPJRotateBy::Create(2, 3.14);
	WPJIntervalAction *reverseBy = rotateByAction->Reverse();
	WPJMoveTo *moveByAction_2 = WPJMoveTo::Create(3, WPJPoint(origin.x + size.width - 75, origin.y + 75));
	WPJWait *waitAction = WPJWait::Create(2.0);
	WPJSequence *sequence = WPJSequence::Create(reverseBy, moveByAction_2, waitAction, rotateByAction, NULL);

	WPJSprite *sprite_2 = WPJSprite::Create();
	sprite_2->InitWithFile("white.png");
	sprite_2->SetAngle(3.14 / 4);
	sprite_2->UpdateDisplayOpacity(255);
	sprite_2->UpdateDisplayColor(wpColor3B(255, 255, 0));
	sprite_2->SetCoordinateSystem(WPJ_COORDINATE_RELATIVE);
	sprite_2->SetBlendFunc(new_blend(AL_FUNC_ADD, AL_SRC_ALPHA, AL_SRC_COLOR));
	sprite_2->SetPosition(WPJPoint(origin.x + 75, origin.y + 75));
	// sprite_2->RunAction(moveByAction_2);
	// sprite_2->RunAction(reverseBy);
	sprite_2->RunAction(sequence);

	WPJGC *gc = WPJGC::GetSharedInst();

	// 初始化背景图片精灵
	WPJSprite *background = WPJSprite::Create();
	background->InitWithFile("background.png");
	// background->SetIgnoreAnchorPoint(true);
	background->SetPosition(origin.x + size.width / 2, origin.y + size.height / 2);
	background->UpdateDisplayColor(wpc3(100, 100, 100));
	background->SetScale(size.width / 800, size.height / 600);

	// 初始化边界精灵
	WPJSprite *border = WPJSprite::Create();
	border->InitWithFile("background.png");
	border->SetPosition(0, 0);
	border->SetIgnoreAnchorPoint(true);
	border->UpdateDisplayColor(wpc3(255, 0, 0));
	border->SetScale(WPJALGOManager::GetSharedInst()->GetScaleX(), WPJALGOManager::GetSharedInst()->GetScaleY());

	/************************************************************************/
	/* Test Area End                                                        */
	/************************************************************************/
	float t2 = 0;
	bool bPause = false;
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
				else if (e.keyboard.keycode == ALLEGRO_KEY_ENTER)
					bPause = !bPause;
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

			// Only For Test
			//////////////////////////////////////////////////////////////////////////
			al_clear_to_color(al_map_rgb_f(0,0,0));

			border->Draw();
			background->Draw();
			sprite->Draw();
			sprite_2->Draw();
			al_flip_display();

			/*
			if (!reverseBy->IsDone())
				WPJLOG("[%s]Node Angle (%f)\n",
					_D_NOW_TIME__,
					sprite_2->GetAngle()
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