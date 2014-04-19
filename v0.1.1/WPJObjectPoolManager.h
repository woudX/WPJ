#ifndef _H_WPJOBJECTPOOLMANAGER
#define _H_WPJOBJECTPOOLMANAGER

#include "ObjectPool.hpp"
#include "WPJStdafx.h"
#include "WPJMacros.h"

NS_WPJ_BEGIN

class WPJObjectPoolManager : WPJObject
{
private:
	std::list<WPJObjectPool* > m_pools;
	static WPJObjectPoolManager *m_inst;
public:
	WPJObjectPoolManager();
	static WPJObjectPoolManager *GetSharedInst();
	void GC(int maxCount);
	template<class T> void CreateObjectPool()
	{
		m_pools.push_back(ObjectPool<WPJObject>::CreateNewPool());
		m_pools.push_back(ObjectPool<WPJAnime>::CreateNewPool());
	}

	// 获得指定类型的Object
	// 接口被抽象的好处是不需要知道具体的哪个对象池，只需通过统一的接口获取即可
	// 通过对象池的存储类型匹配进行判断
	template<class T> T* GetIdleObject()
	{
		T *ptr = NULL;
		foreach_in_list_auto(WPJObjectPool*, itor, m_pools)
		{
			HString type(typeid(T).name());

			if (ptr_data(itor)->PoolType()->EqualWith(&type))
			{
				WPJObjectPool *obj_pool = ptr_data(itor);
				ObjectPool<T> *pool = dynamic_cast<ObjectPool<T>* >(obj_pool);
				ptr = pool->GetIdleObject();
				break;
			}
		}

		ASSERT(ptr != NULL);
		return ptr;
	}

	~WPJObjectPoolManager();
};

NS_WPJ_END

#endif // !_H_WPJOBJECTPOOLMANAGER
