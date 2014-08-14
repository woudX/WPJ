#include "DemoScene.h"

#include "WPJLib.h"
#include "DemoSpritePlayer.h"
USING_NS_WPJ

DemoScene *DemoScene::CreateNewObject()
{
	DemoScene *pRet = new DemoScene();

	if (pRet)
	{
		pRet->AutoRelease();
		pRet->Init();
	}

	return pRet;
}

DemoScene::DemoScene()
{

}

void DemoScene::EventRouteTestFunction(WPJEvent *e)
{
	WPJLOG("[%s] key pressed from scene ... code =  %d\n", _D_NOW_TIME__, e->e.keyboard.keycode);
	WPJNode *son = GetChildByTag(1);

	if (son != NULL)
	{
		WPJRotateBy *rotateBy = WPJRotateBy::Create(1, deg_std(90));

		float dx = 0, dy = 0;
		if (e->e.keyboard.keycode == ALLEGRO_KEY_LEFT)
			dx = -20;
		else if (e->e.keyboard.keycode == ALLEGRO_KEY_RIGHT)
			dx = 20;
		else if (e->e.keyboard.keycode == ALLEGRO_KEY_UP)
			dy = -20;
		else if (e->e.keyboard.keycode == ALLEGRO_KEY_DOWN)
			dy = 20;
		
		son->SetPosition(son->GetPosition().x + dx, son->GetPosition().y + dy);
		son->RunAction(rotateBy);
	}	
}


bool DemoScene::Init()
{
	//	注册一个事件函数
	RegistEventHandler(eventhandler_selector(DemoScene::EventRouteTestFunction), ALLEGRO_EVENT_KEY_CHAR);

	WPJDirector *pDirector = WPJDirector::GetSharedInst();
	WPJPoint origin = pDirector->GetViewOriginPoint();
	WPJSize size = pDirector->GetViewSize();

	//	测试
	WPJSprite *pSprite = WPJSprite::Create();
	pSprite->InitWithFile(full_path("4color.png").c_str());
	pSprite->SetAngle(deg_std(0));
	pSprite->SetPosition(75, 75);
	pSprite->ScheduleUpdate();
	this->AddChild(pSprite, 3, 1);
	
	//	Player
	DemoPlayer *player = DemoPlayer::Create();
	player->InitWithFile(full_path("white.png").c_str());
	player->SetPosition(300, 300);
	player->ScheduleUpdate();
	this->AddChild(player, 5, 2);

	// 初始化背景图片精灵
	WPJSprite *background = WPJSprite::Create();
	background->InitWithFile("background.png");
	background->SetPosition(origin.x + size.width / 2, origin.y + size.height / 2);
	background->UpdateDisplayColor(wpc3(100, 100, 100));
	background->SetScale(size.width / 800, size.height / 600);
	this->AddChild(background, 2);

	// 初始化边界精灵
	WPJSprite *border = WPJSprite::Create();
	border->InitWithFile("background.png");
	border->SetPosition(0, 0);
	border->SetIgnoreAnchorPoint(true);
	border->UpdateDisplayColor(wpc3(255, 0, 0));
	border->SetScale(WPJALGOManager::GetSharedInst()->GetScaleX(), WPJALGOManager::GetSharedInst()->GetScaleY());
	this->AddChild(border, 1);

	return true;
}