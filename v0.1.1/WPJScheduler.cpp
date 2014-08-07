#include "WPJScheduler.h"
#include "WPJGarbageCollection.h"
#include "WPJDirector.h"
#include "WPJLib.h"

USING_NS_WPJ

_SchedulerTimers::_SchedulerTimers()
:target(NULL)
,paused(false)
{

}

_SchedulerTimers::~_SchedulerTimers()
{
	WPJ_SAFE_RELEASE(target);

	foreach_in_list_auto(WPJTimer*, itor, timers)
	{
		WPJ_SAFE_RELEASE(pp(itor));
	}

	timers.clear();
}

_SchedulerUpdates::_SchedulerUpdates()
:target(NULL)
,priority(0)
,paused(false)
,markedForDeletion(false)
{

}

_SchedulerUpdates::~_SchedulerUpdates()
{
	WPJ_SAFE_RELEASE(target);
}

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
	timer->AutoRelease();

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

SEL_SCHEDULE WPJTimer::GetpfnSelector()
{
	return m_pfnSelector;
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
				if (m_fElapsed >= m_fInterval)
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
		// 由Singleton WPJDirector获取到Scheduler然后传入target和pfnSelector注销Timer
	}
}

WPJScheduler::WPJScheduler()
:m_fTimeScale(1.0f)
{

}

void WPJScheduler::GetSharedPtr(WPJScheduler* &object)
{
	object = this;
	object->Retain();
}

WPJScheduler *WPJScheduler::GetCopiedPtr()
{
	return DupCopy();
}

WPJScheduler *WPJScheduler::DupCopy()
{
	return NULL;
}

U_INT WPJScheduler::GetSize()
{
	return sizeof(this);
}

WPJScheduler *WPJScheduler::CreateNewObject()
{
	WPJScheduler *scheduler = new WPJScheduler();
	scheduler->AutoRelease();

	return scheduler;
}

void WPJScheduler::ScheduleSelector(WPJObject *target, SEL_SCHEDULE pfnSelector, float fInterval, bool bPaused)
{
	ScheduleSelector(target, pfnSelector, fInterval, WPJRepeatForever, 0.0f, bPaused);
}

void WPJScheduler::ScheduleSelector(WPJObject *target, SEL_SCHEDULE pfnSelector, float fInterval, U_INT nRepeat, float fDelay, bool bPaused)
{
	// To-Do: 
	// 1.find the target in m_lCustomedSchedulerTimer
	// 2.check pfnSelect is in timers, if not CreateNewTimer and add to timers

	bool t_bIsFind = false;

	foreach_in_list_auto(_SchedulerTimers*, itor, m_lCustomedSchedulerTimer)
	{
		if ((*itor)->target == target)
		{
			t_bIsFind = true;
			bool t_bSame = false;
			foreach_in_list_auto(WPJTimer*, t_itor, (*itor)->timers)
			{
				if ((*t_itor)->GetpfnSelector() == pfnSelector)
				{
					t_bSame = true;
					WPJLOG("[%s] Error:%s\n", _D_NOW_TIME__, "this selector has been added into timers");
					break;
				}
			}

			if (!t_bSame)
			{
				WPJTimer *timer = WPJTimer::CreateNewObject(); ASSERT(timer != NULL);
				timer->InitalWithTarget(target, pfnSelector, fInterval, nRepeat, fDelay);

				(*itor)->timers.push_back(timer);
			}

			break;
		}
	}

	if (!t_bIsFind)	// if not find,create new _SchedulerTimers and do the same thing
	{
		// initalize schedulerTimers
		_SchedulerTimers *schedulerTimers = new _SchedulerTimers();
		schedulerTimers->paused = bPaused;
		schedulerTimers->target = target;
		WPJ_SAFE_RETAIN(target);

		WPJTimer *timer = WPJTimer::CreateNewObject(); ASSERT(timer != NULL);
		timer->InitalWithTarget(target, pfnSelector, fInterval, nRepeat, fDelay);

		// insert into m_lCustomedSchedulerTimer
		schedulerTimers->timers.push_back(timer);
		m_lCustomedSchedulerTimer.push_back(schedulerTimers);
	}

}


void WPJScheduler::SetTimeScale(float var)
{
	m_fTimeScale = var;
}

float WPJScheduler::GetTimeScale()
{
	return m_fTimeScale;
}

void WPJScheduler::UnscheduleSelector(WPJObject *target, SEL_SCHEDULE pfnSelector)
{
	foreach_in_list_auto(_SchedulerTimers*, itor, m_lCustomedSchedulerTimer)
	{
		if ((*itor)->target == target)
			foreach_in_list(WPJTimer*, t_itor, (*itor)->timers)
			{
				if ((*t_itor)->GetpfnSelector() == pfnSelector)
				{
					// release Timer and erase from the timers
					WPJ_SAFE_RELEASE_NULL(pp(t_itor));
					t_itor = (*itor)->timers.erase(t_itor);
				}
				else
					++t_itor;
			}
	}
}

void WPJScheduler::UnscheduleAllSelector(WPJObject *target)
{
	foreach_in_list_auto(_SchedulerTimers*, itor, m_lCustomedSchedulerTimer)
	{
		if ((*itor)->target == target)
			foreach_in_list_auto(WPJTimer*, t_itor, (*itor)->timers)
			{
				// release timer
				WPJ_SAFE_RELEASE_NULL(pp(t_itor));
			}

		(*itor)->timers.clear();
	}
}

void WPJScheduler::UnscheduleAll()
{
	safe_remove_all_from_list(_SchedulerUpdates*, m_lUpdate0List);
	safe_remove_all_from_list(_SchedulerUpdates*, m_lUpdatePosList);
	safe_remove_all_from_list(_SchedulerUpdates*, m_lUpdateNegList);
	safe_remove_all_from_list(_SchedulerTimers*, m_lCustomedSchedulerTimer);
}

void WPJScheduler::CheckInsertUpdate(std::list<_SchedulerUpdates*> &updateList, WPJObject *target, int nPriority, bool bPaused)
{
	bool t_bAlreadyExist = false;

	foreach_in_list_auto(_SchedulerUpdates*, itor, updateList)
	{
		if ((*itor)->target == target)
		{
			t_bAlreadyExist = true;
			WPJLOG("[%s] Info : target has already been inserted\n", _D_NOW_TIME__);
		}
	}

	// if target not exist , create new target-update
	if (!t_bAlreadyExist)
	{
		_SchedulerUpdates *schedulerUpdate = new _SchedulerUpdates();	ASSERT(schedulerUpdate != NULL);
		schedulerUpdate->paused = bPaused;
		schedulerUpdate->target = target;
		WPJ_SAFE_RETAIN(target);

		schedulerUpdate->priority = nPriority;

		updateList.push_back(schedulerUpdate);
	}
}

void WPJScheduler::ScheduleUpdateForTarget(WPJObject *target, int nPriority, bool bPaused)
{
	bool t_bAlreadyExist = false;

	if (nPriority > 0)
		CheckInsertUpdate(m_lUpdatePosList, target, nPriority, bPaused);
	else if (nPriority == 0)
		CheckInsertUpdate(m_lUpdate0List, target, nPriority, bPaused);
	else if (nPriority < 0)
		CheckInsertUpdate(m_lUpdateNegList, target, nPriority, bPaused);
}

void WPJScheduler::CheckRemoveUpdate(std::list<_SchedulerUpdates*> &updateList,const WPJObject *target)
{
	foreach_in_list_auto(_SchedulerUpdates*, itor, updateList)
	{
		if ((*itor)->target == target)
		{
			(*itor)->markedForDeletion = true;
			break;
		}
	}
}

_SchedulerUpdates *WPJScheduler::FindUpdateByTarget(const WPJObject *target)
{
	_SchedulerUpdates *t_pUpdate = NULL;

	find_in_list(_SchedulerUpdates*, t_pUpdate, target, m_lUpdate0List)
	find_in_list(_SchedulerUpdates*, t_pUpdate, target, m_lUpdatePosList)
	find_in_list(_SchedulerUpdates*, t_pUpdate, target, m_lUpdateNegList)

	return t_pUpdate;
}

void WPJScheduler::UnscheduleUpdateForTarget(const WPJObject *target)
{
	_SchedulerUpdates *t_pUpdate = FindUpdateByTarget(target);

	if (t_pUpdate != NULL)
		t_pUpdate->markedForDeletion = true;
}

void WPJScheduler::PauseTarget(WPJObject *target)
{
	_SchedulerUpdates *t_pUpdate = FindUpdateByTarget(target);

	if (t_pUpdate != NULL)
		t_pUpdate->paused = true;
}

void WPJScheduler::ResumeTarget(WPJObject *target)
{
	_SchedulerUpdates *t_pUpdate = FindUpdateByTarget(target);

	if (t_pUpdate != NULL)
		t_pUpdate->paused = false;
}

bool WPJScheduler::IsTargetPaused(WPJObject *target)
{
	_SchedulerUpdates *t_pUpdate = FindUpdateByTarget(target);

	if (t_pUpdate != NULL)
		return t_pUpdate->paused;

	ASSERT(0);
	return false;
}

void WPJScheduler::Update(float dt)
{
	// call normal update
	// priority > 0
	foreach_in_list_auto(_SchedulerUpdates*, itor, m_lUpdatePosList)
	{
		if (!((*itor)->markedForDeletion) && !((*itor)->paused))
			(*itor)->target->Update(dt);
	}

	// priority = 0
	foreach_in_list_auto(_SchedulerUpdates*, itor, m_lUpdate0List)
	{
		if (!((*itor)->markedForDeletion) && !((*itor)->paused))
			(*itor)->target->Update(dt);
	}

	// priority < 0
	foreach_in_list_auto(_SchedulerUpdates*, itor, m_lUpdateNegList)
	{
		if (!((*itor)->markedForDeletion) && !((*itor)->paused))
			(*itor)->target->Update(dt);
	}

	// customed call
	foreach_in_list_auto(_SchedulerTimers*, itor, m_lCustomedSchedulerTimer)
	{
		if (!(*itor)->paused)
		foreach_in_list_auto(WPJTimer*, t_itor, (*itor)->timers)
		{
			(*t_itor)->Update(dt);
		}
	}

	// recycle update, customed timers will be recycled auto
	foreach_in_list(_SchedulerUpdates*, itor, m_lUpdatePosList)
	{
		if ((*itor)->markedForDeletion)
		{
			ptr_safe_del(pp(itor));
			itor = m_lUpdatePosList.erase(itor);
		}
		else
			++itor;
	}

	foreach_in_list(_SchedulerUpdates*, itor, m_lUpdate0List)
	{
		if ((*itor)->markedForDeletion)
		{
			ptr_safe_del(pp(itor));
			itor = m_lUpdate0List.erase(itor);
		}
		else
			++itor;
	}

	foreach_in_list(_SchedulerUpdates*, itor, m_lUpdateNegList)
	{
		if ((*itor)->markedForDeletion)
		{
			ptr_safe_del(pp(itor));
			itor = m_lUpdateNegList.erase(itor);
		}
		else
			++itor;
	}
}

WPJScheduler::~WPJScheduler()
{
	safe_remove_all_from_list(_SchedulerUpdates*, m_lUpdate0List);
	safe_remove_all_from_list(_SchedulerUpdates*, m_lUpdatePosList);
	safe_remove_all_from_list(_SchedulerUpdates*, m_lUpdateNegList);
	safe_remove_all_from_list(_SchedulerTimers*, m_lCustomedSchedulerTimer);
}