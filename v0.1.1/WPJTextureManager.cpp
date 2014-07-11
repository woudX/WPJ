#include "WPJTextureManager.h"
#include "WPJString.h"
#include "WPJTexture2D.h"

USING_NS_WPJ

WPJTextureManager *WPJTextureManager::m_pTextureManager = 0;

WPJTextureManager *WPJTextureManager::GetSharedInst()
{
	if (m_pTextureManager == 0)
		m_pTextureManager = new WPJTextureManager();

	return m_pTextureManager;
}

WPJTextureManager::WPJTextureManager()
{

}

void WPJTextureManager::GC()
{
	std::map<HString, WPJTexture2D*>::iterator itor;
	for (itor = m_mpTextureCache.begin(); itor != m_mpTextureCache.end(); )
	{
		if (itor->second->GetReference() == 1)
		{
			itor->second->Release();
			itor = m_mpTextureCache.erase(itor);
		}
		else
		{
			itor++;
		}
	}	
}

WPJTexture2D *WPJTextureManager::CreateNewTexture2D(const char *pszFilename)
{
	WPJTexture2D *pRet = NULL;
	pRet = CreateNewTexture2D(pszFilename, WPJRectZero);
	return pRet;
}

WPJTexture2D *WPJTextureManager::CreateNewTexture2D(const char *pszFilename, const WPJRect &rect)
{
	HString obBitmapFilename(pszFilename);
	std::map<HString, WPJTexture2D*>::iterator itor;
	WPJTexture2D *pRet = NULL;

	//	find if there is already has an bitmap
	itor = m_mpTextureCache.find(obBitmapFilename);
	if (itor != m_mpTextureCache.end())
	{
		pRet = itor->second;	
	}
	else
	{
		pRet = WPJTexture2D::CreateNewObject();
		pRet->InitWithFile(pszFilename, rect);
		m_mpTextureCache.insert(std::make_pair(HString(pszFilename), pRet));

		//	Retain to 2,  so when it is not used again, the using count is 1
		pRet->Retain();
	}

	return pRet;
}

void WPJTextureManager::ClearTextureCache()
{
	std::map<HString, WPJTexture2D *>::iterator itor;
	for (itor = m_mpTextureCache.begin(); itor != m_mpTextureCache.end();)
	{
		while (itor->second && (itor->second->GetReference() != 0))
		{
			itor->second->Release();
		}
		itor = m_mpTextureCache.erase(itor);
	}
}

WPJTextureManager::~WPJTextureManager()
{
	ClearTextureCache();
}