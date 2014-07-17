#ifndef _H_WPJMACROS
#define _H_WPJMACROS

#include "WPJStdC.h"

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#define NS_WPJ_BEGIN	namespace wpj_engine {
#define NS_WPJ_END		}
#define USING_NS_WPJ	using namespace wpj_engine;

/// Garbage Collection
//////////////////////////////////////////////////////////////////////////

//	WPJEngine provide 3 kind of methods to do with garbage collection
//	- GC_OPEN : this method will collect garbage automatically when a frame done ,
//		you	can also set GC_MAX_COUNT to control the max count in each collection
#define GC_OPEN		0

//	- GC_WATCH : this method will help developer to watch memory status, every
//		object created by factory method will be watched. When main func ends, the
//		engine will print how much resource have been leak, also you can use WPJGC
//		to watch now leak when debuging
//
//		like:	WPJGC::GetSharedInst()->CheckMemoryLeak()
//
//		---- We recommend you to use GC_OPEN if you have not confident with memory manage ----
#define GC_WATCH	1

//	- GC_CLOSE : this method will do nothing with garbage collection, when GC_Close, all
//		works about gc will paused, actually, the programs will be more faster
//		so, we recommend to use GC_CLOSE when all systems finish and debug well
#define GC_CLOSE	2

//	Please select garbage collection type
#define GC_TYPE	GC_OPEN

//	Every time garbage collection can recycle count, don't too big or too less
#define GC_MAX_COUNT 400000

//	Safe retain and release
#define WPJ_SAFE_RETAIN(p) do { if (p) { (p)->Retain(); } } while (0)
#define WPJ_SAFE_RELEASE(p) do { if (p) { (p)->Release(); } } while (0)
#define WPJ_SAFE_RELEASE_NULL(p) do { if (p) { (p)->Release(); (p) = NULL; } } while(0)

#define POOL_MAX_SIZE 500

/// Debug define
//////////////////////////////////////////////////////////////////////////
#define _D_NOW_TIME__	WPJTime::NowTime()

/// Additional define
//////////////////////////////////////////////////////////////////////////

//	WPJEngine provide WPJ_ENABLED_ACTION_STACK to control action, the actions
//	run at the same time which are same kinds will composition
//	This switch default is open, you can close it to cancel composition, but 
//	we are not recommend, when it's closed, only the last actions will effect
#ifndef WPJ_ENABLED_ACTION_STACK
#define WPJ_ENABLED_ACTION_STACK 1
#endif

/// container迭代器宏定义
//////////////////////////////////////////////////////////////////////////
#define list_iterator(className) std::list<className>::iterator

#define foreach_in_list_auto(className,itor,container)\
	for (list_iterator(className) itor = container.begin();\
		itor != container.end(); itor++)

#define foreach_in_list(className,itor,container)\
	for (list_iterator(className) itor = container.begin();\
	itor != container.end();)

#define safe_remove_all_from_list(className, container)\
	foreach_in_list(className, itor, container)\
	{\
		if ((*itor) != NULL)\
		{\
			delete (*itor);\
			(*itor) = NULL;\
			itor = container.erase(itor);\
		}\
		else\
			++itor;\
	}\
	container.clear();

/// data define
//////////////////////////////////////////////////////////////////////////
typedef unsigned int U_INT;
typedef unsigned char U_CHAR;
#define U_INT_MAX 0xffffffff
#define MAX_STRING_LEN	(1024 * 100)
#define WPJRepeatForever U_INT_MAX - 1
#ifndef FLT_EPSILON
#define FLT_EPSILON     1.192092896e-07F	
#endif

#define UN_USED_PARAM(...)

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
#define pp(ptr) (*ptr)
#define ptr_safe_del(p) do { if (p) { delete (p); (p) = 0; } } while(0)

/** WPJ_PROPERTY_READONLY is used to declare protected property
 we can use getter to get the var
 @varType : the type of property
 @varName : the name of property
 @funcName: the name of getter
*/

#define WPJ_PROPERTY_READONLY(varType,varName,funcName)\
protected: varType varName;\
public: virtual varType Get##funcName();

/** WPJ_PROPERTY is used to declare property
 we can use getter/setter to get/set the var
 @varType : the type of property
 @varName : the name of property
 @funcName: the name of getter/setter
*/

#define WPJ_PROPERTY(varType,varName,funcName)\
protected: varType varName;\
public: virtual varType Get##funcName();\
public: virtual void Set##funcName(varType var);

/** WPJ_PROPERTY_BY_REF is used to declare property
 we can use getter/setter to get/set the var
 @varType : the type of property
 @varName : the name of property
 @funcName: the name of getter/setter
*/

#define WPJ_PROPERTY_BY_REF(varType,varName,funcName)\
protected: varType varName;\
public: virtual varType &Get##funcName();\
public: virtual void Set##funcName(varType var);
#endif


