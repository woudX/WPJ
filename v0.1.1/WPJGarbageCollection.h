#ifndef _H_WPJGARBAGECOLLECTION
#define _H_WPJGARBAGECOLLECTION

#include "WPJObject.h"
#include "WPJMacros.h"
#include "WPJStdafx.h"

/// Garbage Collection ������
//////////////////////////////////////////////////////////////////////////

NS_WPJ_BEGIN

class WPJGC
{
public:
	static WPJGC *GetSharedInst();
	void AddPtr(WPJObject* gcPtr);
	void RemovePtr(WPJObject* gcPtr);
	void GC();
	void CheckMemoryLeak();
	void SetLimit(bool ifLimit);
	~WPJGC();
protected:
	WPJGC();
private:
	static WPJGC *m_inst;
	std::list<WPJObject* > m_GCList;
	bool m_gcLimit;	// ��������
	U_INT m_maxGcCount;	// ��������Ŀ
};

NS_WPJ_END

#endif