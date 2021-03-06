#ifndef _CPP_MAIN_
#define _CPP_MAIN_

#include "WPJGarbageCollection.h"
#include "WPJObjectPoolManager.h"
#include "WPJString.h"
#include "WPJScheduler.h"
#include "WPJTest.h"
#include "WPJALGOManager.h"
#include "WPJTime.h"
#include "WPJAppDelegate.h"
#include <windows.h>
#include <stdio.h>
#include "WPJList.h"
#include <ctime>

USING_NS_WPJ

void PoolTesting();
void GCTesting();
void WPJNodeTesting();

int main(int argc, char **argv)
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF|_CRTDBG_ALLOC_MEM_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

	// Set frame resolution
	WPJALGOManager::GetSharedInst()->SetFrameSize(800, 600);

	WPJALGOManager::GetSharedInst()->SetFrameZoomFactor(1.0);
	return WPJAppDelegate::GetSharedInst()->Run();	
}

/// AllegroTesting
//////////////////////////////////////////////////////////////////////////
int AllegroTesting()
{
	ALLEGRO_DISPLAY *display = NULL;

	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	display = al_create_display(640, 480);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

	al_clear_to_color(al_map_rgb(0,0,0));

	al_flip_display();

	al_rest(3.0);

	al_destroy_display(display);

	return 0;
}

/// WPJNodeTesting
//////////////////////////////////////////////////////////////////////////
void WPJNodeTesting()
{

	WPJNode *pNode = WPJNodeTest::CreateNewObject();
	WPJNode *pNode2 = WPJNodeTest::CreateNewObject();
	WPJScheduler *pSchedule = WPJScheduler::CreateNewObject();

	pNode->SetScheduler(pSchedule);
	pNode2->SetScheduler(pSchedule);

	pNode->ScheduleUpdate();
	pNode2->ScheduleUpdate();

	pNode->AddChild(pNode2);

	pNode->Schedule(schedule_selector(WPJNodeTest::TestFuncA), 3);
	pNode->Schedule(schedule_selector(WPJNodeTest::TestFuncB), 2, 5, 4);
	int i = 0;
	while (i++ < 20)
	{
		WPJLOG("--- Frame %d Start ----- %s -----\n", i, _D_NOW_TIME__);
		pSchedule->Update(1);
		WPJLOG("--- Frame %d End   ----- %s -----\n>>>\n", i, _D_NOW_TIME__);

		if (i == 12)
			pNode->UnscheduleUpdate();

		if (i == 15)
			pNode->Unschedule(schedule_selector(WPJNodeTest::TestFuncB));

		Sleep(1000);
	}

	pSchedule->Release();
	WPJGC::GetSharedInst()->GC();

	delete WPJGC::GetSharedInst();
}

/// SchedulerTesting
//////////////////////////////////////////////////////////////////////////
void SchedulerTesting()
{
	WPJObject *obj = WPJObject::CreateNewObject();
	WPJAnime *anime = WPJAnime::CreateNewObject();
	WPJScheduler *schedule = WPJScheduler::CreateNewObject();
	schedule->ScheduleUpdateForTarget(obj, 3, false);
	schedule->ScheduleSelector(anime, schedule_selector(WPJAnime::ofTest), 3, false);
	schedule->ScheduleSelector(anime, schedule_selector(WPJAnime::ofTest), 5, 10, 0, false);

	int count = 20;
	while (count > 0)
	{
		schedule->Update(1);
		Sleep(1000);
		--count;

		if (count == 12)
			schedule->UnscheduleAllSelector(anime);

		if (count == 10)
			schedule->PauseTarget(obj);

		if (count == 5)
			schedule->ResumeTarget(obj);

		WPJLOG("Time Limit ... %d\n", count);
	}


	anime->Release();
	obj->Release();
	schedule->Release();
	WPJGC::GetSharedInst()->GC();
	delete WPJGC::GetSharedInst();
}

/// PoolTesting
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

/// GCTesting
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
			WPJLOG("----------������ͣ----------\n");
			for (int i = 3; i > 0; --i)
			{
				WPJLOG("ʣ��ʱ�䣺%d\n",i);
				Sleep(1000);
			}

		}
	}
	delete WPJGC::GetSharedInst();
}
#endif