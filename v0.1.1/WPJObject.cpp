#include "WPJObject.h"
#include "WPJGarbageCollection.h"

USING_NS_WPJ;

WPJObject::WPJObject()
	:m_uReference(1)
	,bIsLive(true)
	,bInPool(false)
{

}

WPJObject::WPJObject(int val)
	:test_data(val)
	,m_uReference(1)
	,bIsLive(true)
	,bInPool(false)
{

}

WPJObject* WPJObject::DupCopy()
{
	WPJObject* newObj = new WPJObject();
	newObj->test_data = test_data;

	return newObj;
}

U_INT WPJObject::GetSize()
{
	return sizeof(*this);
}

void WPJObject::Retain()
{
	++m_uReference;
}

void WPJObject::Release()
{
	--m_uReference;
	bIsLive = false;
}

U_INT WPJObject::GetRefCount()
{
	return m_uReference;
}

WPJObject *WPJObject::GetSharedPtr()
{
	Retain();

	return this;
}

WPJObject *WPJObject::GetCopiedPtr()
{
	return DupCopy();
}

WPJObject *WPJObject::CreateNewObject()
{
	WPJObject *object = new WPJObject();
	WPJGC::GetSharedInst()->AddPtr(object);

	return object;
}

WPJObject *WPJObject::CreateNewObject(bool t_bInPool = false)
{
	WPJObject *object = new WPJObject();
	object->bInPool = t_bInPool;
	WPJGC::GetSharedInst()->AddPtr(object);

	return object;
}


WPJAnime::WPJAnime()
{

}

WPJAnime::WPJAnime(int animeVal, int val):WPJObject(val),animeData(animeVal)
{

}

WPJObject* WPJAnime::DupCopy()
{
	WPJAnime *newAnime = new WPJAnime();
	newAnime->animeData = animeData;
	newAnime->test_data = test_data;

	return newAnime;
}

U_INT WPJAnime::GetSize()
{
	return sizeof(*this);
}