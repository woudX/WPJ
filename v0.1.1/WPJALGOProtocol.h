#ifndef _H_WPJALGOPROTOCOL
#define _H_WPJALGOPROTOCOL

#include "WPJStdafx.h"
#include "WPJMacros.h"
#include "WPJGeometry.h"


NS_WPJ_BEGIN

enum ResolutionPolicy {
	//	this method will show all units as far as possible, so the screen maybe have
	//	black area on the two sides of screen
	wResolutionShowAll,

	//	this method will show units on full screen, but this resolution policy will let
	//	some units out of screen
	wResolutionNoBorder,

	wResolutionUnknown
};

class WPJALGOProtocol
{
public:
	WPJALGOProtocol();
	~WPJALGOProtocol();

	WPJSize& GetFrameSize();
	void SetFrameSize(float width, float height);

	WPJSize& GetResolutionSize();
	void SetDesignResolutionSize(float width, float height, ResolutionPolicy resolutionPolicy);

protected:
	
	WPJSize m_obScreenSize;					// Real screen size
	WPJSize m_obDesignResolutionSize;		// Design resolution size
	WPJRect m_obViewPortRect;				// View port rect

	WPJ_PROPERTY(float, m_fScaleX, ScaleX)
	WPJ_PROPERTY(float, m_fScaleY, ScaleY)

	ResolutionPolicy m_obResolutionPolicy;
};

NS_WPJ_END

#endif
