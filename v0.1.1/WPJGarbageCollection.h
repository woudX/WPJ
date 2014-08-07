#ifndef _H_WPJGARBAGECOLLECTION
#define _H_WPJGARBAGECOLLECTION

#include "WPJObject.h"
#include "WPJMacros.h"
#include "WPJStdafx.h"


/**
 *	Garbage Collection, this class contain garbage collection and autorelease
 */

NS_WPJ_BEGIN

class _AutoReleasePool
{
public:
	void AddObject(WPJObject *object);

	_AutoReleasePool();
	~_AutoReleasePool();

private:
	std::list<WPJObject*> m_lObjectList;

};

class WPJGC
{
public:
	static WPJGC *GetSharedInst();
	void AddPtr(WPJObject* gcPtr);
	void RemovePtr(WPJObject* gcPtr);
	void GC();
	void CheckMemoryLeak();
	void SetLimit(bool ifLimit);

	_AutoReleasePool *m_pCurrentPool;
	void AddObject(WPJObject *object);
	void Push();
	void Pop();
	void Finalize();

	~WPJGC();
protected:
	WPJGC();
private:
	static WPJGC *m_inst;
	std::list<WPJObject* > m_GCList;
	bool m_gcLimit;	// 回收限制
	U_INT m_maxGcCount;	// 最大回收数目

	std::list<_AutoReleasePool*> m_lAutoReleasePools;
};

NS_WPJ_END

#endif