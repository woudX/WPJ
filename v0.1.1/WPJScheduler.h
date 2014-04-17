#ifndef _H_WPJSCHEDULER
#define _H_WPJSCHEDULER

#include "WPJMacros.h"
#include "WPJObject.h"
#include "WPJStdafx.h"

NS_WPJ_BEGIN

class WPJTimer : public WPJObject
{
public:
	static WPJTimer *CreateNewObject();
	
	bool InitalWithTarget(WPJObject *pTarget, SEL_SCHEDULE pfnSelector);
	bool InitalWithTarget(WPJObject *pTarget, SEL_SCHEDULE pfnSelector, float fSecond);
	bool InitalWithTarget(WPJObject *pTarget, SEL_SCHEDULE pfnSelector, float fSecond, U_INT nRepeat, float fDelay);

	void Update(float dt);

protected:
	WPJ_PROPERTY(float, m_fInterval, Interval)
	WPJ_PROPERTY_READONLY(SEL_SCHEDULE,m_pfnSelector, pfnSelector)
	WPJObject *m_pTarget;
	float m_fElapsed;
	bool m_bRunForever;
	bool m_bUseDelay;
	U_INT m_uTimesExecuted;
	U_INT m_uRepeat;	// 0 repeat forever, 1 is 2 x executed
	float m_fDelay;

	WPJTimer();

};

/**
 _SchedulerTimers is a inner-class
 It contain the information about registed WPJObject-WPJTimer and only used for manage all customed Scheduler
*/
class _SchedulerTimers
{
public:
	std::list<WPJTimer*> timers;
	WPJObject *target;
	bool paused;
	
	_SchedulerTimers();
	~_SchedulerTimers();
};

class _SchedulerUpdates
{
public:
	WPJObject *target;
	int priority;
	bool paused;
	bool markedForDeletion;

	_SchedulerUpdates();
	~_SchedulerUpdates();
};

class WPJScheduler : public WPJObject
{
public:
	void Update(float dt);
	static WPJScheduler *CreateNewObject();

	void ScheduleSelector(WPJObject *target, SEL_SCHEDULE pfnSelector, float fInterval, bool bPaused);
	void ScheduleSelector(WPJObject *target, SEL_SCHEDULE pfnSelector, float fInterval, U_INT nRepeat, float fDelay, bool bPaused);
	void UnscheduleSelector(WPJObject *target, SEL_SCHEDULE pfnSelector);
	void UnscheduleAllSelector(WPJObject *target);

	void ScheduleUpdateForTarget(WPJObject *target, int nPriority, bool bPaused);
	void UnscheduleUpdateForTarget(const WPJObject *target);

	void UnscheduleAllWithMinPriority(int nMinPriority);
	void UnscheduleAll();
	void PauseTarget(WPJObject *target);
	void ResumeTarget(WPJObject *target);
	bool IsTargetPaused(WPJObject *target);

	
private:
	WPJ_PROPERTY(float, m_fTimeScale, TimeScale)
		
	std::list<_SchedulerUpdates*> m_lUpdateNegList;	// priority < 0
	std::list<_SchedulerUpdates*> m_lUpdate0List;	// priority = 0
	std::list<_SchedulerUpdates*> m_lUpdatePosList;	// priority > 0
	std::list<_SchedulerTimers*> m_lCustomedSchedulerTimer;	// customed

	WPJScheduler();

	void CheckInsertUpdate(std::list<_SchedulerUpdates*> &updateList, WPJObject *target, int nPriority, bool bPaused);
};

NS_WPJ_END

#endif