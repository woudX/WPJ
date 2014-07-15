#include "WPJIntervalAction.h"
#include "WPJGarbageCollection.h"

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

void WPJIntervalAction::Stop()
{
	m_pTarget = NULL;
}

void WPJIntervalAction::Step(float dt)
{
	if (!m_bInitial)
	{
		m_bInitial = true;
		m_fElapsed = 0;
	}
	else if (!IsDone()) 
	{
		float next_dt = ((m_fElapsed + dt) > m_fDuration) ? (m_fDuration - m_fElapsed) : dt;
		m_fElapsed += dt;
		Update(dt);
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

	m_obEndPoint = target->GetPosition() + m_obDeltaPositon;
	m_obStartPoint = target->GetPosition();
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
		WPJPoint t_obPos = m_pTarget->GetPosition();
		if (dt >= 0.00001)
			t_obPos = t_obPos + ((m_obEndPoint - m_obStartPoint) / m_fDuration) * dt;
		m_pTarget->SetPosition(t_obPos);
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
	m_obDeltaPositon = endPosition;
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
		pRet = WPJMoveTo::Create(m_fDuration, m_obDeltaPositon);
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
	WPJIntervalAction::StartWithTarget(target);

	m_obStartPoint = target->GetPosition();
	m_obEndPoint = m_obDeltaPositon;
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

	m_fStartAngle = target->GetAngle();
	m_fEndAngle = target->GetAngle() + m_fDeltaAngle;
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
		float t_fAngle = m_pTarget->GetAngle();

		if (dt >= 0.00001)
			t_fAngle += ((m_fEndAngle - m_fStartAngle) / m_fDuration) * dt;
		m_pTarget->SetAngle(t_fAngle);
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
		pRet = WPJRotateTo::Create(m_fDuration, m_fDeltaAngle);
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
	m_fDeltaAngle = fAngle;
}

void WPJRotateTo::StartWithTarget(WPJNode *target)
{
	WPJIntervalAction::StartWithTarget(target);

	m_fStartAngle = target->GetAngle();
	m_fEndAngle = m_fDeltaAngle;
	
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
	
	// Issue_1 :
	// This place should need not to call, this will let tick lose efficacy
	// but if not call this , the action will call StartWithTarget on first time, which
	// means first dt will be lost

	m_pAction1->StartWithTarget(target);
	m_pAction2->StartWithTarget(target);
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
	if (m_fElapsed < m_pAction1->GetDuration())
	{
		m_pAction1->Step(dt);
	}
	else
	{
		if (m_pAction2 != NULL)
			m_pAction2->Step(dt);
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
	m_pAction1->Step(dt);

	if (m_pAction2)
		m_pAction2->Step(dt);
}

bool WPJSpawn::InitWithTwoActions(WPJFiniteAction *pAction1, WPJFiniteAction *pAction2)
{
	ASSERT(pAction1 != NULL);
	ASSERT(pAction2 != NULL);

	m_fDuration = max(pAction1->GetDuration(), pAction2->GetDuration());

	m_pAction1 = pAction1;
	WPJ_SAFE_RETAIN(pAction1);

	m_pAction2 = pAction2;
	WPJ_SAFE_RETAIN(pAction2);
	
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
	int iNextChange = m_pRepeatAction->GetDuration() * (m_iCompleteCount + 1);
	m_pRepeatAction->Step(dt);

	if (m_fElapsed > iNextChange)
	{
		m_pRepeatAction->Stop();
		m_pRepeatAction->StartWithTarget(m_pTarget);

		m_iCompleteCount++;
	}
	
}

WPJRepeat::~WPJRepeat()
{
	WPJ_SAFE_RELEASE(m_pRepeatAction);
}
