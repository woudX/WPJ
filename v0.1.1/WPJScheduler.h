#ifndef _H_WPJSCHEDULER
#define _H_WPJSCHEDULER

#include "WPJMacros.h"
#include "WPJObject.h"
#include "WPJStdafx.h"

NS_WPJ_BEGIN

/**
	WPJTimer provide the basic timing function, it can realize delay, repeat 
	and interval run
*/

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
	_SchledulerTimer is a non-public class, it contains WPJObject and Timers has been registed
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

/**
	_SchedulerUpdates is a non-public class, it contains WPJObject which the Update function 
	has been registed
*/
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

/**
	WPJScheduler is used to maintain all schedulers in project, it provide many methods 
	to operate the normal scheduler and customed scheduler
*/

class WPJScheduler : public WPJObject
{
public:

	/// Inherate Method
	static WPJScheduler *CreateNewObject();
	virtual U_INT GetSize();
	virtual void GetSharedPtr(WPJScheduler* &object);
	virtual WPJScheduler *GetCopiedPtr();

	void Update(float dt);

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

	~WPJScheduler();

private:
	WPJ_PROPERTY(float, m_fTimeScale, TimeScale)
		
	std::list<_SchedulerUpdates*> m_lUpdateNegList;	// priority < 0
	std::list<_SchedulerUpdates*> m_lUpdate0List;	// priority = 0
	std::list<_SchedulerUpdates*> m_lUpdatePosList;	// priority > 0
	std::list<_SchedulerTimers*> m_lCustomedSchedulerTimer;	// customed

	WPJScheduler();

	_SchedulerUpdates *FindUpdateByTarget(const WPJObject *target);
	void CheckInsertUpdate(std::list<_SchedulerUpdates*> &updateList, WPJObject *target, int nPriority, bool bPaused);
	void CheckRemoveUpdate(std::list<_SchedulerUpdates*> &updateList, const WPJObject *target);
};

#define find_in_list(type, findPtr, targetPtr, list)\
foreach_in_list_auto(type, itor, list)\
{\
	if ((*itor)->target == targetPtr)\
	{\
		findPtr = (*itor);\
		break;\
	}\
}

NS_WPJ_END

#endif