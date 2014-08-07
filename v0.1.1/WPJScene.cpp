#include "WPJScene.h"
#include "WPJGarbageCollection.h"

USING_NS_WPJ

WPJScene *WPJScene::CreateNewObject()
{
	WPJScene *t_pScene = new WPJScene();

	if (t_pScene && t_pScene->Init())
	{
		t_pScene->AutoRelease();
		return t_pScene;
	}
	else
	{
		delete t_pScene;
		return NULL;
	}
}

bool WPJScene::Init()
{
	return true;
}

WPJScene::WPJScene()
{

}

WPJScene::~WPJScene()
{

}