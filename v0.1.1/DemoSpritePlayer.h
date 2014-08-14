#ifndef _H_DEMOSPRITEPLAYER
#define _H_DEMOSPRITEPLAYER

#include "WPJLib.h"

NS_WPJ_BEGIN

class DemoPlayer : public WPJSprite
{
public:
	DemoPlayer();

	static DemoPlayer *Create();
	virtual void Update(float dt);
	void DefenseBubble(WPJEvent *e);
};

NS_WPJ_END

#endif