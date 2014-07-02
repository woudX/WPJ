#include "WPJALGOProtocol.h"

USING_NS_WPJ

WPJALGOProtocol::WPJALGOProtocol()
:m_obResolutionPolicy(wResolutionUnknown)
,m_fScaleX(1.0f)
,m_fScaleY(1.0f)
{

}

float WPJALGOProtocol::GetScaleX()
{
	return m_fScaleX;
}

void WPJALGOProtocol::SetScaleX(float var)
{
	m_fScaleX = var;
}

float WPJALGOProtocol::GetScaleY()
{
	return m_fScaleY;
}

void WPJALGOProtocol::SetScaleY(float var)
{
	m_fScaleY = var;
}

void WPJALGOProtocol::SetFrameSize(float width, float height)
{
	m_obDesignResolutionSize = m_obScreenSize = _nsize(width, height);
}

WPJSize &WPJALGOProtocol::GetFrameSize()
{
	return m_obScreenSize;
}

WPJSize &WPJALGOProtocol::GetResolutionSize()
{
	
	return m_obDesignResolutionSize;
}

void WPJALGOProtocol::SetDesignResolutionSize(float width, float height, ResolutionPolicy resolutionPolicy)
{
	ASSERT(resolutionPolicy != wResolutionUnknown);

	m_obDesignResolutionSize.SetSize(width, height);

	m_fScaleX = (float)m_obScreenSize.width / m_obDesignResolutionSize.width;
	m_fScaleY = (float)m_obScreenSize.height / m_obDesignResolutionSize.width;

	// decide to select which scale
	if (resolutionPolicy == wResolutionNoBorder)
	{
		m_fScaleX = m_fScaleY = MAX(m_fScaleX, m_fScaleY);
	}
	else if (resolutionPolicy == wResolutionShowAll)
	{
		m_fScaleX = m_fScaleY = MIN(m_fScaleX, m_fScaleY);
	}

	// calculate the rect of viewport
	float fViewPortW = m_obDesignResolutionSize.width * m_fScaleX;
	float fViewPortH = m_obDesignResolutionSize.height * m_fScaleY;

	m_obViewPortRect.SetRect((m_obScreenSize.width - fViewPortW) / 2, 
		(m_obScreenSize.height - fViewPortH) / 2,
		fViewPortW, fViewPortH);

	m_obResolutionPolicy = resolutionPolicy;
}

WPJALGOProtocol::~WPJALGOProtocol()
{

}