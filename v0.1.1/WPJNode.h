#ifndef _H_WPJNODE
#define _H_WPJNODE

#include "WPJMacros.h"
#include "WPJObject.h"
#include "WPJScheduler.h"

#include "WPJGeometry.h"
#include "WPJProtocols.h"

NS_WPJ_BEGIN

class WPJAction;
class WPJActionManager;
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
	- Actions				¡Ì
	- Scheduler and Timer	¡Ì
	- Draw					¡Ì
	- Transformation			¡Ì
	- Coordinate Converters	¡Ì
 */

enum WPJ_COORDINATE_SYSTEMS {
	WPJ_COORDINATE_WORLD		= 0,
	WPJ_COORDINATE_RELATIVE		= 1,
	WPJ_COORDINATE_ALLEGRO		= 2,
	WPJ_COORDINATE_NUMS
};


class WPJNode : public WPJObject
{
public:

	/// Constructor and Distructor
	static WPJNode *CreateNewObject();
	virtual bool Init();
	~WPJNode();

	/// Inherited Method
	virtual void GetSharedPtr(WPJNode* &object);
	WPJNode *Copy();
	virtual WPJObject *DupCopy(WPJZone *zone);
	virtual U_INT	GetSize();
	virtual void Release();

	/// Getter And Setter
	/**
	 *	These are not all of the getter and setter, some are defined by marco, for example,
	 *	WPJ_PROPERTY define getter/setter, more detail info can be seen in 'WPJMarcos.h'
	 */
	virtual void SetScale(float fx, float fy);
	virtual void SetPosition(float fx, float fy);
	virtual void SetAnchorPoint(float fx, float fy);
	virtual bool IsRunning();

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
	
	/// Draw
	/**
	 *	Actually, draw method is the package of allegro, but the user needn't to learn how to
	 *	use allegro
	 */

	// Draw method, override this
	virtual void Draw();

	// Visits this node's children and draw them recursively
	virtual void Visit();

	// Sort all childrens by iOrder, bigger order will draw after
	virtual void SortAllChildren();
	bool CmpMethod(const WPJNode *a, const WPJNode *b);
	bool operator() (const WPJNode *a, const WPJNode *b);

	//	After ignore anchor point, node's final position will only consider position but not 
	//	position && anchor point
	//	The default is false, but it always be true on WPJLayer because Layer needn't to consider
	//	anchor point, the position(0, 0) can decide where to draw
	void SetIgnoreAnchorPoint(bool bValue);
	bool IsIgnoreAnchorPoint();

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
	virtual void CleanUp();

	/// Action
	/**
	 *	Action is controlled by WPJActionManager, there is only package the interface 
	 *	of the WPJActionManager
	 */

	// Run a action with this unit
	void RunAction(WPJAction *pAction);

	/// Coordinate Convertion
	/**
	 *	In WPJ, there are 3 kinds of coordinate systems, they are:
	 *	WPJ_COORDINATE_WORLD	: discript node position in real world
	 *	WPJ_COORDINATE_RELATIVE : discript node position in relative system
	 *	WPJ_COORDINATE_ALLEGRO	: discript node position in allegro system
	 *
	 *	We provide these methods to transform coordinate:
	 *				WPJ_COORDINATE_RELATIVE	->	WPJ_COORDINATE_WORLD
	 *				WPJ_COORDINATE_RELATIVE ->	WPJ_COORDINATE_ALLEGRO
	 *				WPJ_COORDINATE_WORLD	->	WPJ_COORDINATE_ALLEGRO - NO_USE
	 *				
	 */

	//	Convert node's coordinate system from relative to world
	WPJPoint RelativeConvertToWorld();

	//	Convert node's coordinate system from relative to allegro system
	//	Usually, it's used for drawing
	virtual WPJPoint RelativeConvertToAllegro();

protected:
	WPJNode();

	int m_iZOrder;
	int m_iTag;
	bool m_bIsRunning;

	// If anchor point is ignored , the final position will only consider position
	bool m_bIgnoreAnchorPoint;

	void DetachChild(WPJNode *p_pChild, bool p_bCleanup);

	std::list<WPJNode* > m_lChildList;
	WPJ_PROPERTY(U_CHAR, m_ucCoordinateSystem, CoordinateSystem)
	WPJ_PROPERTY(WPJNode*, m_pParent, Parent)                                                                                                                               
	WPJ_PROPERTY(WPJScheduler*, m_pScheduler, Scheduler)
	WPJ_PROPERTY(WPJActionManager*, m_pActionManager, ActionManager)
	WPJ_PROPERTY(float, m_fScaleX, ScaleX)
	WPJ_PROPERTY(float, m_fScaleY, ScaleY)
	WPJ_PROPERTY(bool, m_bVisible, Visible)
	
	WPJ_PROPERTY_BY_REF(WPJPoint, m_obAnchorPoint, AnchorPoint)		// transition center, default (0.5, 0.5)
	WPJ_PROPERTY_BY_REF(WPJPoint, m_obPosition, Position)			// position
	WPJ_PROPERTY_BY_REF(WPJRect, m_obRegion, Region)				// region, default (0, 0, 0, 0) - show all
	WPJ_PROPERTY_BY_REF(WPJSize, m_obContentSize, ContentSize)		// node untransmit size
	WPJ_PROPERTY(float, m_fAngle, Angle)							// rotate, default 0
	
private:
};

class WPJNodeRGBA : public WPJNode, public WPJRGBAProtocol
{
public:
	WPJNodeRGBA();
	static WPJNodeRGBA *CreateNewObject();
	virtual WPJObject *DupCopy(WPJZone *zone);
	WPJNodeRGBA *Copy();
	virtual ~WPJNodeRGBA();
	virtual void Release();

	virtual U_CHAR GetDisplayOpacity();
	virtual void UpdateDisplayOpacity(U_CHAR opacity);
	virtual U_CHAR GetOpacity();
	virtual void SetOpacity(U_CHAR opacity);

	virtual const wpColor3B& GetDisplayColor();
	virtual void UpdateDisplayColor(const wpColor3B& color);
	virtual const wpColor3B& GetColor();
	virtual void SetColor(const wpColor3B& color);

	virtual bool IsOpacityModifyRGB();
	virtual void SetOpacityModifyRGB(bool bValue);

	virtual bool IsCascadeColorEnabled();
	virtual void SetCascadeColorEnabled(bool bValue);
	virtual bool IsCascadeOpacityEnabled();
	virtual void SetCascadeOpacityEnabled(bool bValue);

protected:
	U_CHAR m_displayOpacity;	//	tint opacity
	U_CHAR m_realOpacity;		//	selfopacity
	wpColor3B m_displayColor;	//	tint color
	wpColor3B m_realColor;		//	self color
	bool m_bCascadeColorEnabled;
	bool m_bCascadeOpacityEnabled;
};

NS_WPJ_END

#endif