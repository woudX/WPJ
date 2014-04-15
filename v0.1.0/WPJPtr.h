#ifndef _H_WPJPTR
#define _H_WPJPTR

#include "WPJMacros.h"
#include "WPJObject.h"

NS_WPJ_BEGIN

// 智能指针中间层
class WPJSafePtr : public WPJObject
{
public:
	friend class WPJPtr;
	WPJObject *m_ptr;	// 数据指针
	U_INT m_uReference;	// 引用次数
	bool m_ifInPool;	// 是否在内存池中
	WPJSafePtr();
	WPJSafePtr(WPJObject* wpj_obj);
	void Retain();
	void Release();
	void SetPtr(WPJObject* wpj_obj);
	WPJObject* DupCopy();
	WPJSafePtr& operator= (const WPJSafePtr& rhs);

	~WPJSafePtr();
};

// 智能指针——已经废弃，不建议使用，新的智能指针请使用WPJTPtr
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
