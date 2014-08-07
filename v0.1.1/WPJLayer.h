#ifndef _H_WPJLAYER
#define _H_WPJLAYER

#include "WPJStdafx.h"
#include "WPJMacros.h"
#include "WPJNode.h"

NS_WPJ_BEGIN

/**
 *	WPJLayer is a subclass of CCNode, it should be contain the method to
 *	recieve input from keyboard and mouse, but now there hasn't been realize
 *	because allegro has provide a series of module to recieve input infos
 *
 *	But WPJLayer is still useful, we are considering let it contain ability to
 *	run script! Maybe one day this function can be realized.
 */
class WPJLayer : public WPJNode
{
public:
	WPJLayer();
	~WPJLayer();

	static WPJLayer *CreateNewObject();
	WPJLayer *Copy();
	virtual WPJObject *DupCopy(WPJZone *zone);
};

/**
 *	WPJLayerRGBA is a subclass of WPJLayer, implement WPJRGBAProtocol
 *	It contains color and opacity
 */
class WPJLayerRGBA : public WPJLayer , public WPJRGBAProtocol
{
public:
	WPJLayerRGBA();
	~WPJLayerRGBA();
	static WPJLayerRGBA *CreateNewObject();
	WPJLayerRGBA *Copy();
	virtual WPJObject *DupCopy(WPJZone *zone);

	virtual U_CHAR GetOpacity();
	virtual void SetOpacity(U_CHAR opacity);

	virtual wpColor3B& GetColor();
	virtual void SetColor(const wpColor3B& color);

	virtual U_CHAR GetDisplayOpacity();
	virtual void UpdateDisplayOpacity(U_CHAR opacity);

	virtual wpColor3B& GetDisplayColor();
	virtual void UpdateDisplayColor(const wpColor3B& color);

	virtual void SetOpacityModifyRGB(bool bValue);
	virtual bool IsOpacityModifyRGB();

	virtual bool IsCascadeOpacityEnabled();
	virtual void SetCascadeOpacityEnabled(bool bValue);

	virtual bool IsCascadeColorEnabled();
	virtual void SetCascadeColorEnabled(bool bValue);

protected:
	U_CHAR m_obDisplayOpacity;
	U_CHAR m_obRealOpacity;
	wpColor3B m_obDisplayColor;
	wpColor3B m_obRealColor;
	bool m_bOpacityModifyRGB;
	bool m_bCascadeColorEnabled;
	bool m_bCascadeOpacityEnabled;
};

/**
 *	WPJLayerColor is a subclass of WPJLayerRGBA, implements WPJBlendProtocol
 *	It contains : layer_color , blender and change size
 */
class WPJLayerColor : public WPJLayerRGBA, public WPJBlendProtocol
{
public:
	WPJLayerColor();

	//	Create a WPJLayerColor with size
	static WPJLayerColor *CreateNewObject(float width, float height);

	//	Create a WPJLyaerColor with size and RGB
	static WPJLayerColor *CreateNewObject(float width, float height, wpColor3B &rgb);
	
	//	Create a WPJLayerColor with size and RGBA
	static WPJLayerColor *CreateNewObject(float width ,float height, wpColor3B &rgb, U_CHAR alpha);


	//	Set/Get blendfunc
	virtual void SetBlendFunc(wpBlendFunc blendFunc);
	virtual wpBlendFunc GetBlendFunc();

	//	Change layer size
	void ChangeWidth(float width);
	void ChangeHeight(float height);

	WPJPoint RelativeConvertToAllegro();

	//	Draw Layer
	virtual void Draw();

	~WPJLayerColor();

protected:
	wpBlendFunc m_obBlendFunc;
};


NS_WPJ_END

#endif