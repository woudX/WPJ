#include "WPJNode.h"
#include "WPJGarbageCollection.h"
#include "WPJActionManager.h"

USING_NS_WPJ

WPJNode::WPJNode()
:m_pScheduler(NULL)
,m_iTag(INT_MAX)
,m_pParent(NULL)
,m_pActionManager(WPJActionManager::GetsharedInst())
{
	
}

WPJNode *WPJNode::CreateNewObject()
{
	WPJNode *t_pNode = new WPJNode();
	WPJGC::GetSharedInst()->AddPtr(t_pNode);

	return t_pNode;
}

void WPJNode::GetSharedPtr(WPJNode* &object)
{
	object = this;
	object->Retain();
}

WPJNode *WPJNode::GetCopiedPtr()
{
	return DupCopy();
}

WPJNode *WPJNode::DupCopy()
{
	return NULL;
}

U_INT WPJNode::GetSize()
{
	return sizeof(this);
}

bool WPJNode::Init()
{
	return true;
}

void WPJNode::SetParent(WPJNode* var)
{
	var->GetSharedPtr(m_pParent);
}

WPJNode *WPJNode::GetParent()
{
	return m_pParent;
}

void WPJNode::SetScheduler(WPJScheduler* var)
{
	var->GetSharedPtr(m_pScheduler);
}

WPJScheduler *WPJNode::GetScheduler()
{
	return m_pScheduler;
}

void WPJNode::SetActionManager(WPJActionManager* var)
{
	m_pActionManager = var;
}

WPJActionManager *WPJNode::GetActionManager()
{
	return m_pActionManager;
}

float WPJNode::GetRotationX()
{
	return m_fRotationX;
}

void WPJNode::SetRotationX(float var)
{
	m_fRotationX = var;
}

float WPJNode::GetRotationY()
{
	return m_fRotationY;
}

void WPJNode::SetRotationY(float var)
{
	m_fRotationY = var;
}

void WPJNode::SetRotation(float fx, float fy)
{
	m_fRotationX = fx;
	m_fRotationY = fy;
}

float WPJNode::GetScaleX()
{
	return m_fScaleX;
}

void WPJNode::SetScaleX(float var)
{
	m_fScaleX = var;
}

float WPJNode::GetScaleY()
{
	return m_fScaleY;
}

void WPJNode::SetScaleY(float var)
{
	m_fScaleY = var;
}

void WPJNode::SetScale(float fx, float fy)
{
	m_fScaleX = fx;
	m_fScaleY = fy;
}

void WPJNode::SetPosition(WPJPoint var)
{
	m_obPosition = var;
}

void WPJNode::SetPosition(float fx, float fy)
{
	m_obPosition.x = fx;
	m_obPosition.y = fy;
}

WPJPoint &WPJNode::GetPosition()
{
	return m_obPosition;
}

void WPJNode::SetAnchorPoint(WPJPoint var)
{
	m_obAnchorPoint = var;
}

void WPJNode::SetAnchorPoint(float fx, float fy)
{
	m_obAnchorPoint.x = fx;
	m_obAnchorPoint.y = fy;
}

WPJPoint &WPJNode::GetAnchorPoint()
{
	return m_obAnchorPoint;
}

void WPJNode::SetVisible(bool var)
{
	m_bVisible = var;
}

bool WPJNode::GetVisible()
{
	return m_bVisible;
}

bool WPJNode::IsRunning()
{
	return m_bIsRunning;
}

void WPJNode::OnEnter()
{
	m_bIsRunning = true;

	foreach_in_list_auto(WPJNode*, itor, m_lChildList)
	{
		if (!(*itor)->m_bIsRunning)
		{
			(*itor)->OnEnter();
		}
	}

	ResumeScheduleAndAction();
}

void WPJNode::OnEnterTransitionDidFinish()
{
	foreach_in_list_auto(WPJNode*, itor, m_lChildList)
	{
		if ((*itor))
		{
			(*itor)->OnEnterTransitionDidFinish();
		}
	}
}

void WPJNode::OnExit()
{
	this->PauseScheduleAndAction();

	m_bIsRunning = false;

	foreach_in_list_auto(WPJNode*, itor, m_lChildList)
	{
		if (*itor)
		{
			(*itor)->OnExit();
		}
	}
}

void WPJNode::OnExitTransitionDidStart()
{
	foreach_in_list_auto(WPJNode*, itor, m_lChildList)
	{
		if (*itor)
		{
			(*itor)->OnExitTransitionDidStart();
		}
	}
}


void WPJNode::AddChild(WPJNode *p_pChild)
{
	AddChild(p_pChild, p_pChild->m_iZOrder, p_pChild->m_iTag);
}

void WPJNode::AddChild(WPJNode *p_pChild, int p_izOrder)
{
	AddChild(p_pChild, p_izOrder, p_pChild->m_iZOrder);
}

void WPJNode::AddChild(WPJNode *p_pChild, int p_izOrder, int p_iTag)
{
	ASSERT(p_pChild != NULL);
	ASSERT(p_pChild->GetParent() == NULL);

	WPJNode *pSharedChild = NULL;
	p_pChild->GetSharedPtr(pSharedChild);

	pSharedChild->m_iZOrder = p_izOrder;
	pSharedChild->m_iTag = p_iTag;
	pSharedChild->m_pParent = this;
	
	m_lChildList.push_back(pSharedChild);

	if (m_bIsRunning)
	{
		// call OnEnter and OnEnterTransitionDidFinish
		pSharedChild->OnEnter();
		pSharedChild->OnEnterTransitionDidFinish();
	}
}

WPJNode *WPJNode::GetChildByTag(int p_iTag)
{
	foreach_in_list_auto(WPJNode*, itor, m_lChildList)
	{
		if ((*itor)->m_iTag == p_iTag)
			return *itor;
	}
	
	return NULL;
}

std::list<WPJNode*> &WPJNode::GetAllChild()
{
	return m_lChildList;
}

U_INT WPJNode::GetChildCount()
{
	return m_lChildList.size();
}

void WPJNode::RemoveChild(WPJNode *p_pChild, bool p_bCleanup)
{
	foreach_in_list_auto(WPJNode*, itor, m_lChildList)
	{
		if ((*itor) == p_pChild)
		{
			DetachChild(p_pChild, p_bCleanup);
			break;
		}
	}
}

void WPJNode::RemoveFromParent(bool p_bCleanUp)
{
	if (m_pParent != NULL)
		m_pParent->RemoveChild(this, p_bCleanUp);
}

void WPJNode::RemoveChildByTag(int p_iTag, bool p_bCleanup)
{
	WPJNode *t_pNode = GetChildByTag(p_iTag);

	if (t_pNode != NULL)
		this->RemoveChild(t_pNode, p_bCleanup);

}

void WPJNode::RemoveAllChild(bool p_bCleanup)
{
	// These codes are same to Detach Method, because directy calling Detach method will cause iterator invalid

	foreach_in_list_auto(WPJNode*, itor, m_lChildList)
	{
		//To-Do: 
		// 1. call OnExit and OnExitTransitionDidStart
		// 2. Clean Up and Remove
		// 3. What should be done about this child's childList??? They need to be Cleanup?
		//	maybe provide a method to destroy tree is a good idea, when needed, use it.

		if (m_bIsRunning)
		{
			// call OnExit and OnExitTransitionDidStart
			(*itor)->OnExit();
			(*itor)->OnExitTransitionDidStart();
		}

		// if don't call cleanup, it's Schedules and Actions won't be released
		if (p_bCleanup)
			(*itor)->CleanUp();

		(*itor)->m_pParent = NULL;

		(*itor)->Release();
	}

	m_lChildList.clear();
}

void WPJNode::CleanUp()
{
	this->UnscheduleAllSelectors();
}

void WPJNode::DetachChild(WPJNode *p_pChild, bool p_bCleanup)
{
	//To-Do: 
	// 1. call OnExit and OnExitTransitionDidStart
	// 2. Clean Up and Remove
	// 3. What should be done about this child's childList??? They need to be Cleanup?
	//	maybe provide a method to destroy tree is a good idea, when needed, use it.

	if (m_bIsRunning)
	{
		// call OnExit and OnExitTransitionDidStart
		p_pChild->OnExit();
		p_pChild->OnExitTransitionDidStart();
	}

	// if don't call cleanup, it's Schedules and Actions won't be released
	if (p_bCleanup)
		p_pChild->CleanUp();

	p_pChild->m_pParent = NULL;

	m_lChildList.remove(p_pChild);
	p_pChild->Release();
}

void WPJNode::Draw()
{

}

void WPJNode::Visit()
{
	if (!m_bVisible)
		return ;

	if (m_lChildList.size() != 0)
	{
		// Visit node which zOrder < 0
		foreach_in_list_auto(WPJNode*, itor, m_lChildList)
		{
			if ((*itor)->m_iZOrder < 0)
				(*itor)->Visit();
		}

		this->Draw();

		// Visit node which zOrder > 0
		foreach_in_list_auto(WPJNode*, itor, m_lChildList)
		{
			if ((*itor)->m_iZOrder > 0)
				(*itor)->Visit();
		}
		
	}
	else
	{
		// This is leaf node
		this->Draw();
	}
}

void WPJNode::Schedule(SEL_SCHEDULE pfnSelector)
{
	m_pScheduler->ScheduleSelector(this, pfnSelector, 0, !m_bIsRunning);
}

void WPJNode::Schedule(SEL_SCHEDULE pfnSelector, float fInterval)
{
	m_pScheduler->ScheduleSelector(this, pfnSelector, fInterval, !m_bIsRunning);
}

void WPJNode::Schedule(SEL_SCHEDULE pfnSelector, float fInterval, U_INT nRepeat, float fDelay)
{
	m_pScheduler->ScheduleSelector(this, pfnSelector, fInterval, nRepeat, fDelay, !m_bIsRunning);
}

void WPJNode::ScheduleOnce(SEL_SCHEDULE pfnSelector, float fDelay)
{
	m_pScheduler->ScheduleSelector(this, pfnSelector, 0, 1, fDelay, !m_bIsRunning);
}

void WPJNode::ScheduleUpdate(int prority)
{
	m_pScheduler->ScheduleUpdateForTarget(this, prority, !m_bIsRunning);
}

void WPJNode::UnscheduleUpdate()
{
	m_pScheduler->UnscheduleUpdateForTarget(this);
}

void WPJNode::Unschedule(SEL_SCHEDULE pfnSelector)
{
	m_pScheduler->UnscheduleSelector(this, pfnSelector);
}

void WPJNode::UnscheduleAllSelectors()
{
	m_pScheduler->UnscheduleAllSelector(this);
}

void WPJNode::PauseScheduleAndAction()
{
	m_pScheduler->PauseTarget(this);
}

void WPJNode::ResumeScheduleAndAction()
{
	m_pScheduler->ResumeTarget(this);
}

void WPJNode::RunAction(WPJAction *pAction)
{
	ASSERT(pAction != NULL);
	m_pActionManager->AddAction(this, pAction, !m_bIsRunning);
}

void WPJNode::Update(float dt)
{

}

WPJNode::~WPJNode()
{

}

/// WPJNodeRGBA
//////////////////////////////////////////////////////////////////////////

WPJNodeRGBA::WPJNodeRGBA() 
{

}

U_CHAR WPJNodeRGBA::GetDisplayOpacity()
{
	return m_displayOpacity;
}

void WPJNodeRGBA::UpdateDisplayOpacity(U_CHAR opacity)
{
	m_displayOpacity = opacity;
}

U_CHAR WPJNodeRGBA::GetOpacity()
{
	return m_realOpacity;
}

void WPJNodeRGBA::SetOpacity(U_CHAR opacity)
{
	m_realOpacity = opacity;
}

const wpColor3B& WPJNodeRGBA::GetDisplayColor()
{
	return m_displayColor;
}

void WPJNodeRGBA::UpdateDisplayColor(const wpColor3B& color)
{
	m_displayColor = color;
}

const wpColor3B& WPJNodeRGBA::GetColor()
{
	return m_realColor;
}

void WPJNodeRGBA::SetColor(const wpColor3B& color)
{
	m_realColor = color;
}

bool WPJNodeRGBA::IsOpacityModifyRGB()
{
	return false;
}

void WPJNodeRGBA::SetOpacityModifyRGB(bool bValue)
{
	UN_USED_PARAM(bValue);
}

bool WPJNodeRGBA::IsCascadeColorEnabled()
{
	return m_bCascadeColorEnabled;
}

void WPJNodeRGBA::SetCascadeColorEnabled(bool bValue)
{
	m_bCascadeColorEnabled = bValue;
}

bool WPJNodeRGBA::IsCascadeOpacityEnabled()
{
	return m_bCascadeOpacityEnabled;
}

void WPJNodeRGBA::SetCascadeOpacityEnabled(bool bValue)
{
	m_bCascadeOpacityEnabled = bValue;
}

WPJNodeRGBA::~WPJNodeRGBA()
{

}