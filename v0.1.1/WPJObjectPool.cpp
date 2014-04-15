#include "WPJObjectPool.h"

USING_NS_WPJ

void WPJObjectPool::GC(int maxcount)
{

}

WPJString *WPJObjectPool::PoolType()
{
	return m_poolType;
}

void WPJObjectPool::ReleasePool()
{
	delete m_poolType;
}

WPJObjectPool::~WPJObjectPool()
{
	delete m_poolType;
};