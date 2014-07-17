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
	virtual WPJObject *DupCopy(WPJZone *zone);
	WPJIntervalAction *Copy();

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
	virtual ~WPJMoveBy();

	virtual WPJObject *DupCopy(WPJZone *zone);
	WPJMoveBy *Copy();

	virtual WPJIntervalAction *Reverse();
	virtual void StartWithTarget(WPJNode *target);
	virtual void Update(float dt);
	virtual void Stop();

	static WPJMoveBy *Create(float fDuration, const WPJPoint& deltaPos);
protected:
	WPJPoint m_obDeltaPositon;
	WPJPoint m_obStartPosition;
	WPJPoint m_obPreviousPosition;
};

/*
 * WPJMoveTo can move a WPJNode to a specific position (x,y)
 */
class WPJMoveTo : public WPJMoveBy
{
public:
	WPJMoveTo();
	WPJMoveTo(float fDuration, const WPJPoint& endPosition);
	virtual ~WPJMoveTo();

	virtual WPJObject *DupCopy(WPJZone *zone);
	WPJMoveTo *Copy();
	virtual void StartWithTarget(WPJNode *target);

	static WPJMoveTo *Create(float fDuration, const WPJPoint& endPosition);

private:
	WPJPoint m_obEndPosition;
};

/**
 *	WPJRotateBy can rotate a WPJNode fAngle in fDuration times 
 *	on the basis of origin angle
 */
class WPJRotateBy : public WPJIntervalAction
{
public:
	static WPJRotateBy *Create(float fDuration, float fAngle);

	WPJRotateBy();
	WPJRotateBy(float fDuration, float fAngle);
	virtual ~WPJRotateBy();

	virtual WPJObject *DupCopy(WPJZone *zone);
	WPJRotateBy *Copy();

	virtual WPJIntervalAction *Reverse();
	virtual void StartWithTarget(WPJNode *target);
	virtual void Update(float dt);
	virtual void Stop();

protected:
	float m_fDeltaAngle;
	float m_fStartAngle;
	float m_fPreviousAngle;
};

/**
 *	WPJRotateTo can rotate a WPJNode to fAngle in fDuration times
 */

class WPJRotateTo : public WPJRotateBy
{
public:
	WPJRotateTo();
	WPJRotateTo(float fDuration, float fAngle);
	virtual ~WPJRotateTo();

	virtual WPJObject *DupCopy(WPJZone *zone);
	WPJRotateTo *Copy();

	virtual void StartWithTarget(WPJNode *target);

	static WPJRotateTo *Create(float fDuration, float fAngle);

protected:
	float m_fEndAngle;
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
	virtual ~WPJWait();

	virtual WPJObject *DupCopy(WPJZone *zone);
	WPJWait *Copy();
	
	virtual void StartWithTarget(WPJNode *target);
	virtual void Update(float dt);
	virtual void Stop();

	static WPJWait *Create(float fDuration);
};

/**
 *	WPJSequence is a sequence of WPJFiniteAction, it can contain at least 
 *	one WPJFiniteAction, and they will be run with order.
 *
 *	Notice : the action in sequence don't have ticks, which means all actions
 *	will be called StartWithTarget() when created, if we don't this, the elapsed
 *	will be fault
 */

class WPJSequence : public WPJIntervalAction
{
public:
	WPJSequence();
	virtual ~WPJSequence();

	virtual WPJObject *DupCopy(WPJZone *zone);
	WPJSequence *Copy();

	virtual void StartWithTarget(WPJNode *target);
	virtual WPJIntervalAction *Reverse();
	virtual void Update(float dt);
	virtual void Stop();

	bool InitWithTwoActions(WPJFiniteAction *pAction1, WPJFiniteAction *pAction2);
	
	static WPJSequence *Create(WPJFiniteAction *pAction1, ...);
	static WPJSequence *CreateWithTwoActions(WPJFiniteAction *pAction1, WPJFiniteAction *pAction2);
	static WPJSequence *CreateWithVariableList(WPJFiniteAction *pAction1, va_list args);
private:
	WPJFiniteAction *m_pAction1, *m_pAction2;
	bool m_bInitAction1, m_bInitAction2;
	float m_fLastDt;
	float m_fSplit;
	int m_iLastRun;
};

/**
 *	WPJSpawn can run at least one action at the same time
 */

class WPJSpawn : public WPJIntervalAction
{
public:
	WPJSpawn();
	virtual ~WPJSpawn();

	virtual WPJObject *DupCopy(WPJZone* zone);
	WPJSpawn *Copy();

	virtual void StartWithTarget(WPJNode *target);
	virtual WPJIntervalAction *Reverse();
	virtual void Update(float dt);
	virtual void Stop();

	bool InitWithTwoActions(WPJFiniteAction *pAction1, WPJFiniteAction *pAction2);

	static WPJSpawn *Create(WPJFiniteAction *pAction1, ...);
	static WPJSpawn *CreateWithTwoActions(WPJFiniteAction *pAction1, WPJFiniteAction *pAction2);
	static WPJSpawn *CreateWithVariableList(WPJFiniteAction *pAction1, va_list args);
	
private:
	WPJFiniteAction *m_pAction1;
	WPJFiniteAction *m_pAction2;
};

/**
 *	WPJRepeat can run a WPJFiniteAction with n times (0 <= n <= MAX_INT), including WPJSequeue and WPJSpawn
 */
class WPJRepeat : public WPJIntervalAction
{
public:
	WPJRepeat();
	~WPJRepeat();

	virtual WPJObject *DupCopy(WPJZone *zone);
	WPJRepeat *Copy();
	virtual WPJIntervalAction *Reverse();

	virtual void StartWithTarget(WPJNode *target);
	virtual void Update(float dt);
	virtual void Stop();

	void InitWithAction(WPJFiniteAction *pAction, int iRepeatCount);
	static WPJRepeat *Create(WPJFiniteAction *pAction, int iRepeatCount);

private:
	WPJFiniteAction *m_pRepeatAction;
	int m_iRepeatCount;
	int m_iCompleteCount;
	float m_fNextDt;

};


NS_WPJ_END

#endif