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
	WPJGC::GetSharedInst()->AddPtr(t_pIntervalAction);

	return t_pIntervalAction;
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
	m_fElapsed = 0;
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
	WPJGC::GetSharedInst()->AddPtr(t_pMoveBy);
	return t_pMoveBy;
}

void WPJMoveBy::StartWithTarget(WPJNode *target)
{
	WPJIntervalAction::StartWithTarget(target);
	m_obPreviousPoint = target->GetPosition();
	m_obStartPoint = target->GetPosition();
}

WPJIntervalAction *WPJMoveBy::Reverse()
{
	return WPJMoveBy::Create(m_fDuration, -m_obDeltaPositon);
}

void WPJMoveBy::Update(float dt)
{
	if (m_pTarget) 
	{
		WPJPoint t_obPos = m_pTarget->GetPosition();
		if (dt >= 0.00001)
			t_obPos = t_obPos + (m_obDeltaPositon / m_fDuration) * dt;
		m_pTarget->SetPosition(t_obPos);
	}
}

WPJMoveBy *WPJMoveBy::DupCopy()
{
	return NULL;
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
	WPJGC::GetSharedInst()->AddPtr(t_pMoveTo);
	return t_pMoveTo;
}

WPJMoveTo *WPJMoveTo::DupCopy()
{
	return NULL;
}

void WPJMoveTo::StartWithTarget(WPJNode *target)
{
	WPJIntervalAction::StartWithTarget(target);
	m_obStartPoint = m_obPreviousPoint = target->GetPosition();
	m_obDeltaPositon = m_obDeltaPositon - target->GetPosition();
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

WPJRotateBy *WPJRotateBy::DupCopy()
{
	return NULL;
}

void WPJRotateBy::StartWithTarget(WPJNode *target)
{
	WPJIntervalAction::StartWithTarget(target);
	m_fStartAngle = m_fPreviousAngle = target->GetAngle();
}

WPJIntervalAction *WPJRotateBy::Reverse()
{
	return new WPJRotateBy(m_fDuration, -m_fDeltaAngle);
}

void WPJRotateBy::Update(float dt)
{
	if (m_pTarget != NULL)
	{
		float t_fAngle = m_pTarget->GetAngle();

		if (dt >= 0.00001)
			t_fAngle += (m_fDeltaAngle / m_fDuration) * dt;
		m_pTarget->SetAngle(t_fAngle);
	}
}

WPJRotateBy *WPJRotateBy::Create(float fDuration, float fAngle)
{
	WPJRotateBy *pRet = new WPJRotateBy(fDuration, fAngle);
	WPJGC::GetSharedInst()->AddPtr(pRet);

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

WPJRotateTo *WPJRotateTo::DupCopy()
{
	return NULL;
}

WPJRotateTo::WPJRotateTo(float fDuration, float fAngle)
{
	m_fDuration = fDuration;
	m_fDeltaAngle = fAngle;
}

void WPJRotateTo::StartWithTarget(WPJNode *target)
{
	WPJIntervalAction::StartWithTarget(target);
	m_fStartAngle = m_fPreviousAngle = target->GetAngle();
	m_fDeltaAngle -= m_fStartAngle;
}

WPJRotateTo *WPJRotateTo::Create(float fDuration, float fAngle)
{
	WPJRotateTo *pRet = new WPJRotateTo(fDuration, fAngle);
	WPJGC::GetSharedInst()->AddPtr(pRet);

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

WPJWait *WPJWait::DupCopy()
{
	return NULL;
}

void WPJWait::StartWithTarget(WPJNode *target)
{
	WPJIntervalAction::StartWithTarget(target);
}

void WPJWait::Update(float dt)
{
	UN_USED_PARAM(dt);
}

WPJWait *WPJWait::Create(float fDuration)
{
	WPJWait *pRet = new WPJWait(fDuration);
	WPJGC::GetSharedInst()->AddPtr(pRet);

	return pRet;
}

WPJWait::~WPJWait()
{

}

/// WPJSequence
//////////////////////////////////////////////////////////////////////////

WPJSequence::WPJSequence()
{

}

WPJSequence::WPJSequence(WPJFiniteAction *pAction1, WPJFiniteAction *pAction2)
{

}

WPJSequence *WPJSequence::DupCopy()
{
	return NULL;
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
			t_pPrev = CreateWithToActions(t_pPrev, t_pNow);
			bOneAction = false;
		}
		else
		{
			if (bOneAction)
			{
				t_pPrev = CreateWithToActions(t_pPrev, WPJWait::Create(0));
			}
			break;
		}
	}

	return (WPJSequence*) t_pPrev;
}

WPJSequence *WPJSequence::CreateWithToActions(WPJFiniteAction *pAction1, WPJFiniteAction *pAction2)
{
	WPJSequence *pRet = new WPJSequence();
	pRet->InitWithTwoActions(pAction1, pAction2);
	WPJGC::GetSharedInst()->AddPtr(pRet);

	return pRet;
}

void WPJSequence::StartWithTarget(WPJNode *target)
{
	WPJIntervalAction::StartWithTarget(target);

	m_pAction1->StartWithTarget(target);
	m_pAction2->StartWithTarget(target);
}

bool WPJSequence::InitWithTwoActions(WPJFiniteAction *pAction1, WPJFiniteAction *pAction2)
{
	ASSERT(pAction1 != NULL);
	ASSERT(pAction2 != NULL);

	m_fDuration = pAction1->GetDuration() + pAction2->GetDuration();

	m_pAction1 = pAction1;
	pAction1->Retain();

	m_pAction2 = pAction2;
	pAction2->Retain();

	return true;
}

void WPJSequence::Update(float dt)
{
	// need to run action1
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

}