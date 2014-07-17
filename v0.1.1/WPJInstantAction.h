#ifndef _H_WPJINSTANTACTION
#define _H_WPJINSTANTACTION

#include "WPJStdafx.h"
#include "WPJMacros.h"
#include "WPJAction.h"

NS_WPJ_BEGIN

/**
 *	Birefly, WPJInstantAction is the base of instant actions series
 *	so, don't create this action directly, please use implement class
 */
class WPJInstantAction : public WPJFiniteAction
{
public:
	static WPJInstantAction *CreateNewObject();
	WPJInstantAction();

	virtual WPJObject *DupCopy(WPJZone *zone);
	WPJInstantAction *Copy();
	virtual void Update(float dt);
	virtual void Step(float dt);
	virtual bool IsDone();
	virtual void StartWithTarget(WPJNode *target);

	virtual ~WPJInstantAction();
protected:
	bool m_bIsDone;
	float m_fElapsed;
};

/**
 *	WPJPlaceBy can place a WPJNode to a certain position directly with origin place
 */
class WPJPlaceBy : public WPJInstantAction
{
public:
	WPJPlaceBy();
	WPJPlaceBy(WPJPoint &point);

	virtual WPJObject *DupCopy(WPJZone *zone);
	WPJPlaceBy *Copy();
	virtual void Update(float dt);
	virtual void StartWithTarget(WPJNode *target);
	virtual WPJFiniteAction *Reverse();

	static WPJPlaceBy *Create(WPJPoint& position);

private:
	WPJPoint m_obDeltaPos;
	WPJPoint m_obStartPos;
	WPJPoint m_obEndPos;
};

/**
 *	WPJCallFunc can callback select target's function
 *	
 *	for example: (m_pSelectTarget->*pCallFunc)(NULL)
 */

class WPJCallFunc : public WPJInstantAction
{
public:
	WPJCallFunc();
	virtual ~WPJCallFunc();
	void Init(WPJNode *pSelectTarget, SEL_CALLFUNC pCallFunc);

	virtual WPJObject *DupCopy(WPJZone *zone);
	WPJCallFunc *Copy();
	virtual WPJFiniteAction *Reverse();
	virtual void StartWithTarget(WPJNode *target);
	virtual void Update(float dt);
	virtual void Execute();

	static WPJCallFunc *Create();
	static WPJCallFunc *Create(WPJNode *pSelectTarget, SEL_CALLFUNC pCallFunc);

protected:
	WPJNode *m_pSelectTarget;

	//	only one var is useful
	union
	{
		SEL_CALLFUNC m_pCallFunc;
		SEL_CALLFUNCN m_pCallFuncN;
		SEL_CALLFUNCND m_pCallFuncND;
		SEL_CALLFUNCO m_pCallFuncO;
	};
};


/**
 *	WPJCallFuncN can callback a select target's function with a WPJObject ptr
 *	for example : (m_pSelectTarget->*m_pCallFuncN)(m_pObject)
 */
class WPJCallFuncO : public WPJCallFunc
{
public:
	WPJCallFuncO();
	~WPJCallFuncO();

	void Init(WPJNode *pSelectTarget, SEL_CALLFUNCO pCallFuncO, WPJObject *pObject);
	virtual WPJObject *DupCopy(WPJZone *zone);
	WPJCallFuncO *Copy();
	void Execute();

	static WPJCallFuncO *Create();
	static WPJCallFuncO *Create(WPJNode *pSelectTarget, SEL_CALLFUNCO pCallFuncO, WPJObject *pObject);

protected:
	WPJObject *m_pObject;
};

/**
 *	WPJCallFuncN can callback a select target's function with target ptr
 *
 *	for example : (m_pSelectTarget->*m_pCallFuncN)(m_pTarget)
 */
class WPJCallFuncN : public WPJCallFunc
{
public:
	WPJCallFuncN();

	void Init(WPJNode *pSelectTarget, SEL_CALLFUNCN pCallFuncN);
	virtual WPJObject *DupCopy(WPJZone *zone);
	WPJCallFuncN *Copy();
	virtual void Execute();

	static WPJCallFuncN *Create();
	static WPJCallFuncN *Create(WPJNode *pSelectTarget, SEL_CALLFUNCN pCallFuncN);
};

/**
 *	WPJCallFuncND call callback a select target's function with target ptr
 *	and a data ptr, notice that data ptr's type is void*
 *
 *	for examlpe : (m_pSelectTarget->*m_pCallFuncND)(m_pTarget,data)
 */

class WPJCallFuncND : public WPJCallFuncN
{
public:
	WPJCallFuncND();

	void Init(WPJNode *pSelectTarget, SEL_CALLFUNCND pCallFuncND, void *pData);
	virtual WPJObject *DupCopy(WPJZone *zone);
	WPJCallFuncND *Copy();
	virtual void Execute();
	
	WPJCallFuncND *Create();
	WPJCallFuncND *Create(WPJNode *pSelectTarget, SEL_CALLFUNCND pCallFuncND, void *pData);

	virtual ~WPJCallFuncND();
protected:
	void *m_pData;
};

NS_WPJ_END

#endif