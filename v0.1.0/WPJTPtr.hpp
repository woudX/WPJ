#ifndef _H_WPJTPTR
#define _H_WPJTPTR

#include "WPJMacros.h"
#include "WPJPtr.h"

NS_WPJ_BEGIN

template<class T>
class WPJTPtr : public WPJObject
{
private:
	WPJTPtr &operator =(const WPJTPtr &rhs) { return NULL; }	// 禁止赋值构造
	//WPJTPtr(const WPJTPtr &orig) { }	// 禁止复制构造

public:
	WPJSafePtr *m_wpjSafePtr;

	WPJTPtr():m_wpjSafePtr(NULL) { }
	WPJTPtr(T *obj_ptr):m_wpjSafePtr(new WPJSafePtr(obj_ptr))
	{
		WPJGC::GetSharedInst()->AddPtr(this->m_wpjSafePtr);
	}
	WPJTPtr(WPJSafePtr *safe_ptr):m_wpjSafePtr(safe_ptr)
	{
		if (!(safe_ptr->m_ifInPool))
			WPJGC::GetSharedInst()->AddPtr(safe_ptr);
	}

	void CopyPtr(const WPJTPtr* rhs)
	{
		// 拷贝目标是复制最底层的数据，因此需要深拷贝WPJObject，再构造WPJSafePtr
		// 对于WPJTPtr原本保存的内容释放控制权
		ASSERT(rhs != NULL);

		if (this != rhs)
		{
			// 释放控制权并深拷贝
			if (m_wpjSafePtr != NULL)
				m_wpjSafePtr->Release();

			T* newObjPtr = dynamic_cast<T*>(rhs->m_wpjSafePtr->m_ptr->DupCopy());
			m_wpjSafePtr = new WPJSafePtr(newObjPtr);
			WPJGC::GetSharedInst()->AddPtr(m_wpjSafePtr);
		}
	}

	void SharePtr(const WPJTPtr* rhs)
	{
		// 共享指针所指向的计数器
		// 对之前指向的数据进行Release操作，对之后指向的数据进行Retain操作

		ASSERT(rhs != NULL);
		if (m_wpjSafePtr != NULL)
			m_wpjSafePtr->Release();	

		m_wpjSafePtr = rhs->m_wpjSafePtr;
		m_wpjSafePtr->Retain();
	}

	U_INT GetRefCount()
	{
		return m_wpjSafePtr->m_uReference;
	}

	void MoveToPool()
	{
		m_wpjSafePtr->m_ifInPool = true;
	}

	void MoveToGC()
	{
		m_wpjSafePtr->m_ifInPool = false;
	}

	T *operator ->() { return dynamic_cast<T*>(m_wpjSafePtr->m_ptr); }

	~WPJTPtr()
	{
		if (m_wpjSafePtr != NULL)
			m_wpjSafePtr->Release();

#ifndef GC_OPEN
		if (m_wpjSafePtr->m_uReference == 0)
			delete m_wpjSafePtr;
#endif
		
	}
};

NS_WPJ_END

#endif // !_H_WPJTPTR
