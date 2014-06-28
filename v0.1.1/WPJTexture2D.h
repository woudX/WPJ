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
	static WPJTexture2D *CreateNewObject();
	WPJTexture2D();
	virtual WPJTexture2D *DupCopy();
	virtual void GetSharedPtr(WPJTexture2D* &object);
	virtual WPJTexture2D *GetCopiedPtr();
	~WPJTexture2D();

	bool InitWithFile(const char *pszFilename);
	bool InitWithSubBitmap(ALLEGRO_BITMAP *bitmap, WPJRect& rect);

private:
	ALLEGRO_BITMAP *m_pBitmap;
};

NS_WPJ_END
#endif // !_H_WPJTEXTURE2D
