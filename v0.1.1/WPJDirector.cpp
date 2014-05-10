#include "WPJDirector.h"
#include "WPJAppDelegate.h"
USING_NS_WPJ

WPJDirector *WPJDirector::m_pInst = 0;

WPJDirector *WPJDirector::GetSharedInst()
{
	if (m_pInst == 0)
		m_pInst = new WPJDisplayLinkDirector;

	return m_pInst;
}

WPJScheduler *WPJDirector::GetScheduler()
{
	return m_pScheduler;
}

void WPJDirector::SetScheduler(WPJScheduler* var)
{
	if (m_pScheduler != var)
	{
		m_pScheduler->Release();
		var->GetSharedPtr(m_pScheduler);
	}
}

WPJALGOManager *WPJDirector::GetALGOManager()
{
	return m_pALGOManager;
}

WPJDirector::WPJDirector()
:m_pScheduler(WPJScheduler::CreateNewObject())
,m_pALGOManager(WPJALGOManager::GetSharedInst())
,m_bPause(false)
,m_bExit(false)
,m_bTimeStart(true)
,m_fAccumDt(0)
,m_uFrames(0)
,m_pLastTimeVal(new TimeVal())
{
	
}

void WPJDirector::RunWithScene(WPJScene *pScene) 
{
	PushScene(pScene);
	StartAnimation();
}

void WPJDirector::PushScene(WPJScene *pScene)
{
	m_obSceneStack.push(pScene);
	pScene->Retain();

	m_bCleanUpRunningScene = false;

	pScene->GetSharedPtr(m_pNextScene);
}

void WPJDirector::PopScene()
{
	WPJScene *t_pScene = m_obSceneStack.top();
	m_obSceneStack.pop();
	t_pScene->Release();

	// No scene, exit
	if (m_obSceneStack.size() == 0)
	{
		End();
	}
	else
	{
		m_bCleanUpRunningScene = true;
		m_obSceneStack.top()->GetSharedPtr(m_pNextScene);
	}
}

void WPJDirector::ReplaceWithScene(WPJScene *pScene)
{
	WPJScene *t_pScene = m_obSceneStack.top();
	m_obSceneStack.pop();
	t_pScene->Release();

	m_bCleanUpRunningScene = true;

	m_obSceneStack.push(pScene);
	pScene->Retain();
}

void WPJDirector::PopToRootScene()
{
	PopToSceneStackLevel(1);
}

void WPJDirector::PopToSceneStackLevel(int pStackLevel) 
{
	int t_iCount = m_obSceneStack.size();

	if (t_iCount == 0)
	{
		End();
		return ;
	}

	if (t_iCount <= pStackLevel)
	{
		return ;
	}

	if (t_iCount > pStackLevel)
	{
		// Remove scene, run OnExitTransitionDidStart and OnExit
		while (t_iCount > pStackLevel)
		{
			WPJScene *t_pScene = m_obSceneStack.top();
			m_obSceneStack.pop();
			
			if (t_pScene->IsRunning())
			{
				t_pScene->OnExitTransitionDidStart();
				t_pScene->OnExit();
			}
			t_pScene->CleanUp();
			t_pScene->Release();

			--t_iCount;
		}

		// Set next scene but not CleanupRunningScene
		m_obSceneStack.top()->GetSharedPtr(m_pNextScene);
		m_bCleanUpRunningScene = false;
	}
}

void WPJDirector::Pause()
{
	m_bPause = true;
	
	// To-do: pause all but draw, reduce draw frequency
	SetAnimationInterval(1.0 / 4);
}

void WPJDirector::Resume()
{
	m_bPause = false;

	// To-do: resume all enclude draw frequency
	SetAnimationInterval(1.0 / 60);
}

void WPJDirector::MainLoop()
{
	if (m_bExit)
		End();
	else
		Draw();
}

void WPJDirector::End()
{
	// Release WPJDirector and exit
}

void WPJDirector::Draw()
{
	CalculateInterval();

	// update
	m_pScheduler->Update(m_fDeltaTime);

	// draw, using visit()
	ShowStatus();
}

void WPJDirector::CalculateInterval()
{
	TimeVal t_liNow;
	WPJTime::GetTimeOfDay(&t_liNow);

	if (m_bTimeStart)
	{
		m_fDeltaTime = 0;
		m_bTimeStart = false;
	}
	else
	{
		m_fDeltaTime = static_cast<float>((t_liNow.tv_sec - m_pLastTimeVal->tv_sec) + (t_liNow.tv_msec - m_pLastTimeVal->tv_msec) / 1000000.0);
	}

	*m_pLastTimeVal = t_liNow;
}

void WPJDirector::ShowStatus()
{
	++m_uFrames;
	m_fAccumDt += m_fDeltaTime;

	if (m_fAccumDt > 1.0f) 
	{
		WPJLOG("[%s] FPS ... %u\n", _D_NOW_TIME__, m_uFrames);
		m_uFrames = 0;
		m_fAccumDt = 0;
	}

}

void WPJDirector::SetAnimationInterval(double dValue)
{

}

void WPJDirector::StartAnimation()
{

}

void WPJDirector::StopAnimation()
{

}

WPJDisplayLinkDirector::WPJDisplayLinkDirector()
	:m_bInvalid(false)
{

}

void WPJDisplayLinkDirector::MainLoop()
{
	if (m_bExit)
		End();
	else if (! m_bInvalid)
		Draw();
}

void WPJDisplayLinkDirector::SetAnimationInterval(double dValue)
{
	m_dAnimationInterval = dValue;
	if (! m_bInvalid)
	{
		StopAnimation();
		StartAnimation();
	}
}

void WPJDisplayLinkDirector::StartAnimation()
{
	if (WPJTime::GetTimeOfDay(m_pLastTimeVal) != 0)
	{
		WPJLOG("[%s] DisPlayLinkDirector ... error on GetTimeOfDay\n", _D_NOW_TIME__);
	}

	m_bInvalid = false;

	WPJAppDelegate::GetSharedInst()->SetAnimationInterval(m_dAnimationInterval);
}

void WPJDisplayLinkDirector::StopAnimation()
{
	m_bInvalid = true;
}