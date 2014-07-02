#ifndef _H_WPJAPPDELEGATEPROTOCOL
#define _H_WPJAPPDELEGATEPROTOCOL

#include "AppMacros.h"

NS_WPJ_BEGIN

/**
 *	This class is a interface, used to set application's init method
 */
class WPJAppDelegateProtocol
{
public:
	//	WPJDirector and WPJALGOManager's init writing here
	//	and other need to be init before whole application start
	//
	//	return true means init correct
	//	return false means init fail
	virtual bool ApplicationDidFinishLaunching() = 0;
	
	//	Set application's animation interval , usually is 60FPS
	virtual void SetAnimationInterval(double dValue) = 0;
	
};

NS_WPJ_END

#endif // !_H_WPJAPPDELEGATEPROTOCOL
