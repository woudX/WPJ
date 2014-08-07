#include "DemoScene.h"
#include "WPJSprite.h"
#include "WPJLib.h"

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

bool DemoScene::Init()
{
	WPJDirector *pDirector = WPJDirector::GetSharedInst();
	WPJPoint origin = pDirector->GetViewOriginPoint();
	WPJSize size = pDirector->GetViewSize();

	//	²âÊÔ
	WPJSprite *pSprite = WPJSprite::Create();
	pSprite->InitWithFile(full_path("4color.png").c_str());
	pSprite->SetAngle(deg_std(0));
	pSprite->SetPosition(75, 75);
	this->AddChild(pSprite, 3);
	
	// ³õÊ¼»¯±³¾°Í¼Æ¬¾«Áé
	WPJSprite *background = WPJSprite::Create();
	background->InitWithFile("background.png");
	background->SetPosition(origin.x + size.width / 2, origin.y + size.height / 2);
	background->UpdateDisplayColor(wpc3(100, 100, 100));
	background->SetScale(size.width / 800, size.height / 600);
	this->AddChild(background, 2);

	// ³õÊ¼»¯±ß½ç¾«Áé
	WPJSprite *border = WPJSprite::Create();
	border->InitWithFile("background.png");
	border->SetPosition(0, 0);
	border->SetIgnoreAnchorPoint(true);
	border->UpdateDisplayColor(wpc3(255, 0, 0));
	border->SetScale(WPJALGOManager::GetSharedInst()->GetScaleX(), WPJALGOManager::GetSharedInst()->GetScaleY());
	this->AddChild(border, 1);

	return true;
}