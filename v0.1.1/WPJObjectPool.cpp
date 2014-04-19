#include "WPJObjectPool.h"

USING_NS_WPJ

void WPJObjectPool::GC(int maxcount)
{

}

HString *WPJObjectPool::PoolType()
{
	return m_poolType;
}

WPJObjectPool::~WPJObjectPool()
{
	delete m_poolType;
};