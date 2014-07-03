#ifndef _H_WPJALGOMANAGER
#define _H_WPJALGOMANAGER

#include "WPJStdafx.h"
#include "WPJMacros.h"
#include "WPJGeometry.h"
#include "WPJString.h"
#include "WPJLib.h"
#include "WPJALGOProtocol.h"
#include <allegro5/allegro.h>
#include <allegro5/blender.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
NS_WPJ_BEGIN

enum WPJ_BLEND_MODE
{
	AL_ZERO					= ALLEGRO_ZERO,
	AL_ONE					= ALLEGRO_ONE,
	AL_SRC_ALPHA				= ALLEGRO_ALPHA,
	AL_ONE_MINUS_SRC_ALPHA	= ALLEGRO_INVERSE_ALPHA,
	AL_SRC_COLOR			= ALLEGRO_SRC_COLOR,
	//AL_DEST_COLOR			= ALLEGRO_DEST_COLOR,
	AL_ONE_MINUS_SRC_COLOR	= ALLEGRO_INVERSE_SRC_COLOR,
	//AL_ONE_MINUS_DEST_COLOR	= ALLEGRO_INVERSE_DEST_COLOR,
	AL_NUM_BLEND_MODES
};

enum WPJ_BLEND_OPERATIONS
{
	AL_FUNC_ADD					= ALLEGRO_ADD,
	AL_FUNC_SRC_MINUS_DEST		= ALLEGRO_SRC_MINUS_DEST,
	AL_FUNC_DEST_MINUS_SRC		= ALLEGRO_DEST_MINUS_SRC,
	AL_FUNC_NUM_BLEND_OPERATIONS
};

enum WPJ_DRAW_FLAGS
{
	AL_FLIP_HORIZONTAL			= ALLEGRO_FLIP_HORIZONTAL,
	AL_FLIP_VERTICAL			= ALLEGRO_FLIP_VERTICAL,
	AL_DRAW_FLAGS_MODES
};

class WPJALGOManager : public WPJALGOProtocol
{
public:
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
	bool InitALGO();

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
	bool WaitForEvent(ALLEGRO_EVENT& e);

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