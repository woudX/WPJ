#include "WPJObject.h"
#include "WPJGarbageCollection.h"

USING_NS_WPJ;

WPJObject::WPJObject()
	:m_uReference(1)
	,m_bIsLive(true)
	,m_bInPool(false)
{

}

bool WPJObject::GetbIsLive()
{
	return m_bIsLive;
}

void WPJObject::SetbIsLive(bool var)
{
	m_bIsLive = var;
}

bool WPJObject::GetbInPool()
{
	return m_bInPool;
}

void WPJObject::SetbInPool(bool var)
{
	m_bInPool = var;
}

WPJObject *WPJObject::DupCopy(WPJZone *zone)
{
	UN_USED_PARAM(zone);
	WPJLOG("[%s] WPJObject is not implement");
	ASSERT(0);
	
	return 0;
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

	if (m_uReference == 0)
	{
		//	if not define GC_OPEN, when a object delete, it must be removed
		//	from WPJGC watching list firstly
#if GC_TYPE == GC_WATCH
		WPJGC::GetSharedInst()->RemovePtr(this);
#endif
		
		delete this;
	}
		// m_bIsLive = false;
}

void WPJObject::AutoRelease()
{
	ASSERT(m_uReference > 0);
	WPJGC::GetSharedInst()->AddObject(this);

#if GC_TYPE != GC_CLOSE
	WPJGC::GetSharedInst()->AddPtr(this);
#endif
}


U_INT WPJObject::GetReference()
{
	return m_uReference;
}

void WPJObject::GetSharedPtr(WPJObject* &object)
{
	object = this;
	object->Retain();
}

WPJObject *WPJObject::GetCopiedPtr()
{
	return NULL;
}

WPJObject *WPJObject::CreateNewObject()
{
	WPJObject *object = new WPJObject();
	object->AutoRelease();

	return object;
}

WPJObject *WPJObject::CreateNewObject(bool t_bInPool = false)
{
	WPJObject *object = new WPJObject();
	object->m_bInPool = t_bInPool;

	WPJGC::GetSharedInst()->AddPtr(object);
	
	return object;
}

void WPJObject::Update(float dt)
{
	UN_USED_PARAM(dt);
	WPJLOG("[%s] Please implement this method!\n", _D_NOW_TIME__);
}

WPJObject::~WPJObject()
{

}

WPJAnime::WPJAnime()
{

}

WPJAnime::WPJAnime(int animeVal):animeData(animeVal)
{

}

WPJAnime *WPJAnime::CreateNewObject()
{
	WPJAnime *t_pAnime = new WPJAnime();
	WPJGC::GetSharedInst()->AddPtr(t_pAnime);

	return t_pAnime;
}

WPJObject* WPJAnime::DupCopy()
{
	WPJAnime *newAnime = new WPJAnime();
	newAnime->animeData = animeData;

	return newAnime;
}

U_INT WPJAnime::GetSize()
{
	return sizeof(*this);
}

void WPJAnime::ofTest(float a)
{
	WPJLOG("%f\n",a);
}