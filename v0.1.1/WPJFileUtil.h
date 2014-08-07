#ifndef _H_WPJFILEUTIL
#define _H_WPJFILEUTIL

#include "WPJStdafx.h"
#include "WPJMacros.h"

NS_WPJ_BEGIN

/**
 *	briefly, this class is used to redirector path of file
 */

class WPJFileUtil
{
public:
	static WPJFileUtil *GetSharedInst();

	//	Add/Remove a search path
	void AddSearchPath(const char *path);
	void RemoveSearchPath(const char *path);

	//	Add/Remove a searh resolution
	void AddSearchResolution(const char *path);
	void RemoveSearchResolution(const char *path);

	//	Get full path with search path
	std::string GetFullPath(const char *path);

	//	Add a path to cache with a full path for next find
	void AddPathToCache(std::string origin, std::string full);

	//	return a bool that if file is exist in fullPath
	bool IsFileExist(const std::string& fullPath);

	~WPJFileUtil();

protected:
	WPJFileUtil();

	//	Initialization
	void Init();

	//	real path can be display by m_lSearchPath ¡Á m_lSearchResolutions
	std::list<std::string> m_lSearchPaths;
	std::list<std::string> m_lSearchResolutions;

	//	once path find, cache will save this 
	std::map<std::string, std::string> m_hPathsCache;

private:
	static WPJFileUtil *m_pInst;
};

#define full_path(pszFileName) (WPJFileUtil::GetSharedInst()->GetFullPath(pszFileName))

NS_WPJ_END

#endif