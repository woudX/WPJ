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

U_INT WPJNode::GetChildCount()
{
	return m_lChildList.size();
}

void WPJNode::RemoveChild(WPJNode *p_pChild, bool p_bCleanup = true)
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

void WPJNode::CleanUp()
{
	this->UnscheduleAllSelectors();
}

void WPJNode::DetachChild(WPJNode *p_pChild, bool p_bCleanup)
{
	if (p_bCleanup)
		p_pChild->CleanUp();

	p_pChild->m_pParent = NULL;
}

WPJNode::~WPJNode()
{

}






