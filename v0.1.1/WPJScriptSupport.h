#ifndef _H_WPJSCRIPTSUPPORT
#define _H_WPJSCRIPTSUPPORT

#include "WPJStdafx.h"
#include "WPJMacros.h"
#include "ScriptH.h"

NS_WPJ_BEGIN

typedef int (*SEL_LUAFUNC)(lua_State *);
#define luafunc_selector(_SELECTOR) (SEL_LUAFUNC)(&_SELECTOR)


/**
 *	WPJScriptProtocol can used because there is only one script - lua can use
 *	If there is other script used, please inherite WPJScriptProtocol to realize
 *	virtual method
 */
class WPJScriptProtocol
{
public:
	WPJScriptProtocol();

	//	Open script engine
	virtual bool Open();

	//	Close script engine
	virtual void Close();

	//	Register game engine api, these apis will be provided to script to call
	virtual void RegisterGameEngineAPI(SEL_LUAFUNC pFunc, const char *pName);

	//	Run a script with file path
	virtual int RunScript(const char *pszFilename);

	~WPJScriptProtocol();

protected:
	//	Initialize script engine's params that it's own
	virtual bool InitScriptEngine();
private:
	lua_State *m_pL;
};


class WPJScriptManager
{
public:
	static WPJScriptManager *GetsharedInst();

	WPJScriptProtocol *GetScriptEngine();
	void SetScriptEngine(WPJScriptProtocol *pScriptEngine);

	~WPJScriptManager();

protected:
	WPJScriptManager();

private:
	static WPJScriptManager *m_pInst;
	WPJScriptProtocol *m_pScriptEngine;
};

NS_WPJ_END

#endif // !_H_WPJSCRIPTSUPPORT
