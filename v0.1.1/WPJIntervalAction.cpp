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