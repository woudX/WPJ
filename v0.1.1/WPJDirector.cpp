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
