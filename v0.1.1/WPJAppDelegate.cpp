#include "WPJAppDelegate.h"
#include "WPJGarbageCollection.h"
#include "WPJFileUtil.h"

#include "WPJTest.h"
#include "WPJIntervalAction.h"
#include "WPJInstantAction.h"
#include "WPJActionManager.h"
#include "WPJSprite.h"
#include "WPJTextureManager.h"
#include "WPJScriptSupport.h"
#include "DemoScene.h"
#include "WPJInputUtil.h"

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
	// Set FPS, default value is 1.0 / 60
	t_pDirector->SetAnimationInterval(1.0 / 60);

	/// Init Draw engine
	//////////////////////////////////////////////////////////////////////////
	WPJALGOManager *t_pALGOManager = WPJALGOManager::GetSharedInst();
	t_pALGOManager->SetDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, wResolutionShowAll);

	/// Init Platform
	//////////////////////////////////////////////////////////////////////////
	WPJFileUtil *pFileUtil = WPJFileUtil::GetSharedInst();
	pFileUtil->AddSearchPath("data/windows/");
	pFileUtil->AddSearchResolution("music/");
	pFileUtil->AddSearchResolution("image/");
	pFileUtil->AddSearchResolution("script/");

	/// Init Support - Lua
	//////////////////////////////////////////////////////////////////////////
	WPJScriptManager *t_pScriptManager = WPJScriptManager::GetsharedInst();
	t_pScriptManager->SetScriptEngine(new WPJScriptProtocol());
	t_pScriptManager->GetScriptEngine()->Open();

	/// User customed init
	//////////////////////////////////////////////////////////////////////////
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
	WPJScene *t_pScene = DemoScene::CreateNewObject();
	t_pDirector->RunWithScene(t_pScene);

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
	WPJInputUtil *t_pInputUtil = WPJInputUtil::GetSharedInst();

	QueryPerformanceCounter(&t_obLILast);

	if (!ApplicationDidFinishLaunching())
	{
		WPJLOG("[%s] Error ... WPJAppDelegation init failed!\n", _D_NOW_TIME__);
		return 0;
	}

	while (1) 
	{
		if (t_pInputUtil->PeekEvent(e))
		{
			t_pInputUtil->AnalysisEvent(e);
			if (e.type == ALLEGRO_EVENT_KEY_DOWN)
				if (e.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				{
					Exit();
					break;
				}
		}
		else
		{
			// Calculate if go into mainloop
			QueryPerformanceCounter(&t_obLINow);

			if (t_obLINow.QuadPart - t_obLILast.QuadPart > m_liAnimationInterval.QuadPart)
			{
				t_obLILast.QuadPart = t_obLINow.QuadPart;

				// Run MainLoop
				WPJDirector::GetSharedInst()->MainLoop();

				//	release events
				WPJInputUtil::GetSharedInst()->ClearAllTriggedEvents();

				//	release autorelease pool
				WPJGC::GetSharedInst()->Pop();

				//	garbage collection
				WPJGC::GetSharedInst()->GC();

			}
			else
				Sleep(0);		
		}
		Sleep(0);
	}
	
	return 0;
}

int WPJAppDelegate::Exit()
{
	WPJScriptManager::GetsharedInst()->GetScriptEngine()->Close();
	delete WPJScriptManager::GetsharedInst();
	WPJALGOManager::GetSharedInst()->DestroyALGO();
	delete WPJFileUtil::GetSharedInst();
	delete WPJTextureManager::GetSharedInst();
	delete WPJALGOManager::GetSharedInst();
	delete WPJInputUtil::GetSharedInst();
	delete WPJDirector::GetSharedInst();
	delete WPJActionManager::GetsharedInst();
	WPJGC::GetSharedInst()->Finalize();
	delete WPJGC::GetSharedInst();
	
	system("pause");

	return 0;
}