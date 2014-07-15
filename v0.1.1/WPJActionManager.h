#ifndef _H_WPJACTIONMANAGER
#define _H_WPJACTIONMANAGER

#include "WPJStdafx.h"
#include "WPJMacros.h"
#include "WPJAction.h"

NS_WPJ_BEGIN

class _ActionElement
{
public:
	WPJNode *pTarget;
	std::list<WPJAction*> m_lpActions;
	bool bPaused;

	void ClearAllActions();
	void AddAction(WPJAction *pAction);
	void Update(float dt);
	~_ActionElement();
};

class WPJActionManager : public WPJObject
{
public:
	static WPJActionManager *GetsharedInst();
	void AddAction(WPJNode *pNode, WPJAction *pAction, bool bPaused);
	void RemoveAllAction();
	void RemoveAllActionFromTarget(WPJNode *target);
	void PauseTarget(WPJNode *target);
	void ResumeTarget(WPJNode *target);
	void PauseAllTarget();
	void ResumeAllTarget();
	virtual void Update(float dt);
	~WPJActionManager();
protected:
	WPJActionManager();
private:
	static WPJActionManager *m_pInst;
	std::list<_ActionElement*> m_lpActionElem;
};

NS_WPJ_END

#endif