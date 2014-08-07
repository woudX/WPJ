#ifndef _H_WPJOBJECT
#define _H_WPJOBJECT

#include "WPJCopying.h"
#include "WPJMacros.h"

NS_WPJ_BEGIN

/**
	WPJObject Class is the root of inherit tree in this project, it define
	many methods and variables to provide basic support for the derived class
*/

class WPJNode;

class WPJObject : public WPJCopying
{
private:

	// the count of reference
	WPJ_PROPERTY_READONLY(U_INT,m_uReference,Reference)

	// if alive
	WPJ_PROPERTY(bool, m_bIsLive, bIsLive)

	// if in Object Pool
	WPJ_PROPERTY(bool, m_bInPool, bInPool)

public:
	WPJObject();

	void Retain();
	void Release();
	void AutoRelease();

	static WPJObject *CreateNewObject();
	static WPJObject *CreateNewObject(bool t_bInPool);

	virtual void GetSharedPtr(WPJObject* &object);
	virtual WPJObject *GetCopiedPtr();

	//	In WPJObject, Dupcopy is no use because this class is only use
	//	to count how many times this class has been quoted
	//	When it's subclass call DupCopy, all data in WPJObject will be init
	virtual WPJObject* DupCopy(WPJZone *zone);
	
	//	Get This Object Size
	virtual U_INT GetSize();


	virtual void Update(float dt);
	virtual ~WPJObject();
};

typedef void (WPJObject::*SEL_SCHEDULE)(float);
typedef void (WPJObject::*SEL_CALLFUNC)();
typedef void (WPJObject::*SEL_CALLFUNCN)(WPJNode*);
typedef void (WPJObject::*SEL_CALLFUNCND)(WPJNode*, void *);
typedef void (WPJObject::*SEL_CALLFUNCO)(WPJObject*);

#define schedule_selector(_SELECTOR) (SEL_SCHEDULE)(&_SELECTOR)
#define callfunc_selector(_SELECTOR) (SEL_CALLFUNC)(&_SELECTOR)
#define callfuncN_selector(_SELECTOR) (SEL_CALLFUNCN)(&_SELECTOR)
#define callfuncND_selector(_SELECTOR) (SEL_CALLFUNCND)(&_SELECTOR)
#define callfuncO_selector(_SELECTOR) (SEL_CALLFUNCO)(&_SELECTOR)

class WPJAnime : public WPJObject
{
public:
	WPJAnime();
	WPJAnime(int animeVal);

	static WPJAnime *CreateNewObject();

	WPJObject *DupCopy();
	virtual U_INT GetSize();
	int animeData;
	
	void ofTest(float a);
};

NS_WPJ_END

#endif

