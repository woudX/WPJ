#ifndef _H_WPJTEXTUREMANAGER
#define _H_WPJTEXTUREMANAGER

#include "WPJStdafx.h"
#include "WPJMacros.h"
#include "WPJGeometry.h"

NS_WPJ_BEGIN

class WPJTexture2D;
class HString;

/**
 *	WPJTextureManager contains all textures that used in system, by using
 *	this class, different places can share a texture at one time
 *	
 *	When the texture is not used again, it can be collected
 */

class WPJTextureManager
{
public:
	//	Get	WPJTextureManager
	static WPJTextureManager *GetSharedInst();

	//	Using this method to get a new Texture2D with image filename
	//	If there is already has a texture2d, manager won't create a new one
	//	but return this texture2d
	WPJTexture2D *CreateNewTexture2D(const char *pszFilename);
	WPJTexture2D *CreateNewTexture2D(const char *pszFilename, const WPJRect &rect);
	//	Collect all not used WPJTexture2D
	void GC();

	//	Clear all textures in cache
	//	[Notice] don't call this method unless you know no one is using textures
	//	at this time
	void ClearTextureCache();

	~WPJTextureManager();

protected:
	WPJTextureManager();

private:
	static WPJTextureManager *m_pTextureManager;
	std::map<HString, WPJTexture2D*> m_mpTextureCache;
};

NS_WPJ_END

#endif