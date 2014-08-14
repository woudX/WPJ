#include "DemoSpritePlayer.h"
#include "WPJInputUtil.h"

USING_NS_WPJ

DemoPlayer *DemoPlayer::Create()
{
	DemoPlayer *pRet = new DemoPlayer();
	pRet->AutoRelease();

	return pRet;
}

DemoPlayer::DemoPlayer()
{
	RegistEventHandler(eventhandler_selector(DemoPlayer::DefenseBubble), ALLEGRO_EVENT_KEY_CHAR);
}

void DemoPlayer::DefenseBubble(WPJEvent *e)
{
	e->ForbidBubble();
	WPJLOG("defense!\n");
}

void DemoPlayer::Update(float dt)
{
	WPJInputUtil *key = WPJInputUtil::GetSharedInst();

	float dx = 0, dy = 0, v = 150;
	if (key->IsKeyPressed(ALLEGRO_KEY_LEFT))
		dx = -v * dt;
	else if (key->IsKeyPressed(ALLEGRO_KEY_RIGHT))
		dx = v * dt;
	
	if (key->IsKeyPressed(ALLEGRO_KEY_UP))
		dy = -v * dt;
	else if (key->IsKeyPressed(ALLEGRO_KEY_DOWN))
		dy = v * dt;

	m_obPosition += _npoint(dx, dy);
	//WPJLOG("%f %f\n", m_obPosition.x, m_obPosition.y);
}