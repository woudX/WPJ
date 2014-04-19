#include "WPJObjectPoolManager.h"

USING_NS_WPJ

WPJObjectPoolManager *WPJObjectPoolManager::m_inst = 0;

WPJObjectPoolManager::WPJObjectPoolManager()
{
	// 初始化常用的对象池
}

WPJObjectPoolManager *WPJObjectPoolManager::GetSharedInst()
{
	if (m_inst == 0)
		m_inst = new WPJObjectPoolManager();

	return m_inst;
}

void WPJObjectPoolManager::GC(int maxCount = GC_MAX_COUNT)
{
	foreach_in_list_auto(WPJObjectPool*, itor, m_pools)
	{
		ptr_data(itor)->GC(maxCount);
	}
}

WPJObjectPoolManager::~WPJObjectPoolManager()
{
	foreach_in_list(WPJObjectPool*, itor, m_pools)
	{
		if (ptr_data(itor) != NULL)
		{
			ptr_del(ptr_data(itor));
			itor = m_pools.erase(itor);
		}
		else
			itor++;
	}

	m_pools.clear();
}
