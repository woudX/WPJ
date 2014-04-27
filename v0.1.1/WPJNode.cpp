#include "WPJNode.h"
#include "WPJGarbageCollection.h"

USING_NS_WPJ

WPJNode::WPJNode()
:m_pScheduler(NULL)
,m_iTag(INT_MAX)
,m_pParent(NULL)
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
		// To-do:call OnEnter and OnEnterTransitionDidFinish
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
		// 1. call OnExit and OnExitTransitionDidFinish
		// 2. Clean Up and Remove
		// 3. What should be done about this child's childList??? They need to be Cleanup?
		//	maybe provide a method to destroy tree is a good idea, when needed, use it.

		if (m_bIsRunning)
		{
			// call OnExit and OnExitTransitionDidFinish
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
	// 1. call OnExit and OnExitTransitionDidFinish
	// 2. Clean Up and Remove
	// 3. What should be done about this child's childList??? They need to be Cleanup?
	//	maybe provide a method to destroy tree is a good idea, when needed, use it.

	if (m_bIsRunning)
	{
		// call OnExit and OnExitTransitionDidFinish
	}

	// if don't call cleanup, it's Schedules and Actions won't be released
	if (p_bCleanup)
		p_pChild->CleanUp();

	p_pChild->m_pParent = NULL;

	m_lChildList.remove(p_pChild);
	p_pChild->Release();
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

void WPJNode::StopScheduleAndAction()
{
	m_pScheduler->PauseTarget(this);
}

void WPJNode::ResumeScheduleAndAction()
{
	m_pScheduler->ResumeTarget(this);
}

void WPJNode::Update(float dt)
{

}

WPJNode::~WPJNode()
{

}






