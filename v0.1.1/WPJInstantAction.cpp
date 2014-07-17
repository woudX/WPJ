#include "WPJInstantAction.h"

USING_NS_WPJ

///	WPJInstantAction
//////////////////////////////////////////////////////////////////////////

WPJInstantAction *WPJInstantAction::CreateNewObject()
{
	WPJInstantAction *pRet = new WPJInstantAction();
	pRet->AutoRelease();

	return pRet;
}

WPJInstantAction::WPJInstantAction()
	:m_bIsDone(false)
	,m_fElapsed(0.0f)
{
	m_fDuration = 0.0f;
}

WPJObject *WPJInstantAction::DupCopy(WPJZone *zone)
{
	WPJInstantAction *pRet = NULL;
	WPJZone *pNewZone = NULL;

	if (zone && zone->m_pCopyZone)
	{
		pRet = (WPJInstantAction *)zone->m_pCopyZone;
	}
	else
	{
		pRet = WPJInstantAction::CreateNewObject();
		zone = pNewZone = new WPJZone(pRet);
	}

	WPJFiniteAction::DupCopy(zone);

	ptr_safe_del(pNewZone);
	return pRet;
}

WPJInstantAction *WPJInstantAction::Copy()
{
	return (WPJInstantAction *)DupCopy(0);
}

void WPJInstantAction::StartWithTarget(WPJNode *target)
{
	WPJFiniteAction::StartWithTarget(target);

	m_fElapsed = 0.0f;
	m_bIsDone = false;
}

void WPJInstantAction::Step(float dt)
{
	UN_USED_PARAM(dt);
	if (!IsDone())
	{
		Update(1.0);
		m_bIsDone = true;
	}
}

void WPJInstantAction::Update(float dt)
{
	UN_USED_PARAM(dt);
}

bool WPJInstantAction::IsDone()
{
	return m_bIsDone;
}

WPJInstantAction::~WPJInstantAction()
{

}

/// WPJPlaceBy
//////////////////////////////////////////////////////////////////////////

WPJPlaceBy::WPJPlaceBy()
{

}

WPJPlaceBy::WPJPlaceBy(WPJPoint &point)
	:m_obDeltaPos(point)
{

}

WPJPlaceBy *WPJPlaceBy::Create(WPJPoint& position)
{
	WPJPlaceBy *pRet = new WPJPlaceBy(position);
	pRet->AutoRelease();

	return pRet;
}

WPJObject *WPJPlaceBy::DupCopy(WPJZone *zone)
{
	WPJPlaceBy *pRet = NULL;
	WPJZone *pNewZone = NULL;

	if (zone && zone->m_pCopyZone)
	{
		pRet = (WPJPlaceBy *)zone->m_pCopyZone;
	}
	else
	{
		pRet = WPJPlaceBy::Create(m_obDeltaPos);
		zone = pNewZone = new WPJZone(pRet);
	}

	WPJInstantAction::DupCopy(zone);
	ptr_safe_del(zone);

	return pRet;
}

WPJPlaceBy *WPJPlaceBy::Copy()
{
	return (WPJPlaceBy *)DupCopy(0);
}

WPJFiniteAction *WPJPlaceBy::Reverse()
{
	return WPJPlaceBy::Create(-m_obDeltaPos);
}

void WPJPlaceBy::Update(float dt)
{
	UN_USED_PARAM(dt);
	m_pTarget->SetPosition(m_obEndPos);
}

void WPJPlaceBy::StartWithTarget(WPJNode *target)
{
	WPJInstantAction::StartWithTarget(target);

	m_obStartPos = m_pTarget->GetPosition();
	m_obEndPos = m_obStartPos + m_obDeltaPos;
}