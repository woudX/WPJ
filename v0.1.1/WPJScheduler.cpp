#include "WPJScheduler.h"
#include "WPJGarbageCollection.h"

USING_NS_WPJ

WPJTimer::WPJTimer()
:m_pTarget(NULL)
,m_fElapsed(-1)
,m_bRunForever(true)
,m_uTimesExecuted(0)
,m_uRepeat(0)
,m_fDelay(0.0f)
,m_fInterval(0.0f)
,m_pfnSelector(NULL)
,m_bUseDelay(false)
{

}

WPJTimer *WPJTimer::CreateNewObject()
{
	WPJTimer *timer = new WPJTimer();
	WPJGC::GetSharedInst()->AddPtr(timer);

	return timer;
}

bool WPJTimer::InitalWithTarget(WPJObject *pTarget, SEL_SCHEDULE pfnSelector)
{
	return InitalWithTarget(pTarget, pfnSelector, 0, WPJRepeatForever, 0.0f);
}

bool WPJTimer::InitalWithTarget(WPJObject *pTarget, SEL_SCHEDULE pfnSelector, float fSecond)
{
	return InitalWithTarget(pTarget, pfnSelector, fSecond, WPJRepeatForever, 0.0f);
}

bool WPJTimer::InitalWithTarget(WPJObject *pTarget, SEL_SCHEDULE pfnSelector, float fSecond, U_INT nRepeat, float fDelay)
{
	m_pTarget = pTarget;
	m_pfnSelector = pfnSelector;
	m_fInterval = fSecond;
	m_fElapsed = -1;
	m_bRunForever = (nRepeat == WPJRepeatForever) ? true : false;
	m_fDelay = fDelay;
	m_uRepeat = nRepeat;
	m_bUseDelay = (m_fDelay > 0.0f) ? true : false;
	return true;
}

float WPJTimer::GetInterval()
{
	return m_fInterval;
}

void WPJTimer::SetInterval(float var)
{
	m_fInterval = var;
}

void WPJTimer::Update(float dt)
{
	if (m_fElapsed == -1)
	{
		m_fElapsed = 0.0f;
	}
	else
	{
		if (m_bRunForever && !m_bUseDelay)
		{
			m_fElapsed += dt;
			if (m_fElapsed >= m_fInterval)
			{
				if (m_pTarget && m_pfnSelector)
				{
					(m_pTarget->*m_pfnSelector)(m_fElapsed);
				}

				m_fElapsed = 0;
			}
		} 
		else
		{
			m_fElapsed += dt;
			if (m_bUseDelay)
			{
				if (m_fElapsed >= m_fDelay)
				{
					if (m_pTarget && m_pfnSelector)
						(m_pTarget->*m_pfnSelector)(m_fElapsed);

					m_fElapsed = m_fElapsed - m_fDelay;
					m_uTimesExecuted += 1;
					m_bUseDelay = false;
				}
			}
			else
			{
				if (m_fElapsed > m_fInterval)
				{
					if (m_pTarget && m_pfnSelector)
						(m_pTarget->*m_pfnSelector)(m_fElapsed);

					m_uTimesExecuted += 1;
					m_fElapsed = false;
				}
			}
		}
	}

	if (!m_bRunForever && m_uTimesExecuted > m_uRepeat)
	{
		// To-Do: 注销Timer，允许GC回收
	}
}