#include "WPJGarbageCollection.h"

USING_NS_WPJ

///	_AutoReleasePool
//////////////////////////////////////////////////////////////////////////

_AutoReleasePool::_AutoReleasePool()
{

}

void _AutoReleasePool::AddObject(WPJObject *object)
{
	m_lObjectList.push_back(object);
}

_AutoReleasePool::~_AutoReleasePool()
{
	foreach_in_list_auto(WPJObject *, itor, m_lObjectList)
	{
		if (pp(itor))
			pp(itor)->Release();
	}

	m_lObjectList.clear();
}

///	WPJGC
//////////////////////////////////////////////////////////////////////////

WPJGC *WPJGC::m_inst = 0;

WPJGC::WPJGC()
	:m_gcLimit(true)
	,m_maxGcCount(GC_MAX_COUNT)
	,m_pCurrentPool(NULL)
{
	
}

WPJGC *WPJGC::GetSharedInst()
{
	if (m_inst == 0)
		m_inst = new WPJGC();

	return m_inst;
}

void WPJGC::AddPtr(WPJObject* gcPtr)
{
	ASSERT(gcPtr != NULL);
	m_GCList.push_back(gcPtr);

	//	when GC_OPEN, gc_list will control object, else GC will only keep 
	//	watch on object but not manage them
#ifdef GC_OPEN
	gcPtr->Retain();
#endif // GC_OPEN

}

void WPJGC::RemovePtr(WPJObject* gcPtr)
{
	ASSERT(gcPtr != NULL);
	m_GCList.remove(gcPtr);
}

void WPJGC::SetLimit(bool ifLimit)
{
	m_gcLimit = ifLimit;
}

void WPJGC::GC()
{
#if GC_TYPE == GC_OPEN
	U_INT gcCount = 0;
	foreach_in_list(WPJObject*, itor, m_GCList)
	{
		if (m_gcLimit && gcCount > m_maxGcCount)
		{
			WPJLOG("[%s] GC 回收达最大限制，暂停回收\n", __TIME__);
			break;
		}

		if (ptr_data(itor)->GetReference() == 1)		// Ref = 1, only gc used
		{
			WPJLOG("[%s] GC ... %u Bytes Complete!\n", __TIME__, ptr_data(itor)->GetSize());

			++gcCount;
			ptr_data(itor)->Release();	// Ref = 0, delete
			itor = m_GCList.erase(itor);
		}
		else
			itor++;
	}

	// WPJLOG("[%s] GC ... Once Complete!\n",_D_NOW_TIME__);
#endif
}

void WPJGC::CheckMemoryLeak()
{
	SetLimit(false);
	GC();

	U_INT leakSize = 0;
	U_INT poolSize = 0;

	foreach_in_list_auto(WPJObject*, itor, m_GCList)
	{
		if (ptr_data(itor)->GetbInPool())
			poolSize += ptr_data(itor)->GetSize();
		else
			leakSize += ptr_data(itor)->GetSize();

		WPJLOG("MemoryLeak ... %u Bytes\n", ptr_data(itor)->GetSize());
	}

	WPJLOG("MemoryLeak Total is ... %u Bytes\n", leakSize);
	WPJLOG("MemoryPool Total is ... %u Bytes\n", poolSize);
	SetLimit(true);

}

void WPJGC::AddObject(WPJObject *object)
{
	//	check if CurrentPool is exist
	if (!m_pCurrentPool)
		Push();

	m_pCurrentPool->AddObject(object);
}

void WPJGC::Push()
{
	_AutoReleasePool *t_pAutoRelease = new _AutoReleasePool();
	m_lAutoReleasePools.push_back(t_pAutoRelease);

	//	update CurrentPool
	m_pCurrentPool = t_pAutoRelease;
}

void WPJGC::Pop()
{
	if (m_lAutoReleasePools.size() == 0)
		return ;

	//	release top pool
	_AutoReleasePool *t_pReleasePool = m_lAutoReleasePools.back();
	m_lAutoReleasePools.pop_back();
	ptr_safe_del(t_pReleasePool);

	//	update CurrentPool
	if (m_lAutoReleasePools.size() == 0)
		m_pCurrentPool = NULL;
	else
		m_pCurrentPool = m_lAutoReleasePools.back();
}

void WPJGC::Finalize()
{
	while (m_lAutoReleasePools.size() > 0)
		Pop();
}

WPJGC::~WPJGC()
{
#if GC_TYPE == GC_WATCH
	CheckMemoryLeak();
#endif
	
#if GC_TYPE == GC_OPEN
	//	release all object
	foreach_in_list_auto(WPJObject*, itor, m_GCList)
	{
		while (ptr_data(itor) && pp(itor)->GetReference() > 1)	// m_uRef = 1
			ptr_data(itor)->Release();

		WPJ_SAFE_RELEASE(ptr_data(itor));// m_uRef = 0
	}

#endif // GC_OPEN
	
	m_GCList.clear();
}