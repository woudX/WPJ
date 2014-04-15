#ifndef _H_WPJPTR
#define _H_WPJPTR

#include "WPJMacros.h"
#include "WPJObject.h"

NS_WPJ_BEGIN

// ����ָ���м��
class WPJSafePtr : public WPJObject
{
public:
	friend class WPJPtr;
	WPJObject *m_ptr;	// ����ָ��
	U_INT m_uReference;	// ���ô���
	bool m_ifInPool;	// �Ƿ����ڴ����
	WPJSafePtr();
	WPJSafePtr(WPJObject* wpj_obj);
	void Retain();
	void Release();
	void SetPtr(WPJObject* wpj_obj);
	WPJObject* DupCopy();
	WPJSafePtr& operator= (const WPJSafePtr& rhs);

	~WPJSafePtr();
};

// ����ָ�롪���Ѿ�������������ʹ�ã��µ�����ָ����ʹ��WPJTPtr
class WPJPtr : public WPJObject
{
private:
	WPJSafePtr *m_wpjSafePtr;

public:
	WPJPtr();
	WPJPtr(WPJObject *obj_ptr);
	WPJPtr(const WPJPtr& orig);
	WPJPtr& operator = (const WPJPtr& rhs);
	WPJObject* operator->();
	WPJObject* GetPtr();
	void SetPtr(WPJObject *ptr);
	WPJObject* DupCopy();

	~WPJPtr();
};


NS_WPJ_END

#endif // !_H_WPJPTR
