#include "WPJTexture2D.h"
#include "WPJGarbageCollection.h"
#include "WPJLib.h"

USING_NS_WPJ

/// WPJTexture2D
//////////////////////////////////////////////////////////////////////////

WPJTexture2D::WPJTexture2D()
	:m_pBitmap(NULL)
	,m_obBitmapPath(HString(""))
{

}

WPJTexture2D *WPJTexture2D::CreateNewObject()
{
	WPJTexture2D *t_pTexture2D = new WPJTexture2D();
	t_pTexture2D->AutoRelease();

	return t_pTexture2D;
}

WPJTexture2D *WPJTexture2D::DupCopy()
{
	return NULL;
}

WPJTexture2D *WPJTexture2D::GetCopiedPtr()
{
	return DupCopy();
}

void WPJTexture2D::GetSharedPtr(WPJTexture2D* &object)
{
	object = this;
	object->Retain();
}

ALLEGRO_BITMAP *WPJTexture2D::GetBitmap()
{
	return m_pBitmap;
}

HString WPJTexture2D::GetBitmapPath()
{
	return m_obBitmapPath;
}

void WPJTexture2D::SetBitmapPath(HString var)
{
	m_obBitmapPath = var;
}

bool WPJTexture2D::InitWithFile(const char *pszFilename)
{
	ASSERT(pszFilename != NULL);
	bool bRet = true;

	m_pBitmap = al_load_bitmap(pszFilename);
	m_obBitmapPath = HString(pszFilename);
	if (!m_pBitmap)
	{
		WPJLOG("[%s] Error on loading bitmap : %s\n", _D_NOW_TIME__, pszFilename);
		bRet = false;
	}

	return bRet;
}

bool WPJTexture2D::InitWithFile(const char *pszFilename, const WPJRect& rect)
{
	ASSERT(pszFilename != NULL);
	bool bRet = true;

	// check rect, if rect is zero create a full bitmap
	if (rect.Equals(WPJRectZero))
	{
		bRet = InitWithFile(pszFilename);
	}
	else
	{
		ALLEGRO_BITMAP *t_pBitmap = al_load_bitmap(pszFilename);
		m_obBitmapPath = HString(pszFilename);
		if (!t_pBitmap)
		{
			WPJLOG("[%s] Error on loading bitmap : %s\n", _D_NOW_TIME__, pszFilename);
			bRet = false;
		}

		bRet = SubBitmap(t_pBitmap, m_pBitmap, rect);
		al_destroy_bitmap(t_pBitmap);
	}
	
	return bRet;
}

bool WPJTexture2D::InitWithTexture(WPJTexture2D *pTexture)
{
	bool bRet = CopyBitmap(pTexture->GetBitmap(), m_pBitmap);
	m_obBitmapPath = pTexture->GetBitmapPath();

	return bRet;
}

bool WPJTexture2D::InitWithTexture(WPJTexture2D *pTexture, const WPJRect& rect)
{
	ASSERT(pTexture != NULL);
	bool bRet = true;

	if (rect.Equals(WPJRectZero))
	{
		bRet = InitWithTexture(pTexture);
	}
	else
	{
		bRet = SubBitmap(pTexture->GetBitmap(), m_pBitmap, rect);
		m_obBitmapPath = pTexture->m_obBitmapPath;
	}

	return bRet;
}

float WPJTexture2D::GetWidth()
{
	return al_get_bitmap_width(m_pBitmap);
}

float WPJTexture2D::GetHeight()
{
	return al_get_bitmap_height(m_pBitmap);
}

bool WPJTexture2D::SubBitmap(ALLEGRO_BITMAP *src, ALLEGRO_BITMAP *dst, const WPJRect& rect)
{
	ASSERT(src != NULL);
	bool bRet = true;

	if (rect.Equals(WPJRectZero))
		dst = al_clone_bitmap(src);
	else
		dst = al_create_sub_bitmap(src, rect.origin.x, rect.origin.y, 
			rect.size.width, rect.size.height);

	if (!dst)
	{
		WPJLOG("[%s] Error on creating sub_bitmap \n", _D_NOW_TIME__);
		bRet = false;
		src = NULL;
	}

	return bRet;
}

bool WPJTexture2D::CopyBitmap(ALLEGRO_BITMAP *src, ALLEGRO_BITMAP *dst)
{
	ASSERT(src != NULL);
	bool bRet = true;

	dst = al_clone_bitmap(src);
	if (!dst)
	{
		WPJLOG("[%s] Error on copying bitmap \n", _D_NOW_TIME__);
		bRet = false;
		src = NULL;
	}

	return bRet;
}

WPJTexture2D::~WPJTexture2D()
{
	ASSERT(m_pBitmap != NULL);
	al_destroy_bitmap(m_pBitmap);
}


