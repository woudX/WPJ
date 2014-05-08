#ifndef _H_WPJAPPDELEGATE
#define _H_WPJAPPDELEGATE

#include "WPJMacros.h"
#include "WPJStdafx.h"
#include "WPJTime.h"
#include "WPJDirector.h"

NS_WPJ_BEGIN

class WPJAppDelegate
{
public:
	static WPJAppDelegate *GetSharedInst();
	void SetAnimationInterval(double interval);
	int Run();

	virtual bool Initialization();

protected:
	WPJAppDelegate();
private:
	static WPJAppDelegate *m_pAppDelegate;
	
	int Exit();

	LARGE_INTEGER m_liAnimationInterval;
};

NS_WPJ_END

#endif