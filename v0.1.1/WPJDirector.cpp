#include "WPJDirector.h"

USING_NS_WPJ

WPJDirector *WPJDirector::m_pInst = 0;

WPJDirector *WPJDirector::GetSharedInst()
{
	if (m_pInst == 0)
		m_pInst = new WPJDirector;

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
}

void WPJDirector::PushScene(WPJScene *pScene)
{

}

void WPJDirector::PopScene()
{

}

void WPJDirector::ReplaceWithScene(WPJScene *pScene)
{

}

void WPJDirector::PopToRootScene()
{

}

void WPJDirector::PopToSceneStackLevel(int pStackLevel /* = 1 */) 
{

}

void WPJDirector::Pause()
{
	m_bPause = true;
	
	// To-do: pause all but draw, reduce draw frequency
}

void WPJDirector::Resume()
{
	m_bPause = false;

	// To-do: resume all enclude draw frequency
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