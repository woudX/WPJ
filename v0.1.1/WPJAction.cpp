#include "WPJAction.h"
#include "WPJGarbageCollection.h"
#include "WPJLib.h"
USING_NS_WPJ

/// WPJAction
//////////////////////////////////////////////////////////////////////////

WPJAction *WPJAction::CreateNewObject() 
{
	WPJAction *t_pAction = new WPJAction();
	WPJGC::GetSharedInst()->AddPtr(t_pAction);
	return t_pAction;
}

WPJAction::WPJAction():m_pTarget(NULL)
{

}

void WPJAction::GetSharedPtr(WPJAction* &object)
{
	object = this;
	object->Retain();
}

WPJObject *WPJAction::DupCopy(WPJZone *zone)
{
	WPJAction *pRet = NULL;

	if (zone && zone->m_pCopyZone)
	{
		pRet = (WPJAction *)zone->m_pCopyZone;
	}
	else
	{
		pRet = WPJAction::CreateNewObject();
	}

	return pRet;
}

WPJAction *WPJAction::Copy()
{
	return (WPJAction *)DupCopy(0);
}

void WPJAction::Update(float dt)
{
	WPJLOG("[%s] Please inherite method!\n", _D_NOW_TIME__);
}

void WPJAction::Step(float dt)
{
	WPJLOG("[%s] Please Inherite method!\n", _D_NOW_TIME__);
}

void WPJAction::Stop()
{
	m_pTarget = NULL;
}

bool WPJAction::IsDone()
{
	return true;
}

void WPJAction::StartWithTarget(WPJNode *target)
{
	//	Issue 3
	m_pTarget = target;
}

void WPJAction::SetTag(int var) 
{
	m_nTag = var;
}

int WPJAction::GetTag() 
{
	return m_nTag;
}

void WPJAction::SetTarget(WPJNode* var) 
{
	var->GetSharedPtr(m_pTarget);
}

WPJNode *WPJAction::GetTarget()
{
	return m_pTarget;
}

WPJAction::~WPJAction()
{
	//	Issue 3 : Action series don't do any retain/release operation
	//	about target, this agreement may make things easier, let
	//	WPJActionManager to deal with these things is ok

	//	WPJ_SAFE_RELEASE(m_pTarget);
}

/// WPJFiniteAction
//////////////////////////////////////////////////////////////////////////

WPJFiniteAction::WPJFiniteAction():m_fDuration(0)
{

}

WPJFiniteAction *WPJFiniteAction::CreateNewObject()
{
	WPJFiniteAction *pRet = new WPJFiniteAction();
	WPJGC::GetSharedInst()->AddPtr(pRet);
	return pRet;
}

WPJObject *WPJFiniteAction::DupCopy(WPJZone *zone)
{
	WPJFiniteAction *pRet = NULL;
	WPJZone *pNewZone = NULL;

	if (zone && zone->m_pCopyZone)
	{
		pRet = (WPJFiniteAction *)zone->m_pCopyZone;
	}
	else
	{
		pRet = WPJFiniteAction::CreateNewObject();
		zone = pNewZone = new WPJZone(pRet);
	}

	WPJAction::DupCopy(zone);
	ptr_safe_del(pNewZone);

	return pRet;
}

WPJFiniteAction *WPJFiniteAction::Copy()
{
	return (WPJFiniteAction *)DupCopy(0);
}

void WPJFiniteAction::SetDuration(float var)
{
	m_fDuration = var;
}

float WPJFiniteAction::GetDuration()
{
	return m_fDuration;
}

WPJFiniteAction *WPJFiniteAction::Reverse()
{
	WPJLOG("[%s] Reverse is not implement\n", _D_NOW_TIME__);
	return NULL;
}

WPJFiniteAction::~WPJFiniteAction()
{

}
