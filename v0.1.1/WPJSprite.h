#ifndef _H_SPRITE
#define _H_SPRITE

#include "WPJStdafx.h"
#include "WPJMacros.h"
#include "WPJNode.h"
#include "WPJGeometry.h"
#include "WPJTexture2D.h"
#include "WPJProtocols.h"
#include "WPJTypes.h"
#include "WPJALGOManager.h"

NS_WPJ_BEGIN

class WPJNodeRGBA;
class WPJTextureProtocol;
class WPJRect;
class WPJTexture2D;
class wpBlendFunc;

class WPJSprite : public WPJNodeRGBA, public WPJTextureProtocol
{
public:
	/**
	 *	Creators
	 */

	WPJSprite();
	static WPJSprite *CreateNewObject();
	virtual WPJSprite *DupCopy();
	virtual WPJSprite *GetCopiedPtr();
	virtual void GetSharedPtr(WPJSprite* &object);
	~WPJSprite();

	//	Create an empty sprite
	static WPJSprite *Create();
	
	//	Create a sprite with an image filename
	static WPJSprite *Create(const char *pszFilename);

	//	Create a sprite with an image and a rect, selected rect will be created
	//	the image origin is upper-left cornor
	static WPJSprite *Create(const char *pszFilename, const WPJRect& rect);

	/**
	 *	Initial
	 */

	//	Initial a sprite with file, param is file route
	void InitWithFile(const char *pszFilename);

	//	Initial a sprite with file and rect , used to create a period texture2d
	//	if rect is zero, rect will use file size automatically
	void InitWithFile(const char *pszFilename, const WPJRect& rect);

	//	Initial a sprite with texture2d, only bitmap will be copied from src texture
	void InitWithTexture(WPJTexture2D *pTexture);

	//	Initial a sprite with texture2d and rect, used to creaye a period texture2d, only bitmap
	//	will be copied from src texture
	void InitWithTexture(WPJTexture2D *pTexture, const WPJRect& rect);

	/**
	 *	Protocols
	 */

	//	Texture
	virtual WPJTexture2D *GetTexture();
	virtual void SetTexture(WPJTexture2D *texture);

	// Blender
	virtual void SetBlendFunc(wpBlendFunc blendFunc);
	virtual wpBlendFunc GetBlendFunc();

	/**
	 *	Draw Params
	 */

	//	if flipHorizontal is true, the sprite will be flip-x when draw
	void SetFlipHorizontal(bool bValue);
	bool IsFlipHorizontal();

	//	if flipVertical is true, the sprite will be flip-y when draw
	void SetFlipVertical(bool bValue);
	bool IsFlipVertical();

	//	if opacityModifyRGB is true, the opacity will affect RGB, for example
	//	-	false -> (R, G, B, ALPHA)
	//	-	true  -> (ALPHA, ALPHA, ALPHA, ALPHA) 
	void SetOpacityModifyRGB(bool bValue);
	bool IsOpacityModifyRGB();

	//	if cascade color is true, the color will affect this node's childrens
	void SetCascadeColorEnabled(bool bValue);
	bool IsCascadeColorEnabled();

	//	if cascade opacity is true, the opacity will affect this node's childrens
	void SetCascadeOpacityEnabled(bool bValue);
	bool IsCascadeOpacityEnabled();

	//	these flag will be used when draw sprite
	void SetDrawFlag(U_CHAR ucValue);

	WPJPoint RelativeConvertToAllegro();
	/**
	 *	Main
	 */
	virtual void Draw();
	virtual void Update(float dt);

private:
	WPJTexture2D *m_pTexture;
	wpBlendFunc m_obBlendFunc;
	
	//	Draw Flag
	U_CHAR m_ucDrawFlag;

	//	Texture flip flags
	bool m_bFlipHorizontal;
	bool m_bFlipVertical;

	//	Opacity modify rgb flag
	bool m_bOpacityModifyRGB;

	//	Cascade color, opacity
	bool m_bCascadeColor;
	bool m_bCascadeOpacity;

};

NS_WPJ_END
#endif