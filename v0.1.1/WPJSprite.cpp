#include "WPJSprite.h"
#include "WPJGarbageCollection.h"

USING_NS_WPJ

WPJSprite::WPJSprite()
	:m_ucDrawFlag(0)
	,m_obBlendFunc(def_blend)
{

}

WPJSprite *WPJSprite::CreateNewObject()
{
	WPJSprite *t_pSprite = new WPJSprite();
	t_pSprite->Retain();

	WPJGC::GetSharedInst()->AddPtr(t_pSprite);
	return t_pSprite;
}

WPJSprite *WPJSprite::DupCopy()
{
	return NULL;
}

WPJSprite *WPJSprite::GetCopiedPtr()
{
	return DupCopy();
}

void WPJSprite::GetSharedPtr(WPJSprite* &object)
{
	object = this;
	object->Retain();
}

WPJSprite *WPJSprite::Create()
{
	WPJSprite *t_pSprite = CreateNewObject();
	return t_pSprite;
}

WPJSprite *WPJSprite::Create(const char *pszFilename)
{
	WPJSprite *t_pSprite = CreateNewObject();
	t_pSprite->InitWithFile(pszFilename);
	return t_pSprite;
}

void WPJSprite::InitWithFile(const char *pszFilename)
{
	WPJTexture2D *t_pTexture = WPJTexture2D::CreateNewObject();
	t_pTexture->InitWithFile(pszFilename);
	SetTexture(t_pTexture);
}

void WPJSprite::InitWithFile(const char *pszFilename, const WPJRect& rect)
{
	WPJTexture2D *t_pTexture = WPJTexture2D::CreateNewObject();
	t_pTexture->InitWithFile(pszFilename, rect);
	SetTexture(t_pTexture);
}

void WPJSprite::InitWithTexture(WPJTexture2D *pTexture)
{
	WPJTexture2D *t_pTexture = WPJTexture2D::CreateNewObject();
	t_pTexture->InitWithTexture(pTexture);
	SetTexture(t_pTexture);
}

void WPJSprite::InitWithTexture(WPJTexture2D *pTexture, const WPJRect& rect)
{
	WPJTexture2D *t_pTexture = WPJTexture2D::CreateNewObject();
	t_pTexture->InitWithTexture(pTexture, rect);
	SetTexture(t_pTexture);
}

WPJTexture2D *WPJSprite::GetTexture()
{
	return m_pTexture;
}

void WPJSprite::SetTexture(WPJTexture2D *texture)
{
	if (m_pTexture != NULL)
		m_pTexture->Release();

	m_pTexture = texture;
}

wpBlendFunc WPJSprite::GetBlendFunc()
{
	return m_obBlendFunc;
}

void WPJSprite::SetBlendFunc(wpBlendFunc blendFunc)
{
	m_obBlendFunc = blendFunc;
}

void WPJSprite::Draw()
{
	// set blender
	al_set_blender(m_obBlendFunc.func, m_obBlendFunc.src, m_obBlendFunc.dest);

	WPJPoint al_pos = RelativeConvertToAllegro();

	if (m_obRegion.Equals(WPJRectZero))
		al_draw_tinted_scaled_rotated_bitmap(
			m_pTexture->GetBitmap(),
			al_map_rgba(m_displayColor.r, m_displayColor.g, m_displayColor.b, m_displayOpacity),		// tint rgba
			m_pTexture->GetWidth() * m_obAnchorPoint.x, 
			m_pTexture->GetHeight() * m_obAnchorPoint.y,	// rotate center
			al_pos.x, al_pos.y,			// draw destination
			m_fScaleX, m_fScaleY,		// scale
			m_fAngle,		// rotate angle
			m_ucDrawFlag);	// draw flag
	else
		al_draw_tinted_scaled_rotated_bitmap_region(
			m_pTexture->GetBitmap(),
			m_obRegion.origin.x, m_obRegion.origin.y, m_obRegion.size.width, m_obRegion.size.height,	// draw region
			al_map_rgba_f(m_displayColor.r, m_displayColor.g, m_displayColor.b, m_displayOpacity),		// tint rgba
			m_pTexture->GetWidth() * m_obAnchorPoint.x, 
			m_pTexture->GetHeight() * m_obAnchorPoint.y,	// rotate center
			al_pos.x, al_pos.y,			// draw destination
			m_fScaleX, m_fScaleY,		// scale
			m_fAngle,		// rotate angle
			m_ucDrawFlag);	// draw flag
}

void WPJSprite::SetFlipHorizontal(bool bValue)
{
	m_bFlipHorizontal = bValue;
}

bool WPJSprite::IsFlipHorizontal()
{
	return m_bFlipHorizontal;
}

void WPJSprite::SetFlipVertical(bool bValue)
{
	m_bFlipVertical = bValue;
}

bool WPJSprite::IsFlipVertical()
{
	return m_bFlipVertical;
}

void WPJSprite::SetOpacityModifyRGB(bool bValue)
{
	m_bOpacityModifyRGB = bValue;
}

bool WPJSprite::IsOpacityModifyRGB()
{
	return m_bOpacityModifyRGB;
}

void WPJSprite::SetCascadeColorEnabled(bool bValue)
{
	m_bCascadeColor = bValue;
}

bool WPJSprite::IsCascadeColorEnabled()
{
	return m_bCascadeColor;
}

void WPJSprite::SetCascadeOpacityEnabled(bool bValue)
{
	m_bCascadeOpacity = bValue;
}

bool WPJSprite::IsCascadeOpacityEnabled()
{
	return m_bCascadeOpacity;
}

WPJPoint WPJSprite::RelativeConvertToAllegro()
{
	WPJPoint t_obAllegroPoint = WPJPointZero;
	WPJPoint t_obWorldPoint = RelativeConvertToWorld();

	if (IsIgnoreAnchorPoint())
	{
		t_obAllegroPoint.x = t_obWorldPoint.x;
		t_obAllegroPoint.y = t_obWorldPoint.y;
	}
	else
	{
		t_obAllegroPoint.x = t_obWorldPoint.x - m_obAnchorPoint.x * m_pTexture->GetWidth();
		t_obAllegroPoint.y = t_obWorldPoint.y - m_obAnchorPoint.y * m_pTexture->GetHeight();
	}
	


	return t_obAllegroPoint;
}

void WPJSprite::SetDrawFlag(U_CHAR ucValue)
{
	m_ucDrawFlag = ucValue;
}

void WPJSprite::Update(float dt)
{

}

WPJSprite::~WPJSprite()
{

}