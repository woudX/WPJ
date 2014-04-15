#ifndef _H_WPJOBJECT
#define _H_WPJOBJECT

#include "WPJCopying.h"
#include "WPJMacros.h"

NS_WPJ_BEGIN

class WPJObject : WPJCopying
{
private:
	U_INT m_uReference;
	WPJ_PROPERTY(bool, m_bIsLive, bIsLive)
	WPJ_PROPERTY(bool, m_bInPool, bInPool)

public:
	int test_data;
	WPJObject();
	WPJObject(int val);

	void Retain();
	void Release();

	U_INT GetRefCount();

	WPJObject *GetSharedPtr();
	WPJObject *GetCopiedPtr();
	virtual WPJObject* DupCopy();
	virtual U_INT GetSize();

	static WPJObject *CreateNewObject();
	static WPJObject *CreateNewObject(bool t_bInPool);
};

typedef void (WPJObject::*SEL_SCHEDULE)(float);

#define schedule_selector(_SELECTOR) (SEL_SCHEDULE)(&_SELECTOR)



class WPJAnime : public WPJObject
{
public:
	WPJObject *DupCopy();
	virtual U_INT GetSize();
	int animeData;
	WPJAnime();
	WPJAnime(int animeVal, int val);
	void ofTest(float a);
};

NS_WPJ_END

#endif

