#ifndef _CPP_MAIN_
#define _CPP_MAIN_

#include "WPJGarbageCollection.h"
#include "WPJObjectPoolManager.h"
#include "WPJString.h"

#include <windows.h>

USING_NS_WPJ;

void PoolTesting();
void GCTesting();

void printtest(float a)
{
	WPJLOG("%f\n",a);
}

int main(void *argc, void **argv)
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF|_CRTDBG_ALLOC_MEM_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	WPJAnime *anime = new WPJAnime();

	SEL_SCHEDULE a = schedule_selector(WPJAnime::ofTest);//schedule_selector();
	(anime->*a)(3);
	//sel(3);
	
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
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 100 - i * 10; ++j)
		{
			WPJObject *tObject = WPJObject::CreateNewObject();
			tObject->Release();
		}
		WPJGC::GetSharedInst()->GC();
		//Sleep(3000);
	}	
}
#endif