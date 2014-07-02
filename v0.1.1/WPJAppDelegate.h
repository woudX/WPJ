#ifndef _H_WPJAPPDELEGATE
#define _H_WPJAPPDELEGATE

#include "WPJMacros.h"
#include "WPJStdafx.h"
#include "WPJAppDelegateProtocol.h"
#include "WPJTime.h"
#include "WPJDirector.h"

NS_WPJ_BEGIN

class WPJAppDelegate : public WPJAppDelegateProtocol
{
public:
	static WPJAppDelegate *GetSharedInst();
	void SetAnimationInterval(double dValue);
	int Run();

	virtual bool ApplicationDidFinishLaunching();
	virtual bool Initialization();
	virtual bool ExtendInit();

	/*
	void SetResourceRootPath(const std::string& rootResDir);
	const std::string& GetResourceRootPath();
	*/

protected:
	WPJAppDelegate();
private:
	static WPJAppDelegate *m_pAppDelegate;
	
	int Exit();

	LARGE_INTEGER m_liAnimationInterval;
};

NS_WPJ_END

#endif