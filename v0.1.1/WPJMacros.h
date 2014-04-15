#ifndef _H_WPJMACROS
#define _H_WPJMACROS

#include <assert.h>
#include <iostream>

#define NS_WPJ_BEGIN	namespace wpj_engine {
#define NS_WPJ_END		}
#define USING_NS_WPJ	using namespace wpj_engine;

/// 调试开关
//////////////////////////////////////////////////////////////////////////
#define GC_OPEN

/// GC回收默认最大值
//////////////////////////////////////////////////////////////////////////
#define GC_MAX_COUNT 400000
#define POOL_MAX_SIZE 500

/// container迭代器宏定义
//////////////////////////////////////////////////////////////////////////
#define list_iterator(className) std::list<className>::iterator
#define foreach_in_list_auto(className,itor,container)\
	for (list_iterator(className) itor = container.begin();\
		itor != container.end(); itor++)
#define foreach_in_list(className,itor,container)\
	for (list_iterator(className) itor = container.begin();\
	itor != container.end();)

/// 数据结构宏定义
//////////////////////////////////////////////////////////////////////////
#define U_INT unsigned int

/// _DEBUG模式
//////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#define WPJLOG(...) std::printf(__VA_ARGS__)

#define ASSERT(expr)\
	if (expr){}\
	else {\
	assert(expr);\
	}
#else
#define WPJLOG(...)
#define ASSERT(expr)
#endif

/// WPJPtr指针操作宏
//////////////////////////////////////////////////////////////////////////
#define ptr_share(dst, src) dst->SharePtr(src)
#define ptr_copy(dst, src) dst->CopyPtr(src)
#define ptr_data(ptr) (*ptr)
#define ptr_del(ptr) delete ptr
#define ptr_new_d(className,ptrName,dataPtr)\
	WPJTPtr<className> *ptrName = new WPJTPtr<className>(dataPtr)
#define ptr_new(className,ptrName)\
	WPJTPtr<className> *ptrName = new WPJTPtr<className>()


/** WPJ_PROPERTY_READONLY is used to declare protected property
 we can use getter to get the var
 @varType : the type of property
 @varName : the name of property
 @funcName: the name of getter
*/

#define WPJ_PROPERTY_READONLY(varType,varName,funcName)\
protected: varType varName;\
public: virtual varType get##funcName();

/** WPJ_PROPERTY is used to declare property
 we can use getter/setter to get/set the var
 @varType : the type of property
 @varName : the name of property
 @funcName: the name of getter/setter
*/

#define WPJ_PROPERTY(varType,varName,fucnName)\
protected: varType varName;\
public: virtual varType get##funcName();\
public: virtual void set##funcName(varType var);

#endif


