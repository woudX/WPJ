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

	//	Setting frame size, this size is window/screen resolution
	WPJSize& GetFrameSize();
	void SetFrameSize(float width, float height);

	//	Setting resolution size, this size is design resolution
	WPJSize& GetDesignResolutionSize();
	void SetDesignResolutionSize(float width, float height, ResolutionPolicy resolutionPolicy);

	//	This origin point is the origin in design resolution, usually is (0, 0)
	//	but sometimes, in NoBorder policy , origin always not (0, 0)
	WPJPoint GetViewOriginPoint();

	//	This size is the actually can be seen, in design resolution, usually is resolutionSize
	//	but sometimes, in NoBorder policy, the size always less than resolutionSize because
	//	some of content is show outbound
	WPJSize GetViewSize();

	//	When Screen resolution is not fit with design resolution, we need use draw offset to 
	//	revise draw position
	WPJSize GetDrawOffset();

protected:
	
	WPJSize m_obScreenSize;					// Real screen size
	WPJSize m_obDesignResolutionSize;		// Design resolution size
	WPJRect m_obViewPortRect;				// View port rect

	WPJ_PROPERTY(float, m_fFrameZoomFactor, FrameZoomFactor)
	WPJ_PROPERTY(float, m_fScaleX, ScaleX)
	WPJ_PROPERTY(float, m_fScaleY, ScaleY)

	ResolutionPolicy m_obResolutionPolicy;
};

NS_WPJ_END

#endif
