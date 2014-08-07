#include "WPJLayer.h"
#include "WPJDirector.h"

USING_NS_WPJ

/// WPJLayer
//////////////////////////////////////////////////////////////////////////
WPJLayer::WPJLayer()
{

}

WPJLayer::~WPJLayer()
{

}

WPJLayer *WPJLayer::CreateNewObject()
{
	WPJLayer *ret = new WPJLayer();
	ret->AutoRelease();

	return ret;
}

WPJObject *WPJLayer::DupCopy(WPJZone *zone)
{
	WPJLayer *pRet = NULL;
	WPJZone *pNewZone = NULL;

	if (zone && zone->m_pCopyZone) 
	{
		pRet = (WPJLayer *)zone->m_pCopyZone;
	} 
	else
	{
		pRet = WPJLayer::CreateNewObject();
		pNewZone = zone = new WPJZone(pRet);
	}

	WPJNode::DupCopy(zone);
	ptr_safe_del(pNewZone);

	return pRet;
}

WPJLayer *WPJLayer::Copy()
{
	return (WPJLayer*)DupCopy(0);
}

/// WPJLayerRGBA
//////////////////////////////////////////////////////////////////////////

WPJLayerRGBA::WPJLayerRGBA()
	:m_obDisplayOpacity(1.0f)
	,m_obRealOpacity(1.0f)
	,m_obDisplayColor(wpColor3B(255, 255, 255))
	,m_obRealColor(wpColor3B(255, 255, 255))
	,m_bCascadeColorEnabled(false)
	,m_bCascadeOpacityEnabled(false)
	,m_bOpacityModifyRGB(false)
{

}

WPJLayerRGBA *WPJLayerRGBA::CreateNewObject()
{
	WPJLayerRGBA *pRet = new WPJLayerRGBA();
	pRet->AutoRelease();

	return pRet;
}

WPJObject *WPJLayerRGBA::DupCopy(WPJZone *zone)
{
	WPJLayerRGBA *pRet = NULL;
	WPJZone *pNewZone = NULL;

	if (zone && zone->m_pCopyZone) 
	{
		pRet = (WPJLayerRGBA *) zone->m_pCopyZone;
	}
	else
	{
		pRet = WPJLayerRGBA::CreateNewObject();
		pNewZone = zone = new WPJZone(pRet);
	}

	WPJLayer::DupCopy(zone);
	ptr_safe_del(pNewZone);

	return pRet;
}

WPJLayerRGBA *WPJLayerRGBA::Copy()
{
	return (WPJLayerRGBA *)DupCopy(0);
}

U_CHAR WPJLayerRGBA::GetOpacity()
{
	return m_obRealOpacity;
}

void WPJLayerRGBA::SetOpacity(U_CHAR opacity)
{
	m_obRealOpacity = opacity;
}

wpColor3B& WPJLayerRGBA::GetColor()
{
	return m_obRealColor;
}

void WPJLayerRGBA::SetColor(const wpColor3B& color)
{
	m_obRealColor = color;
}

U_CHAR WPJLayerRGBA::GetDisplayOpacity()
{
	return m_obDisplayOpacity;
}

void WPJLayerRGBA::UpdateDisplayOpacity(U_CHAR opacity)
{
	m_obDisplayOpacity = opacity;
}

wpColor3B& WPJLayerRGBA::GetDisplayColor()
{
	return m_obDisplayColor;
}

void WPJLayerRGBA::UpdateDisplayColor(const wpColor3B& color)
{
	m_obDisplayColor = color;
}

void WPJLayerRGBA::SetOpacityModifyRGB(bool bValue)
{
	m_bOpacityModifyRGB = bValue;
}

bool WPJLayerRGBA::IsOpacityModifyRGB()
{
	return m_bOpacityModifyRGB;
}

void WPJLayerRGBA::SetCascadeColorEnabled(bool bValue)
{
	m_bCascadeColorEnabled = bValue;
}

bool WPJLayerRGBA::IsCascadeColorEnabled()
{
	return m_bCascadeColorEnabled;
}

void WPJLayerRGBA::SetCascadeOpacityEnabled(bool bValue)
{
	m_bCascadeOpacityEnabled = bValue;
}

bool WPJLayerRGBA::IsCascadeOpacityEnabled()
{
	return m_bCascadeOpacityEnabled;
}

WPJLayerRGBA::~WPJLayerRGBA()
{

}

/// WPJLayerColor
//////////////////////////////////////////////////////////////////////////

WPJLayerColor::WPJLayerColor()
{

}

WPJLayerColor *WPJLayerColor::CreateNewObject(float width, float height)
{
	return CreateNewObject(width, height, wpc3(255, 255, 255));
}

WPJLayerColor *WPJLayerColor::CreateNewObject(float width, float height, wpColor3B &rgb)
{
	return CreateNewObject(width, height, rgb, 0);
}

WPJLayerColor *WPJLayerColor::CreateNewObject(float width ,float height, wpColor3B &rgb, U_CHAR alpha)
{
	WPJLayerColor *bRet = new WPJLayerColor();

	if (bRet)
	{
		bRet->AutoRelease();

		bRet->SetContentSize(_nsize(width, height));
		bRet->SetColor(rgb);
		bRet->SetOpacity(alpha);
	}

	return bRet;
}

void WPJLayerColor::SetBlendFunc(wpBlendFunc blendFunc)
{
	m_obBlendFunc = blendFunc;
}

wpBlendFunc WPJLayerColor::GetBlendFunc()
{
	return m_obBlendFunc;
}

void WPJLayerColor::ChangeWidth(float width)
{
	SetContentSize(_nsize(width, m_obContentSize.height));
}

void WPJLayerColor::ChangeHeight(float height)
{
	SetContentSize(_nsize(m_obContentSize.width, height));
}

WPJPoint WPJLayerColor::RelativeConvertToAllegro()
{
	return WPJNode::RelativeConvertToAllegro();
}

void WPJLayerColor::Draw()
{

}

WPJLayerColor::~WPJLayerColor()
{

}





