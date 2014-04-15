#ifndef _H_OBJECTPOOL
#define _H_OBJECTPOOL

#include "WPJStdafx.h"
#include "WPJMacros.h"
#include "WPJObjectPool.h"

NS_WPJ_BEGIN

template <class T>
class ObjectPool : public WPJObjectPool
{
	
public:
	static ObjectPool *CreateNewPool(U_INT maxSize = POOL_MAX_SIZE)
	{
		ObjectPool *objectPool = new ObjectPool<T>();
		ASSERT(objectPool != NULL);

		objectPool->SetPoolSize(maxSize);
		objectPool->Allocate();
		objectPool->m_poolType = new WPJString(typeid(T).name());

		return objectPool;
	}

	void SetPoolSize(U_INT maxSize) { m_maxSize = maxSize; }

	T *GetIdleObject()
	{
		while (true)
		{
			T *ptr = GetObject();
			if (ptr == NULL)
				ExpandPoolSize();
			else
			{
				m_UsedPool.push_back(ptr);

				// 共享指针
				T *sharedPtr = ptr->GetSharedPtr();
				return sharedPtr;
			}
		}
	}

	void GC(int maxCount)
	{
		int bIdleCount = 0;
		
		foreach_in_list(WPJObject* , itor, m_UsedPool)
		{
			if (ptr_data(itor)->GetRefCount() == 1)
			{
				m_IdlePool.push_back(ptr_data(itor));
				itor = m_UsedPool.erase(itor);
				++bIdleCount;
			}
			else
				++itor;
		}

		WPJLOG("[%s] Object Pool ... %d change to idle\n", __TIME__, bIdleCount);
		WPJLOG("[%s] Object Pool ... Complete!\n", __TIMESTAMP__);
	}

	void ReleasePool()
	{
		foreach_in_list(WPJObject* , itor, m_UsedPool)
		{
			T *t = dynamic_cast<T*>(ptr_data(itor));
			ptr_del(t);
			itor = m_UsedPool.erase(itor);
		}
		m_UsedPool.clear();

		foreach_in_list(WPJObject* , itor, m_IdlePool)
		{
			T *t = dynamic_cast<T*>(ptr_data(itor));
			ptr_del(t);
			itor = m_IdlePool.erase(itor);
		}
		m_IdlePool.clear();

	}

	~ObjectPool()
	{
		ReleasePool();
	}

protected:
	ObjectPool() { }

private:
	std::list<WPJObject* > m_UsedPool;
	std::list<WPJObject* > m_IdlePool;
	U_INT m_maxSize;

	// 分配对象池内存
	void Allocate()
	{
		ExpandPoolSize(m_maxSize);
	}

	// 扩充对象池的容量，参数指定扩充大小，不指定则采用默认分配方法
	// 创建对象时调用new，避免对象池中的数据加入GarbageCollection，影响垃圾回收检查
	void ExpandPoolSize(int incSize = -1)
	{
		int increaseSize = incSize <= 0 ? IncreaseRule() : incSize;

		while (increaseSize > 0)
		{
			T *object = new T(); ASSERT(object != NULL);
			object->bInPool = true;

			m_IdlePool.push_back(object);
			--increaseSize;
		}
	}

	int IncreaseRule()
	{
		return 10 + m_UsedPool.size() / 3;
	}
	
	T *GetObject() 
	{
		if (m_IdlePool.size() > 0)
		{
			T *ptr = dynamic_cast<T*>(m_IdlePool.front()); ASSERT(ptr != NULL);
			m_IdlePool.pop_front();
			return ptr;
		}
		else
			return NULL;
	}
	
	
};

NS_WPJ_END

#endif // !_H_OBJECTPOOL
