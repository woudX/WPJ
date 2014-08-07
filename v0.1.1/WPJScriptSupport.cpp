#include "WPJScriptSupport.h"

USING_NS_WPJ

///	WPJScriptProtocol
//////////////////////////////////////////////////////////////////////////

WPJScriptProtocol::WPJScriptProtocol() 
{

}

bool WPJScriptProtocol::Open()
{
	m_pL = luaL_newstate();	
	bool bRet = m_pL ? true : false;

	if (bRet)
		bRet = InitScriptEngine();

	return bRet;
}

void WPJScriptProtocol::Close()
{
	lua_close(m_pL);
}

bool WPJScriptProtocol::InitScriptEngine()
{
	//	Load libs
	luaL_openlibs(m_pL);

	return true;
}

void WPJScriptProtocol::RegisterGameEngineAPI(SEL_LUAFUNC pFunc, const char *pName)
{
	lua_pushcfunction(m_pL, pFunc);
	lua_setglobal(m_pL, pName);
}

int WPJScriptProtocol::RunScript(const char *pszFilename)
{
	int tError = luaL_dofile(m_pL, pszFilename);
	return tError;
}

WPJScriptProtocol::~WPJScriptProtocol()
{

}


///	WPJScriptManager
//////////////////////////////////////////////////////////////////////////
WPJScriptManager *WPJScriptManager::m_pInst = 0;

WPJScriptManager *WPJScriptManager::GetsharedInst()
{
	if (m_pInst == 0)
		m_pInst = new WPJScriptManager();

	return m_pInst;
}

WPJScriptManager::WPJScriptManager():m_pScriptEngine(NULL)
{

}

WPJScriptProtocol *WPJScriptManager::GetScriptEngine()
{
	return m_pScriptEngine;
}

void WPJScriptManager::SetScriptEngine(WPJScriptProtocol *pScriptEngine)
{
	m_pScriptEngine = pScriptEngine;
}

WPJScriptManager::~WPJScriptManager()
{
	ptr_safe_del(m_pScriptEngine);
}