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

	~WPJInstantAction();
protected:
	bool m_bIsDone;
	float m_fElapsed;
};

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


NS_WPJ_END

#endif