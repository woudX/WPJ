#include "WPJActionManager.h"

USING_NS_WPJ

/// _ActionElement
//////////////////////////////////////////////////////////////////////////

void _ActionElement::ClearAllActions()
{
	foreach_in_list_auto(WPJAction*, itor, m_lpActions)
		pp(itor)->Release();
	m_lpActions.clear();
}

void _ActionElement::AddAction(WPJAction *pAction)
{
	if (pAction != NULL)
	{
		pAction->Retain();
		m_lpActions.push_back(pAction);
	}
}

void _ActionElement::Update(float dt)
{
	if (!bPaused)
	{
		foreach_in_list_auto(WPJAction*, itor, m_lpActions)
		{
			if (pp(itor) != NULL)
			{
				pp(itor)->Step(dt);
			}
		}
	}
}

_ActionElement::~_ActionElement()
{
	ClearAllActions();
	pTarget->Release();
	pTarget = NULL;
}

/// WPJActionManager
//////////////////////////////////////////////////////////////////////////

WPJActionManager *WPJActionManager::m_pInst = 0;

WPJActionManager::WPJActionManager()
{

}

WPJActionManager *WPJActionManager::GetsharedInst()
{
	if (m_pInst == 0)
		m_pInst = new WPJActionManager();

	return m_pInst;
}

void WPJActionManager::AddAction(WPJNode *pNode, WPJAction *pAction, bool bPaused)
{
	ASSERT(pNode != NULL && pAction != NULL);

	_ActionElement *pActionElem = NULL;

	foreach_in_list_auto(_ActionElement*,itor,m_lpActionElem)
	{
		if (ptr_data(itor)->pTarget == pNode)
		{
			pActionElem = ptr_data(itor);
			break;
		}
	}

	// regist target
	pAction->StartWithTarget(pNode);

	// if there is no ActionElement, create a new one and init it
	if (pActionElem == NULL)
	{
		pActionElem = new _ActionElement();
		pNode->GetSharedPtr(pActionElem->pTarget);
		pActionElem->bPaused = bPaused;

		m_lpActionElem.push_back(pActionElem);
	}

	// storage action
	pActionElem->AddAction(pAction);

	
	
}

void WPJActionManager::RemoveAllAction()
{
	foreach_in_list_auto(_ActionElement*, itor, m_lpActionElem)
	{
		if (*itor != NULL)
			pp(itor)->ClearAllActions();
	}
}

void WPJActionManager::RemoveAllActionFromTarget(WPJNode *target)
{
	foreach_in_list_auto(_ActionElement*, itor, m_lpActionElem)
	{
		if (pp(itor) != NULL)
			if (pp(itor)->pTarget == target)
			{
				pp(itor)->ClearAllActions();
				break;
			}	
	}
}

void WPJActionManager::PauseTarget(WPJNode *target)
{
	foreach_in_list_auto(_ActionElement*, itor, m_lpActionElem)
	{
		if (pp(itor) != NULL)
			if (pp(itor)->pTarget == target)
			{
				pp(itor)->bPaused = true;
				break;
			}
	}
}

void WPJActionManager::PauseAllTarget()
{
	foreach_in_list_auto(_ActionElement*, itor, m_lpActionElem)
	{
		if (pp(itor) != NULL)
			pp(itor)->bPaused = true;
	}
}

void WPJActionManager::ResumeTarget(WPJNode *target)
{
	foreach_in_list_auto(_ActionElement*, itor, m_lpActionElem)
	{
		if (pp(itor) != NULL)
			if (pp(itor)->pTarget == target)
			{
				pp(itor)->bPaused = false;
				break;
			}
	}
}

void WPJActionManager::ResumeAllTarget()
{
	foreach_in_list_auto(_ActionElement*, itor, m_lpActionElem)
	{
		if (pp(itor) != NULL)
			pp(itor)->bPaused = false;
	}
}

void WPJActionManager::Update(float dt)
{
	foreach_in_list_auto(_ActionElement*, itor, m_lpActionElem)
	{
		if (pp(itor) != NULL)
			pp(itor)->Update(dt);
	}
}

WPJActionManager::~WPJActionManager()
{
	foreach_in_list_auto(_ActionElement*, itor, m_lpActionElem)
	{
		if (*itor != NULL)
			delete *itor;
	}

	m_lpActionElem.clear();
}
