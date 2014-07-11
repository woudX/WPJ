#ifndef _H_WPJACTION
#define _H_WPJACTION

#include "WPJStdafx.h"
#include "WPJMacros.h"
#include "WPJNode.h"

NS_WPJ_BEGIN
/**
 *	WPJAction is used to create unit action, actually it is a interface class.
 *	By defining all kinds of interfaces, we can complete more kinds actions
 *	
 	!!![NOTICE] you are better not instance this class because it's a interface class
 */
class WPJAction : public WPJObject {
public:
	// Constructor and Desctructor
	static WPJAction *CreateNewObject();
	WPJAction();
	virtual ~WPJAction();

	// Inherit Methods
	virtual void GetSharedPtr(WPJAction* &object);
	virtual WPJObject *DupCopy(WPJZone *zone);
	WPJAction *Copy();

	virtual void Release();
	virtual void Update(float dt);

	// Main Methods
	virtual bool IsDone();
	virtual void StartWithTarget(WPJNode *target);
	virtual void Step(float dt);
	virtual void Stop();
	
protected:
	WPJ_PROPERTY(int,m_nTag,Tag)
	WPJ_PROPERTY(WPJNode*,m_pTarget,Target)
};

class WPJFiniteAction : public WPJAction
{
public:
	// Constructor and Destructor
	static WPJFiniteAction *CreateNewObject();
	WPJFiniteAction();

	virtual WPJObject *DupCopy(WPJZone *zone);
	WPJFiniteAction *Copy();
	virtual ~WPJFiniteAction();

	// Main Method
	virtual WPJFiniteAction *Reverse();

protected:
	WPJ_PROPERTY(float,m_fDuration,Duration)
};

NS_WPJ_END
#endif