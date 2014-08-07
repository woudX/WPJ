#ifndef _H_WPJDIRECTOR
#define _H_WPJDIRECTOR

#include "WPJStdafx.h"
#include "WPJMacros.h"
#include "WPJObject.h"
#include "WPJScene.h"
#include "WPJALGOManager.h"

NS_WPJ_BEGIN

class WPJScriptManager;
class WPJScriptProtocol;
class WPJActionManager;
class TimeVal;

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
	static WPJDirector *GetSharedInst();

	inline float GetDeltaTime() { return m_fDeltaTime; }
	virtual ~WPJDirector();

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
	void PopToSceneStackLevel(int pStackLevel);
	void RunWithScene(WPJScene *pScene);
	void ReplaceWithScene(WPJScene *pScene);

	/**
	 *	WPJDirector Flow Control
	 */
	virtual void MainLoop();
	void CalculateInterval();
	void End();
	void ShowStatus();
	virtual void SetAnimationInterval(double dValue);
	virtual void StartAnimation();
	virtual void StopAnimation();

	/**
	 *	Draw Engine
	 */

	// This method will be called every frame, so don't call it manually
	virtual void Draw();

	WPJPoint GetViewOriginPoint();	
	WPJSize GetViewSize();
	WPJSize GetDrawOffset();

	/**
	 *	Script Engine
	 */
	WPJScriptProtocol *GetScriptEngine();

protected:
	WPJDirector();

	TimeVal *m_pLastTimeVal;
	float m_fDeltaTime;
	U_INT m_uFrames;
	float m_fAccumDt;

	bool m_bPause;
	bool m_bExit;
	bool m_bTimeStart;

	// if m_bCleanUpRunningScene = true, the old scene will be clear
	bool m_bCleanUpRunningScene;

	double m_dAnimationInterval;

	// m_pNextScene will be update & draw in next frame
	WPJScene *m_pNextScene;
	WPJScene *m_pRunningScene;

	WPJActionManager *m_pActionManager;
	WPJ_PROPERTY(WPJScheduler*, m_pScheduler, Scheduler)
	WPJ_PROPERTY_READONLY(WPJALGOManager*, m_pALGOManager, ALGOManager)
	WPJ_PROPERTY_READONLY(WPJScriptManager*, m_pScriptManager, ScriptManager)

private:
	static WPJDirector *m_pInst;
	
	std::stack<WPJScene*> m_obSceneStack;
};

/**
 *	This extend class is used to synchronizes timer with the refresh rate of display.
 *	Scheduled timer and drawing are synchronizes with the refresh rate of display.
 */
class WPJDisplayLinkDirector : public WPJDirector
{
public:
	WPJDisplayLinkDirector();
	virtual void MainLoop();
	virtual void SetAnimationInterval(double dValue);
	virtual void StartAnimation();
	virtual void StopAnimation();

protected:
	bool m_bInvalid;
};

NS_WPJ_END

#endif