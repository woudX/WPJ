#include "WPJPtr.h"
#include "WPJGarbageCollection.h"

USING_NS_WPJ;

/************************************************************************/
/* WPJSafePtr Code                                                      */
/************************************************************************/
WPJSafePtr::WPJSafePtr()
{

}

WPJSafePtr::WPJSafePtr(WPJObject *wpj_obj):m_uReference(1),m_ptr(wpj_obj),m_ifInPool(false)
{
	
}

void WPJSafePtr::Retain()
{
	++m_uReference;
}

void WPJSafePtr::Release()
{
	--m_uReference;
}

void WPJSafePtr::SetPtr(WPJObject* wpj_obj)
{
	ASSERT(wpj_obj != NULL);

	m_ptr = wpj_obj;
}

WPJSafePtr& WPJSafePtr::operator= (const WPJSafePtr& rhs)
{
	ASSERT(&rhs != NULL);

	// �н����ô�����
	m_uReference = rhs.m_uReference;
	m_ptr = m_ptr;

	return *this;
}

WPJObject* WPJSafePtr::DupCopy()
{
	return NULL;
}

WPJSafePtr::~WPJSafePtr()
{
	// ���ü���Ϊ0ʱ�����������ͷŶ�Ӧ������
	delete m_ptr;
}

/************************************************************************/
/* WPJPtr Code                                                          */
/************************************************************************/

WPJPtr::WPJPtr():m_wpjSafePtr(NULL)
{

}

WPJPtr::WPJPtr(WPJObject *obj_ptr):m_wpjSafePtr(new WPJSafePtr(obj_ptr))
{
	WPJGC::GetSharedInst()->AddPtr(this->m_wpjSafePtr);
}

WPJPtr::WPJPtr(const WPJPtr& orig)
{
	// ���ƹ��캯��Ŀ���Ǹ�����ײ�����ݣ������Ҫ��ȸ���WPJObject���ٹ���WPJPtr
	// ����WPJPtrԭ����������ݽ����ͷ�
	ASSERT(&orig != NULL);

	if (this != &orig)
	{
		this->m_wpjSafePtr->Release();

		// To-do: ��Ӹ��Ʋ����Ĵ���
	}

}

WPJObject* WPJPtr::operator->()
{
	return m_wpjSafePtr->m_ptr;
}

WPJPtr& WPJPtr::operator= (const WPJPtr& rhs)
{
	// ��ֵ�����������и��Ʋ�����ֻ�Ǽ򵥵�ָ��ָ����ͬ��WPJObject
	ASSERT(&rhs != NULL);

	// ֮ǰ���õ�����Ҫȡ��
	if (m_wpjSafePtr != NULL)
		m_wpjSafePtr->Release();

	// ����µ�����
	m_wpjSafePtr = rhs.m_wpjSafePtr;
	m_wpjSafePtr->Retain();
	
	return *this;
}

WPJObject* WPJPtr::GetPtr()
{
	return m_wpjSafePtr->m_ptr;
}

void WPJPtr::SetPtr(WPJObject *ptr)
{

}

WPJObject* WPJPtr::DupCopy()
{
	return NULL;
}

WPJPtr::~WPJPtr()
{
	// �������������ô���
	m_wpjSafePtr->Release();

#ifndef GC_OPEN
	if (m_wpjSafePtr->m_uReference == 0)
		delete m_wpjSafePtr;
#endif
}
