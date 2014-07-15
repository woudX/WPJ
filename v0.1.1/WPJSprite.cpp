#include "WPJSprite.h"
#include "WPJGarbageCollection.h"
#include "WPJDirector.h"
#include "WPJTextureManager.h"

USING_NS_WPJ

WPJSprite::WPJSprite()
	:m_ucDrawFlag(0)
	,m_obBlendFunc(def_blend)
{

}

WPJSprite *WPJSprite::CreateNewObject()
{
	WPJSprite *t_pSprite = new WPJSprite();
	t_pSprite->AutoRelease();

	return t_pSprite;
}

WPJObject *WPJSprite::DupCopy(WPJZone *zone)
{
	WPJZone *pNewZone = NULL;
	WPJSprite *pRet = NULL;

	if (zone && zone->m_pCopyZone)
	{
		pRet = (WPJSprite *)zone->m_pCopyZone;
	}
	else
	{
		pRet = WPJSprite::CreateNewObject();
		zone = pNewZone = new WPJZone(pRet);
	}

	//	copy parent class
	WPJNodeRGBA::DupCopy(zone);
	ptr_safe_del(pNewZone);

	//	copy this class
	pRet->m_obBlendFunc = m_obBlendFunc;
	pRet->m_ucDrawFlag = m_ucDrawFlag;
	pRet->m_bFlipHorizontal = m_bFlipHorizontal;
	pRet->m_bFlipVertical = m_bFlipVertical;
	pRet->m_bOpacityModifyRGB = m_bOpacityModifyRGB;

	//	Warn : Texture don't copy, they are resource, so can be shared by many sprites
	pRet->m_pTexture = WPJTextureManager::GetSharedInst()
		->CreateNewTexture2D(m_pTexture->GetBitmapPath().c_str());

	return pRet;
}

WPJSprite *WPJSprite::Copy()
{
	return (WPJSprite *)DupCopy(0);
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
	WPJTexture2D *t_pTexture2d = WPJTextureManager::GetSharedInst()->CreateNewTexture2D(pszFilename);
	t_pSprite->SetTexture(t_pTexture2d);

	return t_pSprite;
}

void WPJSprite::Release()
{
	WPJNodeRGBA::Release();
}

void WPJSprite::InitWithFile(const char *pszFilename)
{
	WPJTexture2D *t_pTexture = WPJTextureManager::GetSharedInst()->CreateNewTexture2D(pszFilename);
	SetTexture(t_pTexture);
}

void WPJSprite::InitWithFile(const char *pszFilename, const WPJRect& rect)
{
	WPJTexture2D *t_pTexture = WPJTextureManager::GetSharedInst()->CreateNewTexture2D(pszFilename, rect);
	SetTexture(t_pTexture);
}

//	Texture init not used
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
	WPJ_SAFE_RELEASE(m_pTexture);
	m_pTexture = texture;
	WPJ_SAFE_RETAIN(texture);
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
	WPJALGOManager *algo = WPJALGOManager::GetSharedInst();
	
	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);

	//	scale sprite
	al_scale_transform(&transform,
		m_fScaleX * algo->GetFrameZoomFactor(),
		m_fScaleY * algo->GetFrameZoomFactor()
		);
	al_translate_transform(
		&transform,
		- al_pos.x * (m_fScaleX * algo->GetFrameZoomFactor() - 1),
		- al_pos.y * (m_fScaleY * algo->GetFrameZoomFactor() - 1)
		);

	//	rotate sprite
	float t_fRotateMoveX = al_pos.x + m_pTexture->GetWidth() * m_fScaleX * algo->GetFrameZoomFactor() / 2;
	float t_fRotateMoveY = al_pos.y + m_pTexture->GetHeight() * m_fScaleY * algo->GetFrameZoomFactor() / 2;
	
	al_translate_transform(&transform, -t_fRotateMoveX, -t_fRotateMoveY);
	al_rotate_transform(&transform, m_fAngle);
	al_translate_transform(&transform, t_fRotateMoveX, t_fRotateMoveY);
	
	al_use_transform(&transform);
	
	//	draw sprite
	if (m_obRegion.Equals(WPJRectZero))
	{
		al_draw_tinted_bitmap(
			m_pTexture->GetBitmap(),
			al_map_rgba(m_displayColor.r, m_displayColor.g, m_displayColor.b, m_displayOpacity),
			al_pos.x,al_pos.y,
			m_ucDrawFlag
			);
	}
	else
	{
		al_draw_tinted_bitmap_region(
			m_pTexture->GetBitmap(),
			al_map_rgba(m_displayColor.r, m_displayColor.g, m_displayColor.b, m_displayOpacity),
			m_obRegion.origin.x, m_obRegion.origin.y, m_obRegion.size.width, m_obRegion.size.height,	// draw region
			al_pos.x,al_pos.y,
			m_ucDrawFlag
			);
	}
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
	m_bCascadeColorEnabled = bValue;
}

bool WPJSprite::IsCascadeColorEnabled()
{
	return m_bCascadeColorEnabled;
}

void WPJSprite::SetCascadeOpacityEnabled(bool bValue)
{
	m_bCascadeOpacityEnabled = bValue;
}

bool WPJSprite::IsCascadeOpacityEnabled()
{
	return m_bCascadeOpacityEnabled;
}

WPJPoint WPJSprite::RelativeConvertToAllegro()
{
	WPJPoint t_obAllegroPoint = WPJPointZero;
	WPJPoint t_obWorldPoint = RelativeConvertToWorld();

	WPJSize offsetSize = WPJDirector::GetSharedInst()->GetDrawOffset();
	float scaleX = WPJDirector::GetSharedInst()->GetALGOManager()->GetScaleX();
	float scaleY = WPJDirector::GetSharedInst()->GetALGOManager()->GetScaleY();
	WPJALGOManager *algo = WPJALGOManager::GetSharedInst();

	t_obAllegroPoint.x = t_obWorldPoint.x;
	t_obAllegroPoint.y = t_obWorldPoint.y;

	// scale to fit the screen resolution
	t_obAllegroPoint.x *= algo->GetScaleX() * algo->GetFrameZoomFactor();
	t_obAllegroPoint.y *= algo->GetScaleY() * algo->GetFrameZoomFactor();

	// anchorPoint fixup
	if (!IsIgnoreAnchorPoint())
	{
		t_obAllegroPoint.x -= m_obAnchorPoint.x * m_pTexture->GetWidth() * algo->GetFrameZoomFactor();
		t_obAllegroPoint.y -= m_obAnchorPoint.y * m_pTexture->GetHeight() * algo->GetFrameZoomFactor();
	}

	// update offset to adjust content to real origin
	t_obAllegroPoint.x += offsetSize.width * algo->GetFrameZoomFactor();
	t_obAllegroPoint.y += offsetSize.height * algo->GetFrameZoomFactor();

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
	//	Release texture2d
	WPJ_SAFE_RELEASE(m_pTexture);
}