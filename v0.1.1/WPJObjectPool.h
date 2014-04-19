#ifndef _H_WPJOBJECTPOOL
#define _H_WPJOBJECTPOOL

#include "WPJMacros.h"
#include "WPJObject.h"
#include "WPJString.h"

NS_WPJ_BEGIN

class WPJObjectPool : public WPJObject
{
public:
	virtual void GC(int maxcount);
	HString *PoolType();
	virtual ~WPJObjectPool();
protected:
	HString *m_poolType;
};

NS_WPJ_END

#endif