#include "WPJGarbageCollection.h"

USING_NS_WPJ

WPJGC *WPJGC::m_inst = 0;

WPJGC::WPJGC():m_gcLimit(true),m_maxGcCount(GC_MAX_COUNT)
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
	U_INT gcCount = 0;
	foreach_in_list(WPJObject*, itor, m_GCList)
	{
		if (m_gcLimit && gcCount > m_maxGcCount)
		{
			WPJLOG("[%s] GC 回收达最大限制，暂停回收\n", __TIME__);
			break;
		}

		if (ptr_data(itor)->GetReference() == 0)
		{
			WPJLOG("[%s] GC ... %u Bytes Complete!\n", __TIME__, ptr_data(itor)->GetSize());

			++gcCount;
			delete ptr_data(itor);
			itor = m_GCList.erase(itor);
		}
		else
			itor++;
	}

	WPJLOG("[%s] GC ... Once Complete!\n",__TIMESTAMP__);
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

WPJGC::~WPJGC()
{
	foreach_in_list(WPJObject*, itor, m_GCList)
	{
		delete ptr_data(itor);
		itor = m_GCList.erase(itor);
	}

	m_GCList.clear();
}