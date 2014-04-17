#ifndef _CPP_MAIN_
#define _CPP_MAIN_

#include "WPJGarbageCollection.h"
#include "WPJObjectPoolManager.h"
#include "WPJString.h"
#include "WPJScheduler.h"

#include <windows.h>

USING_NS_WPJ;

void PoolTesting();
void GCTesting();

int main(void *argc, void **argv)
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF|_CRTDBG_ALLOC_MEM_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	
	WPJObject *obj = new WPJObject();
	WPJScheduler *schedule = new WPJScheduler();
	schedule->ScheduleUpdateForTarget(obj, 3, false);

	while (1)
	{
		schedule->Update(1);
		Sleep(1000);
	}
	
	system("pause");
	return 0;
}

/// 对象池测试
//////////////////////////////////////////////////////////////////////////
void PoolTesting()
{
	ObjectPool<WPJObject> *pool = ObjectPool<WPJObject>::CreateNewPool();

	for (int i = 0; i < 100; ++i)
	{
		WPJObject *test = pool->GetIdleObject();
		test->Release();

		if (i % 20 == 0)
		{
			pool->GC(3000);
			//Sleep(2000);
		}
	}

	pool->GC(3000);
	delete pool;
}

/// 测试自动回收
//////////////////////////////////////////////////////////////////////////
void GCTesting()
{
	int count = 0;
	while (1)
	{
		count++;
		WPJObject *object = WPJObject::CreateNewObject();
		object->Release();

		if (count % 300000 == 0)
		{
			count = 0;
			WPJGC::GetSharedInst()->GC();
			WPJLOG("----------回收暂停----------\n");
			for (int i = 3; i > 0; --i)
			{
				WPJLOG("剩余时间：%d\n",i);
				Sleep(1000);
			}

		}
	}
	delete WPJGC::GetSharedInst();
}
#endif