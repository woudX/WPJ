#ifndef _H_WPJTPTR
#define _H_WPJTPTR

#include "WPJMacros.h"
#include "WPJPtr.h"

NS_WPJ_BEGIN

template<class T>
class WPJTPtr : public WPJObject
{
private:
	WPJTPtr &operator =(const WPJTPtr &rhs) { return NULL; }	// ��ֹ��ֵ����
	//WPJTPtr(const WPJTPtr &orig) { }	// ��ֹ���ƹ���

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
		// ����Ŀ���Ǹ�����ײ�����ݣ������Ҫ���WPJObject���ٹ���WPJSafePtr
		// ����WPJTPtrԭ������������ͷſ���Ȩ
		ASSERT(rhs != NULL);

		if (this != rhs)
		{
			// �ͷſ���Ȩ�����
			if (m_wpjSafePtr != NULL)
				m_wpjSafePtr->Release();

			T* newObjPtr = dynamic_cast<T*>(rhs->m_wpjSafePtr->m_ptr->DupCopy());
			m_wpjSafePtr = new WPJSafePtr(newObjPtr);
			WPJGC::GetSharedInst()->AddPtr(m_wpjSafePtr);
		}
	}

	void SharePtr(const WPJTPtr* rhs)
	{
		// ����ָ����ָ��ļ�����
		// ��֮ǰָ������ݽ���Release��������֮��ָ������ݽ���Retain����

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
