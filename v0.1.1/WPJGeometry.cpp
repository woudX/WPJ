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