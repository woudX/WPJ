#ifndef _H_WPJDIRECTOR
#define _H_WPJDIRECTOR

#include "WPJStdafx.h"
#include "WPJMacros.h"
#include "WPJObject.h"
#include "WPJScene.h"
#include "WPJALGOManager.h"

NS_WPJ_BEGIN

/**
 *	Brief, WPJDirector is responsible for scene change¡¢pause¡¢resume, flow control, like a director
 *	So WPJDirector contains these kinds of method:
 *	-	Scene Work (push¡¢pop and replace ...)
 *	-	Flow Control (mainloop)
 *	-	Draw Engine	(drawing system)
 *	-	Manage Class (like WPJALGOManager and WPJScheduler ...)
 */

class WPJDirector : public WPJObject
{
public:
	WPJDirector *GetSharedInst();

	/**
	 *	WPJDirector Props
	 */

	// When this method call, the whole system will pause except draw, but the draw frequency 
	// will be reduced to 4 FPS
	void Pause();

	// When this method call, the whole system will resume
	void Resume();

	// Return if the system is pause
	inline bool IsPause() { return m_bPause; }

	/**
	 *	WPJDirector Scene Operations
	 */
	void PushScene(WPJScene *pScene);
	void PopScene();
	void PopToRootScene();
	void PopToSceneStackLevel(int pStackLevel = 1);
	void RunWithScene(WPJScene *pScene);
	void ReplaceWithScene(WPJScene *pScene);

	/**
	 *	WPJDirector Flow Control
	 */
	virtual void MainLoop();
	void End();

	/**
	 *	Draw Engine
	 */

	// This method will be called every frame, so don't call it manually
	virtual void Draw();

protected:
	WPJDirector();

	bool m_bPause;
	WPJ_PROPERTY(WPJScheduler* ,m_pScheduler, Scheduler)
	WPJ_PROPERTY_READONLY(WPJALGOManager*, m_pALGOManager, ALGOManager)
private:
	static WPJDirector *m_pInst;
	
	std::stack<WPJScene*> m_obSceneStack;
};

NS_WPJ_END

#endif