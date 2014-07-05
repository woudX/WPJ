#ifndef _H_WPJINTERVALACTION
#define _H_WPJINTERVALACTION

#include "WPJStdafx.h"
#include "WPJMacros.h"
#include "WPJAction.h"

NS_WPJ_BEGIN
/*
 * This class is used to make IntervalAction, as you can see, IntervalAction is derived from 
 * FiniteAction, and IntervalAction will derive many actions like MoveTo and FadeIn etc.
 *
 * The concrete classes like MoveTo only need to realize Update(), that's enough, other work 
 * is belong to IntervalActions Class
 */
class WPJIntervalAction : public WPJFiniteAction
{
public:
	// Constructor and Destructor
	static WPJIntervalAction *CreateNewObject();
	WPJIntervalAction();
	virtual ~WPJIntervalAction();

	// Inherited Methods
	virtual void Step(float dt);
	virtual WPJIntervalAction *Reverse();
	virtual bool IsDone();
	virtual void StartWithTarget(WPJNode *target);
	
	// Main Methods
	inline float GetElapsed() { return m_fElapsed; }
	inline void SetElapsed(float var) { m_fElapsed = var; }

protected:
	float m_fElapsed;
	bool m_bInitial;

};

/*
 * WPJMoveBy can move a WPJNode to a relative position by (x,y) and it's initial position
 */
class WPJMoveBy : public WPJIntervalAction
{
public:
	WPJMoveBy();
	WPJMoveBy(float fDuration, const WPJPoint& deltaPos);
	~WPJMoveBy();

	virtual WPJMoveBy *DupCopy();
	virtual WPJIntervalAction *Reverse();
	virtual void StartWithTarget(WPJNode *target);
	virtual void Update(float dt);
	
	static WPJMoveBy *Create(float fDuration, const WPJPoint& deltaPos);
protected:
	WPJPoint m_obDeltaPositon;
	WPJPoint m_obStartPoint;
	WPJPoint m_obPreviousPoint;
};

/*
 * WPJMoveTo can move a WPJNode to a specific position (x,y)
 */
class WPJMoveTo : public WPJMoveBy
{
public:
	WPJMoveTo();
	WPJMoveTo(float fDuration, const WPJPoint& endPosition);
	~WPJMoveTo();

	virtual WPJMoveTo *DupCopy();
	virtual void StartWithTarget(WPJNode *target);

	static WPJMoveTo *Create(float fDuration, const WPJPoint& endPosition);
};

/**
 *	WPJRotateBy can rotate a WPJNode fAngle in fDuration times 
 *	on the basis of origin angle
 */
class WPJRotateBy : public WPJIntervalAction
{
public:
	WPJRotateBy();
	WPJRotateBy(float fDuration, float fAngle);
	~WPJRotateBy();

	virtual WPJRotateBy *DupCopy();
	virtual WPJIntervalAction *Reverse();
	virtual void StartWithTarget(WPJNode *target);
	virtual void Update(float dt);

	float m_fDeltaAngle;
	float m_fStartAngle;
	float m_fPreviousAngle;

	static WPJRotateBy *Create(float fDuration, float fAngle);
};

/**
 *	WPJRotateTo can rotate a WPJNode to fAngle in fDuration times
 */

class WPJRotateTo : public WPJRotateBy
{
public:
	WPJRotateTo();
	WPJRotateTo(float fDuration, float fAngle);
	~WPJRotateTo();

	virtual WPJRotateTo *DupCopy();
	virtual void StartWithTarget(WPJNode *target);

	static WPJRotateTo *Create(float fDuration, float fAngle);
};

/**
 *	WPJWait can let WPJNode wait fDuration times, and continue to do action
 *	it often used in action sequence, e.g. like WPJSequence and WPJRepeat ...
 */

class WPJWait : public WPJIntervalAction
{
public:
	WPJWait();
	WPJWait(float fDuration);
	~WPJWait();

	virtual WPJWait *DupCopy();
	virtual void StartWithTarget(WPJNode *target);
	virtual void Update(float dt);

	static WPJWait *Create(float fDuration);
};

class WPJSequence : public WPJIntervalAction
{
public:
	WPJSequence();
	WPJSequence(WPJFiniteAction *pAction1, WPJFiniteAction *pAction2);
	~WPJSequence();

	virtual WPJSequence *DupCopy();
	virtual void StartWithTarget(WPJNode *target);
	virtual WPJIntervalAction *Reverse();
	virtual void Update(float dt);

	bool InitWithTwoActions(WPJFiniteAction *pAction1, WPJFiniteAction *pAction2);

	static WPJSequence *Create(WPJFiniteAction *pAction1, ...);
	static WPJSequence *CreateWithToActions(WPJFiniteAction *pAction1, WPJFiniteAction *pAction2);
	static WPJSequence *CreateWithVariableList(WPJFiniteAction *pAction1, va_list args);
private:
	WPJFiniteAction *m_pAction1, *m_pAction2;


};


NS_WPJ_END

#endif