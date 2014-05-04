#ifndef _H_WPJALGOMANAGER
#define _H_WPJALGOMANAGER

#include "WPJStdafx.h"
#include "WPJMacros.h"
#include "WPJGeometry.h"
#include "WPJString.h"
#include "WPJLib.h"

#include <allegro5/allegro.h>

NS_WPJ_BEGIN

class WPJALGOManager
{
public:
	WPJ_PROPERTY_BY_REF(WPJSize,m_obWndSize,WndSize)
	WPJ_PROPERTY_BY_REF(HString,m_obWndName,WndName)

	/// Getter And Setter
	/**
	 *	Only Getter and Setter
	 */
	void SetWndSize(int width, int height);

	/// Intialize method
	/**
	 *	These are allegro packaged method, so user can use this method easily
	 */
	// Initalize Allegro, call this method after setting WPJEGLManager params
	void InitALGO();

	// Destroy Allegro
	void DestroyALGO();

	// Get bool about Allegro is ready to use
	bool IsALGOReady();

	/// Interactive method
	/**
	 *	These method are used to realize the interactvie between 
	 *	user and engine, including:
	 *	- KeyBoard
	 *	- Mouse
	 */
	ALLEGRO_EVENT &WaitForEvent();

	static WPJALGOManager *GetSharedInst();

	~WPJALGOManager();
protected:
	WPJALGOManager();
private:
	static WPJALGOManager *m_pALGOManager;

	ALLEGRO_DISPLAY *m_pDisplay;
	ALLEGRO_EVENT_QUEUE *m_pEventQueue;
	ALLEGRO_EVENT m_obEvent;

};

NS_WPJ_END

#endif 