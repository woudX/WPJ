#ifndef _H_WPJTEXTURE2D
#define _H_WPJTEXTURE2D

#include "WPJStdafx.h"
#include "WPJMacros.h"
#include "WPJObject.h"
#include "WPJALGOManager.h"

NS_WPJ_BEGIN

class WPJTexture2D : public WPJObject
{
public:
	/**
	 *	Inherite Methods
	 */
	static WPJTexture2D *CreateNewObject();
	WPJTexture2D();
	virtual WPJTexture2D *DupCopy();
	virtual void GetSharedPtr(WPJTexture2D* &object);
	virtual WPJTexture2D *GetCopiedPtr();
	~WPJTexture2D();

	/**
	 *	Initial Methods
	 */

	//	Initial a texture2d with file, param is file route
	bool InitWithFile(const char *pszFilename);

	//	Initial a texture2d with file and rect , used to create a period texture2d
	//	if rect is zero, this method is same with InitWithFile(const char *pszFilename)
	bool InitWithFile(const char *pszFilename, const WPJRect& rect);

	//	Initial a texture2d with texture2d, only bitmap will be copied from src texture
	bool InitWithTexture(WPJTexture2D *pTexture);

	//	Initial a texture2d with texture2d and rect, used to creaye a period texture2d, only bitmap
	//	will be copied from src texture
	bool InitWithTexture(WPJTexture2D *pTexture, const WPJRect& rect);

	/**
	 *	Bitmap Properties
	 */

	float GetWidth();
	float GetHeight();

protected:
	/**
	 *	Bitmap Operation Methods
	 */

	//	Copy a rect from src bitmap to dst bitmap, if return false then dst = NULL
	bool SubBitmap(ALLEGRO_BITMAP *src, ALLEGRO_BITMAP *dst, const WPJRect& rect);

	//	Copy a bitmap from src to dst, if return false then dst = NULL
	bool CopyBitmap(ALLEGRO_BITMAP *src, ALLEGRO_BITMAP *dst);

private:
	WPJ_PROPERTY_READONLY(ALLEGRO_BITMAP*, m_pBitmap, Bitmap)
	WPJ_PROPERTY(HString, m_obBitmapPath, BitmapPath)
};

NS_WPJ_END
#endif // !_H_WPJTEXTURE2D
