#include "WPJScene.h"
#include "WPJGarbageCollection.h"

USING_NS_WPJ

void WPJScene::GetSharedPtr(WPJScene* &object)
{
	object = this;
	object->Retain();
}

WPJScene *WPJScene::CreateNewObject()
{
	WPJScene *t_pScene = new WPJScene();

	if (t_pScene && t_pScene->Init())
	{
		WPJGC::GetSharedInst()->AddPtr(t_pScene);
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