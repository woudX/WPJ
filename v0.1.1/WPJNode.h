#ifndef _H_WPJNODE
#define _H_WPJNODE

#include "WPJObject.h"
#include "WPJMacros.h"
#include "WPJScheduler.h"

NS_WPJ_BEGIN

/**
 *	Brief WPJNode is the core class of all kinds of derived classes, it contains basic draw params and method
	so that all draw classes is WPJNode.

	The WPJNode main function are:
	1. It can contain other WPJNode (Drawing Tree consisting of different WPJNodes )
	2. It can schedule/unschedule callback function
	3. It contain basic position params (Point, Rotate, etc.)
	4. It can execute actions

	WPJNode can be divide into these parts:
	- Setters & Getters for Graphic Properties
	- Children and Parent ¡Ì
	- Event Callbacks
	- Actions
	- Scheduler and Timer ¡Ì
	- Transformation
	- Coordinate Converters
 */

class WPJScheduler;

class WPJNode : public WPJObject
{
public:

	/// Factory Method
	WPJNode *CreateNewObject();

	/// Inherited Method
	virtual void GetSharedPtr(WPJNode* &object);
	virtual WPJNode *GetCopiedPtr();
	virtual WPJNode *DupCopy();
	virtual U_INT	GetSize();

	/// Children And Parent
	/**
	 *	WPJNode provide 3 kinds of method to operate children and parent to construct Drawing-Tree
	 *  They are:
	 *	- AddChild (ChildNode, zOrder, tag)
	 *	- Get/Set series
	 *	- Remove series (When remove occured, all actions and schedules should be cleanup)
	 */


	virtual void AddChild(WPJNode *p_pChild);
	virtual void AddChild(WPJNode *p_pChild, int p_izOrder);
	virtual void AddChild(WPJNode *p_pChild, int p_izOrder, int p_iTag);

	virtual WPJNode *GetChildByTag(int p_iTag);
	virtual std::list<WPJNode* >& GetAllChild();
	virtual U_INT GetChildCount();

	virtual void RemoveChild(WPJNode *p_pChild, bool p_bCleanup);
	virtual void RemoveFromParent();
	virtual void RemoveFromParentAndCleanup();
	virtual void RemoveChildByTag(int p_iTag, bool p_bCleanup);
	virtual void RemoveAllChild(bool p_bcleanup);
	
	/// Scheduler And Timer
	/**
	 *	WPJNode contain a scheduler class therefore it only packaged Scheduler's interfaces but 
	 *	not realize them.
	 *	Using These packaged interfaces to operator scheduler indirectly
	 *	More details information about these interfaces in WPJScheduler.h
	 */

	bool IsScheduled(SEL_SCHEDULE pfnSelector);
	void Schedule(SEL_SCHEDULE pfnSelector);
	void Schedule(SEL_SCHEDULE pfnSelector, float fInterval);
	void Schedule(SEL_SCHEDULE pfnSelector, float fInterval, U_INT nRepeat, float fDelay);
	void ScheduleOnce(SEL_SCHEDULE pfnSelector, float fDelay);

	void Unschedule(SEL_SCHEDULE);
	void UnscheduleAllSelectors();
	
	void StopScheduleAndAction();
	void ResumeScheduleAndAction();
	
	/// Update
	virtual void Update(float dt);
	~WPJNode();
protected:
	WPJNode();

	int m_iZOrder;
	int m_iTag;
	bool m_bIsRunning;

	void CleanUp();
	void DetachChild(WPJNode *p_pChild, bool p_bCleanup);
private:
	std::list<WPJNode* > m_lChildList;

	WPJ_PROPERTY(WPJNode*, m_pParent, Parent)
	WPJ_PROPERTY(WPJScheduler*, m_pScheduler, Scheduler);
};

NS_WPJ_END

#endif