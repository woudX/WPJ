#include "WPJGeometry.h"

USING_NS_WPJ

WPJPoint WPJPoint::zero = WPJPoint(0,0);

WPJPoint::WPJPoint()
:x(0.f)
,y(0.f)
{

}

WPJPoint::WPJPoint(const WPJPoint &rhs)
:x(rhs.x)
,y(rhs.y)
{
	
}

WPJPoint::WPJPoint(float fx, float fy)
:x(fx)
,y(fy)
{

}

WPJPoint WPJPoint::operator+ (const WPJPoint &rhs) const
{
	return WPJPoint(x + rhs.x, y + rhs.y);
}

WPJPoint WPJPoint::operator- (const WPJPoint &rhs) const
{
	return WPJPoint(x - rhs.x, y - rhs.y);
}

WPJPoint WPJPoint::operator- () const
{
	return WPJPoint(-x, -y);
}

WPJPoint WPJPoint::operator* (float ft) const
{
	return WPJPoint(x * ft, y * ft);
}

WPJPoint WPJPoint::operator/ (float ft) const
{
	ASSERT(ft != 0.f);
	return WPJPoint(x / ft, y / ft);
}

bool WPJPoint::Equals(const WPJPoint &rhs) const
{
	return (fabs(x - rhs.x) <= FLT_EPSILON && fabs(y - rhs.y) <= FLT_EPSILON);
}

void WPJPoint::SetPoint(float fx, float fy)
{
	x = fx;
	y = fy;
}

float WPJPoint::GetAngle(const WPJPoint &rhs) const
{
	float t_fCross = Cross(rhs);
	float t_fDot = Dot(rhs);

	ASSERT(t_fDot != 0.f);
	return atan2f(t_fCross, t_fDot);
}

WPJPoint WPJPoint::RotateByAngle(const WPJPoint &pivot, float fAngle) const
{
	return pivot + (*this - pivot).Rotate(WPJPoint::ForAngle(fAngle));
}

WPJPoint WPJPoint::RotateByAngle(float fAngle) const
{
	return zero + (*this - zero).Rotate(WPJPoint::ForAngle(fAngle));
}

WPJPoint::~WPJPoint()
{

}

WPJSize::WPJSize()
:width(0.f)
,height(0.f)
{

}

WPJSize::WPJSize(const WPJSize &rhs)
:width(rhs.width)
,height(rhs.height)
{

}

WPJSize::WPJSize(float fx, float fy)
:width(fx)
,height(fy)
{

}

WPJSize::WPJSize(const WPJPoint &rhs)
{
	SetSize(rhs.x, rhs.y);
}

WPJSize &WPJSize::operator= (const WPJSize &rhs)
{
	SetSize(rhs.width, rhs.height);
	return *this;
}

WPJSize &WPJSize::operator= (const WPJPoint &rhs)
{
	SetSize(rhs.x, rhs.y);
	return *this;
}

WPJSize WPJSize::operator+ (const WPJSize &rhs) const
{
	return WPJSize(width + rhs.width, height + rhs.height);
}

WPJSize WPJSize::operator- (const WPJSize &rhs) const
{
	return WPJSize(width - rhs.width, height - rhs.height);
}

WPJSize WPJSize::operator* (const WPJSize &rhs) const
{
	return WPJSize(width * rhs.width, height * rhs.height);
}

WPJSize WPJSize::operator/ (const WPJSize &rhs) const
{
	ASSERT(rhs.width != 0 && rhs.height != 0);
	return WPJSize(width / rhs.width, height / rhs.height);
}

void WPJSize::SetSize(float fx, float fy)
{
	width = fx;
	height = fy;
}

bool WPJSize::Equals(const WPJSize &rhs) const
{
	return fabs(width - rhs.width) <= FLT_EPSILON && fabs(height - rhs.height) <= FLT_EPSILON;
}

WPJSize::~WPJSize()
{

}