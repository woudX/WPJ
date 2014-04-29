#ifndef _H_WPJNODE
#define _H_WPJNODE

#include "WPJObject.h"
#include "WPJMacros.h"
#include "WPJScheduler.h"
#include "WPJGeometry.h"

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
	- Children and Parent	¡Ì
	- Event Callbacks		¡Ì
	- Actions
	- Scheduler and Timer	¡Ì
	- Transformation
	- Coordinate Converters
 */

class WPJScheduler;
class WPJPoint;

class WPJNode : public WPJObject
{
public:

	/// Constructor and Distructor
	static WPJNode *CreateNewObject();
	virtual bool Init();
	~WPJNode();

	/// Inherited Method
	virtual void GetSharedPtr(WPJNode* &object);
	virtual WPJNode *GetCopiedPtr();
	virtual WPJNode *DupCopy();
	virtual U_INT	GetSize();

	/// Getter And Setter
	virtual void SetRotation(float fx, float fy);
	virtual void SetScale(float fx, float fy);
	virtual void SetPosition(float fx, float fy);
	virtual void SetAnchorPoint(float fx, float fy);

	/// Event Callback
	/**
	 *	Event Callback Contains the method called atuomatically when WPJNode enter/exit the "stage"
	 *	Thet are:
	 *	- OnEnter
	 *	- OnEnterTransitionDidFinish
	 *	- OnExit
	 *	- OnExitTransitionDidStart
	 */

	// If this node enter the "stage", this event will be called automatically
	// While the event running, you can access 'brothers/sisters' by parents pointer
	virtual void OnEnter();

	// If this node enter the "stage", this event will be called automatically
	// This method contain the effect when node enter
	virtual void OnEnterTransitionDidFinish();

	// If this node exit the "stage", this event will be called automatically
	// While the event exiting, you can access 'brothers/sisters' by parents pointer
	virtual void OnExit();

	// If this node exit the "stage", this event will be called automatically
	// This method contain the effect when node exit
	virtual void OnExitTransitionDidStart();

	/// Children And Parent
	/**
	 *	WPJNode provide 3 kinds of method to operate children and parent to construct Drawing-Tree
	 *  They are:
	 *	- AddChild (ChildNode, zOrder, tag)
	 *	- Get/Set series
	 *	- Remove series (When remove occured, all actions and schedules should be cleanup)
	 */

	// Add a child
	virtual void AddChild(WPJNode *p_pChild);

	// Add a child with zOrder
	virtual void AddChild(WPJNode *p_pChild, int p_izOrder);

	// Add a child with zOrder and Tag
	virtual void AddChild(WPJNode *p_pChild, int p_izOrder, int p_iTag);

	// Get child by it's tag
	virtual WPJNode *GetChildByTag(int p_iTag);

	// Get a reference of childList
	virtual std::list<WPJNode* >& GetAllChild();

	// Get child count
	virtual U_INT GetChildCount();

	// Remove a child (Cleanup is default to True)
	// If not cleanup, child's schedules and actions won't be released
	virtual void RemoveChild(WPJNode *p_pChild, bool p_bCleanup = true);

	// Remove this node from parent (Cleanup is default to True)
	// If not cleanup, child's schedules and actions won't be released
	virtual void RemoveFromParent(bool p_bCleanUp = true);

	// Remove a child by tag (Cleanup is default to True)
	// If not cleanup, child's schedules and actions won't be released
	virtual void RemoveChildByTag(int p_iTag, bool p_bCleanup = true);

	// Remove all child (Cleanup is default to True)
	// If not cleanup, child's schedules and actions won't be released
	virtual void RemoveAllChild(bool p_bCleanup = true);
	
	/// Scheduler And Timer
	/**
	 *	WPJNode contain a scheduler class therefore it only packaged Scheduler's interfaces but 
	 *	not realize them.
	 *	Using These packaged interfaces to operator scheduler indirectly
	 *	More details information about these interfaces in WPJScheduler.h
	 */

	bool IsScheduled(SEL_SCHEDULE pfnSelector);

	// Schedule a SEL_SCHEDULE and will be called every frame
	// Recommend to use Update if these code need to be called every frame
	void Schedule(SEL_SCHEDULE pfnSelector);

	// Schedule a SEL_SCHEDULE and will be called every 'interval' frame
	void Schedule(SEL_SCHEDULE pfnSelector, float fInterval);

	// Schedule a SEL_SCHEDULE, after a delay it will be called every 'interval' frame, total nRepeat
	void Schedule(SEL_SCHEDULE pfnSelector, float fInterval, U_INT nRepeat, float fDelay);

	// Schedule a SEL_SCHEDULE, after a delay it will be called only once
	void ScheduleOnce(SEL_SCHEDULE pfnSelector, float fDelay);

	// Schedule Update with prority, if called with no paras, the proprity is default to 0
	// After using this method, Update method will be called every frame automatically
	void ScheduleUpdate(int prority = 0);

	// Unschedule Update
	// Call if you don't want Update to be called automatically
	void UnscheduleUpdate();

	// Unschedule a SEL_SCHEDULE in WPJNode
	void Unschedule(SEL_SCHEDULE pfnSelector);

	// Unschedule all this node's selectors which has already scheduled in m_pSchedule
	void UnscheduleAllSelectors();
	
	// Stop all schedules and actions about this node
	void PauseScheduleAndAction();

	// Resume all schedules and actions about this node
	void ResumeScheduleAndAction();
	
	/// Update
	virtual void Update(float dt);
	
protected:
	WPJNode();

	int m_iZOrder;
	int m_iTag;
	bool m_bIsRunning;

	void CleanUp();
	void DetachChild(WPJNode *p_pChild, bool p_bCleanup);

	std::list<WPJNode* > m_lChildList;
	
	WPJ_PROPERTY_BY_REF(WPJPoint, m_obAnchorPoint, AnchorPoint)
	WPJ_PROPERTY_BY_REF(WPJPoint, m_obPosition, Position)

	WPJ_PROPERTY(WPJNode*, m_pParent, Parent)
	WPJ_PROPERTY(WPJScheduler*, m_pScheduler, Scheduler)
	WPJ_PROPERTY(float, m_fRotationX, RotationX)
	WPJ_PROPERTY(float, m_fRotationY, RotationY)
	WPJ_PROPERTY(float, m_fScaleX, ScaleX)
	WPJ_PROPERTY(float, m_fScaleY, ScaleY)
	WPJ_PROPERTY(bool, m_bVisible, Visible)
private:
	
	
};

NS_WPJ_END

#endif