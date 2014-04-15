#ifndef _H_WPJSCHEDULER
#define _H_WPJSCHEDULER

#include "WPJMacros.h"
#include "WPJObject.h"

NS_WPJ_BEGIN

class WPJTimer : WPJObject
{
public:
	static WPJTimer *CreateNewObject();
	
	bool InitalWithTarget(WPJObject *pTarget, SEL_SCHEDULE pfnSelector);
	bool InitalWithTarget(WPJObject *pTarget, SEL_SCHEDULE pfnSelector, float fSecond);
	bool InitalWithTarget(WPJObject *pTarget, SEL_SCHEDULE pfnSelector, float fSecond, U_INT nRepeat, float fDelay);

	void Update(float dt);

protected:
	WPJ_PROPERTY(float, m_fInterval, Interval)

	WPJObject *m_pTarget;
	float m_fElapsed;
	bool m_bRunForever;
	bool m_bUseDelay;
	U_INT m_uTimesExecuted;
	U_INT m_uRepeat;	// 0 repeat forever, 1 is 2 x executed
	float m_fDelay;
	SEL_SCHEDULE m_pfnSelector;

	WPJTimer();

};

NS_WPJ_END

#endif