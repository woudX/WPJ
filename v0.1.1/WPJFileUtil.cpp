#include "WPJFileUtil.h"

using namespace std;

NS_WPJ_BEGIN

WPJFileUtil *WPJFileUtil::m_pInst = 0;

WPJFileUtil::WPJFileUtil()
{
	
}

WPJFileUtil *WPJFileUtil::GetSharedInst()
{
	if (m_pInst == 0)
	{
		m_pInst = new WPJFileUtil();
		m_pInst->Init();
	}
	
	return m_pInst;
}

void WPJFileUtil::Init()
{
	//	add a empty search resolution, so that when search the root will find first
	AddSearchResolution("");
}

void WPJFileUtil::AddSearchPath(const char *path)
{
	std::string opt(path);
	bool bExist = false;

	foreach_in_list_auto(std::string, itor, m_lSearchPaths)
	{
		if (pp(itor).compare(opt) == 0)
		{
			bExist = true;
			break;
		}
	}

	if (!bExist)
		m_lSearchPaths.push_back(opt);
}

void WPJFileUtil::RemoveSearchPath(const char *path)
{
	std::string opt(path);
	m_lSearchPaths.remove(opt);
}

void WPJFileUtil::AddSearchResolution(const char *path)
{
	std::string opt(path);
	bool bExist = false;

	foreach_in_list_auto(std::string, itor, m_lSearchResolutions)
	{
		if (pp(itor).compare(opt) == 0)
		{
			bExist = true;
			break;
		}
	}

	if (!bExist)
		m_lSearchResolutions.push_back(opt);
}

void WPJFileUtil::RemoveSearchResolution(const char *path)
{
	std::string opt(path);

	m_lSearchResolutions.remove(opt);
}

std::string WPJFileUtil::GetFullPath(const char *path)
{
	std::string origin(path);
	std::string ret(origin);
	bool bInCache = false;
	bool bFind = false;

	if (m_hPathsCache.find(origin) != m_hPathsCache.end())
	{
		//	find ret in cache
		ret = m_hPathsCache.at(origin);
		bInCache = true;
		bFind = true;
	}
	else
	{
		//	find in SearchPaths ¡Á SearchResolutions
		ASSERT(m_lSearchPaths.size() != 0);
		
		foreach_in_list_auto(std::string, pathItor, m_lSearchPaths)
		{
			if (bFind)
				break;

			foreach_in_list_auto(std::string ,resolutionItor, m_lSearchResolutions)
			{
				std::string fullPath = "";
				fullPath += pp(pathItor);
				fullPath += pp(resolutionItor);
				fullPath += origin;

				if (IsFileExist(fullPath))
				{
					ret = fullPath;
					bFind = true;
					break;
				}
			}
		}
	}

	if (!bInCache)
		AddPathToCache(origin, ret);

	return ret;
}

void WPJFileUtil::AddPathToCache(std::string origin, std::string full)
{
	m_hPathsCache.insert(std::make_pair(origin, full));
}

bool WPJFileUtil::IsFileExist(const std::string& fullPath)
{
	bool bRet = true;

	if (!fopen(fullPath.c_str(), "r+"))
	{
		bRet = false;
	}
	
	return bRet;
}

WPJFileUtil::~WPJFileUtil()
{
	m_lSearchPaths.clear();
	m_lSearchResolutions.clear();
	m_hPathsCache.clear();
}

NS_WPJ_END