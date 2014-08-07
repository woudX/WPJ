#include "WPJIntervalAction.h"
#include "WPJGarbageCollection.h"
#include "WPJLib.h"

USING_NS_WPJ

/// WPJIntervalAction
//////////////////////////////////////////////////////////////////////////
WPJIntervalAction::WPJIntervalAction()
:m_fElapsed(0)
,m_bInitial(false)
{

}

WPJIntervalAction *WPJIntervalAction::CreateNewObject()
{
	WPJIntervalAction *t_pIntervalAction = new WPJIntervalAction();
	t_pIntervalAction->AutoRelease();

	return t_pIntervalAction;
}

WPJObject *WPJIntervalAction::DupCopy(WPJZone *zone)
{
	WPJIntervalAction *pRet = NULL;
	WPJZone *pNewZone = NULL;

	if (zone && zone->m_pCopyZone)
	{
		pRet = (WPJIntervalAction *)zone->m_pCopyZone;
	}
	else
	{
		pRet = WPJIntervalAction::CreateNewObject();
		zone = pNewZone = new WPJZone(pRet);
	}

	WPJFiniteAction::DupCopy(zone);
	ptr_safe_del(pNewZone);

	return pRet;
}

WPJIntervalAction *WPJIntervalAction::Copy()
{
	return (WPJIntervalAction *)DupCopy(0);
}

void WPJIntervalAction::Step(float dt)
{
	//	Issue 5 : in cocos2dx , this is if else statement, but in WPJ this may
	//	let dt lost ,which will let whole action lost a bit
	if (!m_bInitial)
	{
		m_bInitial = true;
		m_fElapsed = 0;
	}
	
	if (!IsDone()) 
	{
		m_fElapsed += dt;

		Update(max(0,
			min(1, 
				m_fElapsed / 
					max(m_fDuration, FLT_EPSILON)
				)
			));
	}
}

bool WPJIntervalAction::IsDone()
{
	return m_fElapsed > m_fDuration;
}


WPJIntervalAction *WPJIntervalAction::Reverse()
{
	WPJLOG("[%s] Reverse is not implement\n", _D_NOW_TIME__);
	return NULL;
}

void WPJIntervalAction::StartWithTarget(WPJNode *target)
{
	WPJFiniteAction::StartWithTarget(target);

	m_bInitial = false;
	m_fElapsed = 0.0f;
}

WPJIntervalAction::~WPJIntervalAction()
{

}

/// WPJMoveBy
//////////////////////////////////////////////////////////////////////////

WPJMoveBy::WPJMoveBy()
{

}

WPJMoveBy::WPJMoveBy(float fDuration, const WPJPoint& deltaPos)
{
	m_fDuration = fDuration;
	m_obDeltaPositon = deltaPos;
}

WPJMoveBy *WPJMoveBy::Create(float fDuration, const WPJPoint& deltaPos)
{
	WPJMoveBy *t_pMoveBy = new WPJMoveBy(fDuration, deltaPos);
	t_pMoveBy->AutoRelease();

	return t_pMoveBy;
}

void WPJMoveBy::StartWithTarget(WPJNode *target)
{
	WPJIntervalAction::StartWithTarget(target);

	m_obStartPosition = m_obPreviousPosition = target->GetPosition();
}

WPJIntervalAction *WPJMoveBy::Reverse()
{
	return WPJMoveBy::Create(m_fDuration, -m_obDeltaPositon);
}

void WPJMoveBy::Stop()
{
	WPJIntervalAction::Stop();
}

void WPJMoveBy::Update(float dt)
{
	if (m_pTarget) 
	{
#if WPJ_ENABLED_ACTION_STACK
		WPJPoint t_obNowPosition = m_pTarget->GetPosition();
		WPJPoint t_obDiff = t_obNowPosition - m_obPreviousPosition;
		m_obStartPosition += t_obDiff;
		WPJPoint t_obNewPosition = m_obStartPosition + m_obDeltaPositon * dt;
		m_obPreviousPosition = t_obNewPosition;

		m_pTarget->SetPosition(t_obNewPosition);
#else
		m_pTarget->SetPosition(m_obStartPosition + m_obStartPosition * dt);
#endif
	}
}

WPJObject *WPJMoveBy::DupCopy(WPJZone *zone)
{
	WPJMoveBy *pRet = NULL;
	WPJZone *pNewZone = NULL;
	
	if (zone && zone->m_pCopyZone)
	{
		pRet = (WPJMoveBy *)zone->m_pCopyZone;
	}
	else
	{
		pRet = WPJMoveBy::Create(m_fDuration, m_obDeltaPositon);
		zone = pNewZone = new WPJZone(pRet);
	}

	WPJIntervalAction::DupCopy(zone);
	ptr_safe_del(pNewZone);

	return pRet;
}

WPJMoveBy *WPJMoveBy::Copy()
{
	return (WPJMoveBy *)DupCopy(0);
}

WPJMoveBy::~WPJMoveBy()
{

}

/// WPJMoveTo
//////////////////////////////////////////////////////////////////////////
WPJMoveTo::WPJMoveTo()
{

}

WPJMoveTo::WPJMoveTo(float fDuration, const WPJPoint& endPosition)
{
	m_fDuration = fDuration;
	m_obEndPosition = endPosition;
}

WPJMoveTo *WPJMoveTo::Create(float fDuration, const WPJPoint& endPosition)
{
	WPJMoveTo *t_pMoveTo = new WPJMoveTo(fDuration, endPosition);
	t_pMoveTo->AutoRelease();

	return t_pMoveTo;
}

WPJObject *WPJMoveTo::DupCopy(WPJZone *zone)
{
	WPJMoveTo *pRet = NULL;
	WPJZone *pNewZone = NULL;

	if (zone && zone->m_pCopyZone)
	{
		pRet = (WPJMoveTo *)zone->m_pCopyZone;
	}
	else
	{
		pRet = WPJMoveTo::Create(m_fDuration, m_obEndPosition);
		zone = pNewZone = new WPJZone(pRet);
	}

	WPJIntervalAction::DupCopy(zone);
	ptr_safe_del(pNewZone);

	return pRet;
}

WPJMoveTo *WPJMoveTo::Copy()
{
	return (WPJMoveTo *)DupCopy(0);
}

void WPJMoveTo::StartWithTarget(WPJNode *target)
{
	WPJMoveBy::StartWithTarget(target);
	m_obDeltaPositon = m_obEndPosition - m_obStartPosition;
}

WPJMoveTo::~WPJMoveTo()
{

}

/// WPJRotateBy
//////////////////////////////////////////////////////////////////////////

WPJRotateBy::WPJRotateBy()
{

}

WPJRotateBy::WPJRotateBy(float fDuration, float fAngle)
{
	m_fDuration = fDuration;
	m_fDeltaAngle = fAngle;
}

WPJObject *WPJRotateBy::DupCopy(WPJZone *zone)
{
	WPJRotateBy *pRet = NULL;
	WPJZone *pNewZone = NULL;

	if (zone && zone->m_pCopyZone)
	{
		pRet = (WPJRotateBy *)zone->m_pCopyZone;
	}
	else
	{
		pRet = WPJRotateBy::Create(m_fDuration, m_fDeltaAngle);
		zone = pNewZone = new WPJZone(pRet);
	}

	WPJIntervalAction::DupCopy(zone);
	ptr_safe_del(pNewZone);

	return pRet;
}

WPJRotateBy *WPJRotateBy::Copy()
{
	return (WPJRotateBy *)DupCopy(0);
}

void WPJRotateBy::StartWithTarget(WPJNode *target)
{
	WPJIntervalAction::StartWithTarget(target);

	m_fPreviousAngle = m_fStartAngle = fmodf(target->GetAngle(), MATH_PI * 2);
}

WPJIntervalAction *WPJRotateBy::Reverse()
{
	return WPJRotateBy::Create(m_fDuration, -m_fDeltaAngle);
}

void WPJRotateBy::Stop()
{
	WPJIntervalAction::Stop();
}

void WPJRotateBy::Update(float dt)
{
	if (m_pTarget != NULL)
	{
#if WPJ_ENABLED_ACTION_STACK
		float t_fNowAngle = m_pTarget->GetAngle();
		float t_fDiff = t_fNowAngle - m_fPreviousAngle;
		m_fStartAngle += t_fDiff;
		float t_fNewAngle = m_fStartAngle + m_fDeltaAngle * dt;
		t_fNewAngle = fmodf(t_fNewAngle, MATH_PI * 2);
		m_fPreviousAngle = t_fNewAngle;
		m_pTarget->SetAngle(t_fNewAngle);
#else
		m_pTarget->SetAngle(m_fStartAngle + m_fDeltaAngle * dt);
#endif
	}
}

WPJRotateBy *WPJRotateBy::Create(float fDuration, float fAngle)
{
	WPJRotateBy *pRet = new WPJRotateBy(fDuration, fAngle);
	pRet->AutoRelease();

	return pRet;
}

WPJRotateBy::~WPJRotateBy()
{

}

/// WPJRotateTo
//////////////////////////////////////////////////////////////////////////

WPJRotateTo::WPJRotateTo()
{

}

WPJObject *WPJRotateTo::DupCopy(WPJZone *zone)
{
	WPJRotateTo *pRet = NULL;
	WPJZone *pNewZone = NULL;

	if (zone && zone->m_pCopyZone)
	{
		pRet = (WPJRotateTo *)zone->m_pCopyZone;
	}
	else
	{
		pRet = WPJRotateTo::Create(m_fDuration, m_fEndAngle);
		zone = pNewZone = new WPJZone(pRet);
	}

	WPJIntervalAction::DupCopy(zone);
	ptr_safe_del(pNewZone);

	return pRet;
}

WPJRotateTo *WPJRotateTo::Copy()
{
	return (WPJRotateTo *)DupCopy(0);
}

WPJRotateTo::WPJRotateTo(float fDuration, float fAngle)
{
	m_fDuration = fDuration;
	m_fEndAngle = fAngle;
}

void WPJRotateTo::StartWithTarget(WPJNode *target)
{
	WPJIntervalAction::StartWithTarget(target);

	m_fStartAngle = m_fPreviousAngle = target->GetAngle();

	//	adujst delta angle to the shortest rotate way
	float t_fDelta = m_fEndAngle - m_fStartAngle;
	if (fabs(t_fDelta) < MATH_PI)
		m_fDeltaAngle = t_fDelta;
	else
		m_fDeltaAngle = (t_fDelta > 0) ? (t_fDelta - MATH_PI * 2) : (t_fDelta + MATH_PI * 2);
}

WPJRotateTo *WPJRotateTo::Create(float fDuration, float fAngle)
{
	WPJRotateTo *pRet = new WPJRotateTo(fDuration, fAngle);
	pRet->AutoRelease();

	return pRet;
}

WPJRotateTo::~WPJRotateTo()
{

}

/// WPJWait
//////////////////////////////////////////////////////////////////////////

WPJWait::WPJWait()
{

}

WPJWait::WPJWait(float fDuration)
{
	m_fDuration = fDuration;
}

WPJObject *WPJWait::DupCopy(WPJZone *zone)
{
	WPJWait *pRet = NULL;
	WPJZone *pNewZone = NULL;

	if (zone && zone->m_pCopyZone)
	{
		pRet = (WPJWait *)zone->m_pCopyZone;
	}
	else
	{
		pRet = WPJWait::Create(m_fDuration);
		zone = pNewZone = new WPJZone(pRet);
	}

	WPJIntervalAction::DupCopy(zone);
	ptr_safe_del(pNewZone);

	return pRet;
}

WPJWait *WPJWait::Copy()
{
	return (WPJWait *)DupCopy(0);
}

void WPJWait::StartWithTarget(WPJNode *target)
{
	WPJIntervalAction::StartWithTarget(target);
}

void WPJWait::Stop()
{
	WPJIntervalAction::Stop();
}

void WPJWait::Update(float dt)
{
	UN_USED_PARAM(dt);
}

WPJWait *WPJWait::Create(float fDuration)
{
	WPJWait *pRet = new WPJWait(fDuration);
	pRet->AutoRelease();

	return pRet;
}

WPJWait::~WPJWait()
{

}

/// WPJSequence
//////////////////////////////////////////////////////////////////////////

WPJSequence::WPJSequence()
	:m_pAction1(NULL)
	,m_pAction2(NULL)
	,m_bInitAction1(false)
	,m_bInitAction2(false)
	,m_fLastDt(0)
	,m_iLastRun(0)
{

}

WPJObject *WPJSequence::DupCopy(WPJZone *zone)
{
	WPJSequence *pRet = NULL;
	WPJZone *pNewZone = NULL;

	if (zone && zone->m_pCopyZone)
	{
		pRet = (WPJSequence *)zone->m_pCopyZone;
	}
	else
	{
		ASSERT(m_pAction1 != NULL);
		ASSERT(m_pAction2 != NULL);

		WPJFiniteAction *t_pAction1 = (WPJFiniteAction*) m_pAction1->Copy();
		WPJFiniteAction *t_pAction2 = (WPJFiniteAction*) m_pAction2->Copy();

		pRet = WPJSequence::CreateWithTwoActions(t_pAction1, t_pAction2);

		zone = pNewZone = new WPJZone(pRet);
	}

	WPJIntervalAction::DupCopy(zone);
	ptr_safe_del(pNewZone);

	return pRet;
}

WPJSequence *WPJSequence::Copy()
{
	return (WPJSequence *)DupCopy(0);
}

WPJIntervalAction *WPJSequence::Reverse()
{
	WPJLOG("[%s] There is no reverse implement for IntervalAction\n", _D_NOW_TIME__);
	return NULL;
}

WPJSequence *WPJSequence::Create(WPJFiniteAction *pAction1, ...)
{
	va_list ap;
	va_start(ap, pAction1);
	
	WPJSequence *pRet = WPJSequence::CreateWithVariableList(pAction1, ap);

	va_end(ap);

	return pRet;
}

WPJSequence *WPJSequence::CreateWithVariableList(WPJFiniteAction *pAction1, va_list args)
{
	WPJFiniteAction *t_pNow;
	WPJFiniteAction *t_pPrev = pAction1;
	bool bOneAction = true;

	while (true)
	{
		t_pNow = va_arg(args, WPJFiniteAction*);

		if (t_pNow)
		{
			t_pPrev = CreateWithTwoActions(t_pPrev, t_pNow);
			bOneAction = false;
		}
		else
		{
			if (bOneAction)
			{
				t_pPrev = CreateWithTwoActions(t_pPrev, WPJWait::Create(0));
			}
			break;
		}
	}

	return (WPJSequence*) t_pPrev;
}

WPJSequence *WPJSequence::CreateWithTwoActions(WPJFiniteAction *pAction1, WPJFiniteAction *pAction2)
{
	WPJSequence *pRet = new WPJSequence();
	pRet->InitWithTwoActions(pAction1, pAction2);
	pRet->AutoRelease();

	return pRet;
}

void WPJSequence::StartWithTarget(WPJNode *target)
{
	WPJIntervalAction::StartWithTarget(target);
	
	//	Issue_1 :
	//	Use InitAction flag to control can resolve the problem about init when repeat
	//	, if you use StartWithTarget may let something wrong

	m_bInitAction1 = false;
	m_bInitAction2 = false;
	m_fLastDt = 0;
	m_fSplit = m_pAction1->GetDuration() / m_fDuration;
	m_iLastRun = 0;
}

bool WPJSequence::InitWithTwoActions(WPJFiniteAction *pAction1, WPJFiniteAction *pAction2)
{
	ASSERT(pAction1 != NULL);
	ASSERT(pAction2 != NULL);

	m_fDuration = pAction1->GetDuration() + pAction2->GetDuration();

	m_pAction1 = pAction1;
	WPJ_SAFE_RETAIN(m_pAction1);

	m_pAction2 = pAction2;
	WPJ_SAFE_RETAIN(m_pAction2);

	return true;
}

void WPJSequence::Stop()
{
	WPJIntervalAction::Stop();

	m_pAction1->Stop();
	m_pAction2->Stop();
}

void WPJSequence::Update(float dt)
{
	WPJFiniteAction *t_pRun = NULL;
	int t_iRun = 0;
	float t_fNewDt = 0.0f;

	if (dt < m_fSplit)
	{
		//	run action1 and check if it's exist
		t_iRun = 1;
		t_pRun = m_pAction1;
		if (m_fSplit != 0)
			t_fNewDt = dt / m_fSplit;
		else
			t_fNewDt = 1;
	}
	else
	{
		//	run action2 and check if it's exist
		t_iRun = 2;
		t_pRun = m_pAction2;
		if (m_fSplit == 1)
			t_fNewDt = 1;
		else
			t_fNewDt = (dt - m_fSplit) / (1 - m_fSplit);
	}

	if (t_iRun == 1)
	{
		//	run action1
		if (!m_bInitAction1 && m_pAction1)
		{
			m_pAction1->StartWithTarget(m_pTarget);
			m_bInitAction1 = true;
		}
	}
	else if (t_iRun == 2)
	{
		//	run action2
		if (m_iLastRun == 0)
		{
			//	action1 skip, run directly
			m_pAction1->StartWithTarget(m_pTarget);
			m_pAction1->Update(1.0f);
			m_pAction1->Stop();
		}
		else if (m_iLastRun == 1)
		{
			//	action1 run finish
			m_pAction1->Update(1.0f);
			m_pAction1->Stop();
		}

		if (!m_bInitAction2 && m_pAction2)
		{
			m_pAction2->StartWithTarget(m_pTarget);
			m_bInitAction2 = true;
		}
	}

	t_pRun->Update(t_fNewDt);
	m_iLastRun = t_iRun;

	//	action 2 skip
	if (abs(dt - 1.0) < FLT_EPSILON && m_iLastRun == 1)
	{
		m_pAction2->StartWithTarget(m_pTarget);
		m_pAction2->Update(1.0f);
		m_pAction2->Stop();
	}
}

WPJSequence::~WPJSequence()
{
	WPJ_SAFE_RELEASE(m_pAction1);
	WPJ_SAFE_RELEASE(m_pAction2);
}

///	WPJSpawn
//////////////////////////////////////////////////////////////////////////

WPJSpawn::WPJSpawn()
	:m_pAction1(NULL)
	,m_pAction2(NULL)

{

}

WPJObject *WPJSpawn::DupCopy(WPJZone* zone)
{
	WPJSpawn *pRet = NULL;
	WPJZone *pNewZone = NULL;

	if (zone && zone->m_pCopyZone)
	{
		pRet = (WPJSpawn *)zone->m_pCopyZone;
	}
	else
	{
		ASSERT(m_pAction1 != NULL);
		ASSERT(m_pAction2 != NULL);

		WPJFiniteAction *t_pAction1 = (WPJFiniteAction *)m_pAction1->Copy();
		WPJFiniteAction *t_pAction2 = (WPJFiniteAction *)m_pAction2->Copy();

		pRet = WPJSpawn::CreateWithTwoActions(t_pAction1, t_pAction2);
		zone = pNewZone = new WPJZone(pRet);
	}

	WPJIntervalAction::DupCopy(zone);
	ptr_safe_del(pNewZone);

	return pRet;
}

WPJSpawn *WPJSpawn::Copy()
{
	return (WPJSpawn *)DupCopy(0);
}

void WPJSpawn::StartWithTarget(WPJNode *target)
{
	WPJIntervalAction::StartWithTarget(target);

	m_pAction1->StartWithTarget(target);
	m_pAction2->StartWithTarget(target);
}

WPJIntervalAction *WPJSpawn::Reverse()
{
	WPJLOG("[%s] There is no implememnt of Spawn!\n", _D_NOW_TIME__);
	return NULL;
}

void WPJSpawn::Stop()
{
	WPJIntervalAction::Stop();

	m_pAction1->Stop();
	m_pAction2->Stop();
}

void WPJSpawn::Update(float dt)
{
	if (m_pAction1)
		m_pAction1->Update(dt);
	
	if (m_pAction2)
		m_pAction2->Update(dt);

}

bool WPJSpawn::InitWithTwoActions(WPJFiniteAction *pAction1, WPJFiniteAction *pAction2)
{
	ASSERT(pAction1 != NULL);
	ASSERT(pAction2 != NULL);

	float t_fDuration1 = pAction1->GetDuration();
	float t_fDuration2 = pAction2->GetDuration();
	m_fDuration = max(t_fDuration1, t_fDuration2);

	m_pAction1 = pAction1;
	m_pAction2 = pAction2;

	if (t_fDuration1 > t_fDuration2)
		m_pAction2 = WPJSequence::CreateWithTwoActions(pAction2, WPJWait::Create(t_fDuration1 - t_fDuration2));
	else if (t_fDuration2 > t_fDuration1)
		m_pAction1 = WPJSequence::CreateWithTwoActions(pAction1, WPJWait::Create(t_fDuration2 - t_fDuration1));

	WPJ_SAFE_RETAIN(m_pAction1);
	WPJ_SAFE_RETAIN(m_pAction2);
	
	return true;
}

WPJSpawn *WPJSpawn::Create(WPJFiniteAction *pAction1, ...)
{
	WPJSpawn *pRet;
	va_list ap;

	va_start(ap, pAction1);
	pRet = WPJSpawn::CreateWithVariableList(pAction1, ap);
	va_end(ap);

	return pRet;
}

WPJSpawn *WPJSpawn::CreateWithTwoActions(WPJFiniteAction *pAction1, WPJFiniteAction *pAction2)
{
	WPJSpawn *pRet = new WPJSpawn();
	pRet->AutoRelease();
	pRet->InitWithTwoActions(pAction1, pAction2);

	return pRet;
}

WPJSpawn *WPJSpawn::CreateWithVariableList(WPJFiniteAction *pAction1, va_list args)
{
	WPJFiniteAction *t_pNow;
	WPJFiniteAction *t_pPrev = pAction1;
	bool bOneAction = true;

	while (1)
	{
		t_pNow = va_arg(args, WPJFiniteAction*);
		if (t_pNow)
		{
			t_pPrev = CreateWithTwoActions(t_pPrev, t_pNow);
			bOneAction = false;
		}
		else
		{
			if (bOneAction)
				t_pPrev = CreateWithTwoActions(t_pPrev, WPJWait::Create(0));
			break;
		}
	}

	return (WPJSpawn*) t_pPrev;
}

WPJSpawn::~WPJSpawn()
{
	WPJ_SAFE_RELEASE(m_pAction1);
	WPJ_SAFE_RELEASE(m_pAction2);
}

///	WPJRepeat
//////////////////////////////////////////////////////////////////////////

WPJRepeat::WPJRepeat()
	:m_pRepeatAction(NULL)
	,m_iCompleteCount(0)
	,m_iRepeatCount(0)
{

}

void WPJRepeat::StartWithTarget(WPJNode *target)
{
	WPJIntervalAction::StartWithTarget(target);

	m_iCompleteCount = 0;
	m_pRepeatAction->StartWithTarget(target);
}

WPJObject *WPJRepeat::DupCopy(WPJZone *zone)
{
	WPJRepeat *pRet = NULL;
	WPJZone *pNewZone = NULL;

	if (zone && zone->m_pCopyZone)
	{
		pRet = (WPJRepeat *)zone->m_pCopyZone;
	}
	else
	{
		WPJFiniteAction *t_pRepeatAction = m_pRepeatAction->Copy();
		pRet = WPJRepeat::Create(t_pRepeatAction, m_iRepeatCount);

		zone = pNewZone = new WPJZone(pRet);
	}

	WPJIntervalAction::DupCopy(zone);
	ptr_safe_del(pNewZone);

	return pRet;
}

WPJRepeat *WPJRepeat::Copy()
{
	return (WPJRepeat *)DupCopy(0);
}

void WPJRepeat::InitWithAction(WPJFiniteAction *pAction, int iRepeatCount)
{
	m_iRepeatCount = iRepeatCount;
	m_pRepeatAction = pAction;

	//	set the duration of WPJRepeat
	m_fDuration = pAction->GetDuration() * iRepeatCount;
	m_fNextDt = pAction->GetDuration() / m_fDuration;

	WPJ_SAFE_RETAIN(pAction);
}

WPJRepeat *WPJRepeat::Create(WPJFiniteAction *pAction, int iRepeatCount)
{
	WPJRepeat *pRet = new WPJRepeat();
	pRet->AutoRelease();
	pRet->InitWithAction(pAction, iRepeatCount);

	return pRet;
}

WPJIntervalAction *WPJRepeat::Reverse()
{
	return WPJRepeat::Create(m_pRepeatAction->Reverse(), m_iRepeatCount);
}

void WPJRepeat::Stop()
{
	WPJIntervalAction::Stop();

	m_pRepeatAction->Stop();
}

void WPJRepeat::Update(float dt)
{
	if (dt >= m_fNextDt)
	{
		//	if dt is too large that can repeat at least one times
		while (dt > m_fNextDt && m_iCompleteCount < m_iRepeatCount)
		{
			m_pRepeatAction->Update(1.0f);
			++m_iCompleteCount;

			m_pRepeatAction->Stop();
			m_pRepeatAction->StartWithTarget(m_pTarget);
			m_fNextDt += m_pRepeatAction->GetDuration() / m_fDuration;
		}

		//	Fix Issue 7, incorecct end value
		if (dt >= 1.0f && m_iCompleteCount < m_iRepeatCount)
			++m_iCompleteCount;

		if (m_iCompleteCount == m_iRepeatCount)
		{
			m_pRepeatAction->Update(1.0f);
			m_pRepeatAction->Stop();
		}
		else
		{
			m_pRepeatAction->Update(fmodf(dt * m_iRepeatCount, 1.0f));;
		}
	}
	else
	{
		m_pRepeatAction->Update(fmodf(dt * m_iRepeatCount, 1.0f));
	}
}

WPJRepeat::~WPJRepeat()
{
	WPJ_SAFE_RELEASE(m_pRepeatAction);
}
