#include "WPJTexture2D.h"
#include "WPJGarbageCollection.h"

USING_NS_WPJ

/// WPJTexture2D
//////////////////////////////////////////////////////////////////////////

WPJTexture2D::WPJTexture2D()
:m_pBitmap(NULL)
{

}

WPJTexture2D *WPJTexture2D::CreateNewObject()
{
	WPJTexture2D *t_pTexture2D = new WPJTexture2D();
	t_pTexture2D->Retain();

	WPJGC::GetSharedInst()->AddPtr(t_pTexture2D);

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

bool WPJTexture2D::InitWithFile(const char *pszFilename)
{
	ASSERT(pszFilename != NULL);
	bool bRet = true;

	m_pBitmap = al_load_bitmap(pszFilename);
	if (!m_pBitmap)
	{
		WPJLOG("[%s] Error on loading bitmap : %s\n", _D_NOW_TIME__, pszFilename);
		bRet = false;
	}

	return bRet;
}

bool WPJTexture2D::InitWithSubBitmap(ALLEGRO_BITMAP *bitmap, WPJRect& rect)
{
	ASSERT(bitmap != NULL);
	bool bRet = true;

	m_pBitmap = al_create_sub_bitmap(bitmap, rect.origin.x, rect.origin.y, 
		rect.size.width, rect.size.height);
	if (!m_pBitmap)
	{
		WPJLOG("[%s] Error on creating sub_bitmap \n", _D_NOW_TIME__);
		bRet = false;
	}

	return bRet;	
}

WPJTexture2D::~WPJTexture2D()
{
	ASSERT(m_pBitmap != NULL);
	al_destroy_bitmap(m_pBitmap);
}


