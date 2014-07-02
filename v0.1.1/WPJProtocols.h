#ifndef _H_WPJPROTOCOLS
#define _H_WPJPROTOCOLS

#include "WPJStdafx.h"
#include "WPJMacros.h"
#include "WPJTexture2D.h"
#include "WPJTypes.h"

NS_WPJ_BEGIN

/**
 *	WPJRGBAProtocol is used to affect WPJNode's color and opacity
 */
class WPJRGBAProtocol
{
public:
	/**
	 *	Opacity Methods, DisplayOpacity is the final effect, and Opacity is theory effect
	 */
	virtual U_CHAR GetDisplayOpacity() = 0;
	virtual void UpdateDisplayOpacity(U_CHAR opacity) = 0;
	virtual U_CHAR GetOpacity() = 0;
	virtual void SetOpacity(U_CHAR opacity) = 0;

	/**
	 *	Color Methods, DisplayColor is the final effect, and Color is theory effect
	 */
	virtual const wpColor3B& GetDisplayColor() = 0;
	virtual void UpdateDisplayColor(const wpColor3B& color) = 0;
	virtual void SetColor(const wpColor3B& color) = 0;
	virtual const wpColor3B& GetColor() = 0;
	
	/**
	 *	If OpacityModifyRGB set true, RGB will be modified by Opacity, for example
	 *	r = r * opacity
	 *	g = g * opacity
	 *	b = b * opacity
	 */
	virtual void SetOpacityModifyRGB(bool bValue) = 0;
	virtual bool IsOpacityModifyRGB() = 0;

	/**
	 *	If CascadeOpacityEnabled , node's children will be affect by it's opacity change
	 */
	virtual bool IsCascadeOpacityEnabled() = 0;
	virtual void SetCascadeOpacityEnabled(bool bValue) = 0;

	/**
	 *	If CascadeOpacityEnabled, node's children will be affect by it's color change
	 */
	virtual bool IsCascadeColorEnabled() = 0;
	virtual void SetCascadeColorEnabled(bool bValue) = 0;
};

class WPJBlendProtocol
{
public:
	virtual void SetBlendFunc(wpBlendFunc blendFunc) = 0;
	virtual wpBlendFunc GetBlendFunc() = 0;
};

class WPJTextureProtocol : public WPJBlendProtocol
{
public:
	virtual void SetTexture(WPJTexture2D *texture) = 0;
	virtual WPJTexture2D *GetTexture() = 0;
};

NS_WPJ_END


#endif