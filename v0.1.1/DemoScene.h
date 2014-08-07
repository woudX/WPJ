#ifndef _H_DEMOSCENE
#define _H_DEMOSCENE

#include "WPJScene.h"

NS_WPJ_BEGIN

class DemoScene : public WPJScene
{
public:
	DemoScene();
	static DemoScene *CreateNewObject();

	bool Init();
};

NS_WPJ_END

#endif
