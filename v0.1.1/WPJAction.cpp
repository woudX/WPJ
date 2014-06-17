#include "WPJAction.h"
#include "WPJGarbageCollection.h"

USING_NS_WPJ

/// WPJAction
//////////////////////////////////////////////////////////////////////////

WPJAction *WPJAction::CreateNewObject() 
{
	WPJAction *t_pAction = new WPJAction();
	WPJGC::GetSharedInst()->AddPtr(t_pAction);
	return t_pAction;
}

WPJAction::WPJAction() 
{

}

void WPJAction::GetSharedPtr(WPJAction* &object)
{
	object = this;
	object->Retain();
}

WPJAction *WPJAction::GetCopiedPtr()
{
	return DupCopy();
}

WPJAction *WPJAction::DupCopy()
{
	return NULL;
}

void WPJAction::Update(float dt)
{
	WPJLOG("[%s] Please inherite method!",_D_NOW_TIME__);
}

void WPJAction::Step(float dt)
{
	WPJLOG("[%s] Please Inherite method!",_D_NOW_TIME__);
}

void WPJAction::Stop()
{
	WPJLOG("[%s] Please Inherite update method!",_D_NOW_TIME__);
}

bool WPJAction::IsDone()
{
	return true;
}

void WPJAction::StartWithTarget(WPJNode *target)
{
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
	m_pTarget->Retain();
	return m_pTarget;
}

WPJAction::~WPJAction()
{
	m_pTarget->Release();
}

/// WPJFiniteAction
//////////////////////////////////////////////////////////////////////////

WPJFiniteAction::WPJFiniteAction():m_fDuration(0)
{

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
