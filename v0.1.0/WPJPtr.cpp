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

	// 承接引用次数和
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
	// 引用计数为0时调用析构，释放对应的数据
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
	// 复制构造函数目标是复制最底层的数据，因此需要深度复制WPJObject，再构造WPJPtr
	// 对于WPJPtr原本保存的内容进行释放
	ASSERT(&orig != NULL);

	if (this != &orig)
	{
		this->m_wpjSafePtr->Release();

		// To-do: 添加复制操作的代码
	}

}

WPJObject* WPJPtr::operator->()
{
	return m_wpjSafePtr->m_ptr;
}

WPJPtr& WPJPtr::operator= (const WPJPtr& rhs)
{
	// 赋值操作符不进行复制操作，只是简单的指针指向相同的WPJObject
	ASSERT(&rhs != NULL);

	// 之前引用的内容要取消
	if (m_wpjSafePtr != NULL)
		m_wpjSafePtr->Release();

	// 添加新的引用
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
	// 计数器减少引用次数
	m_wpjSafePtr->Release();

#ifndef GC_OPEN
	if (m_wpjSafePtr->m_uReference == 0)
		delete m_wpjSafePtr;
#endif
}
