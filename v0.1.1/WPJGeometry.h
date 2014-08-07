#ifndef _H_WPJGEOMETRY
#define _H_WPJGEOMETRY

#include "WPJStdafx.h"
#include "WPJMacros.h"
#include "WPJGeometryEx.h"

/**
 *	WPJGeometry contains many kinds of geometry class used in the WPJEngine, including:
 *	- WPJPoint
 *	- WPJSize
 */

NS_WPJ_BEGIN

class WPJPoint 
{
public:
	float x,y;

	WPJPoint();
	WPJPoint(float fx, float fy);
	WPJPoint(const WPJPoint &rhs);

	WPJPoint operator + (const WPJPoint &rhs) const;
	WPJPoint &operator +=(const WPJPoint &rhs) ;
	WPJPoint operator - (const WPJPoint &rhs) const;
	WPJPoint &operator -=(const WPJPoint &rhs) ;

	WPJPoint operator - () const;

	WPJPoint operator * (float ft) const;
	WPJPoint operator / (float ft) const;

	bool Equals (const WPJPoint &rhs) const;
	void SetPoint (float fx, float fy);
	// Calculates the distance between this and origin
	inline float GetLength() const
	{
		return sqrtf(x * x + y * y);
	}

	// Calculates the distance between this and origin (not use mathlib)
	inline float GetLengthSq() const
	{
		return Dot(*this);
	}

	// Calculates the distance between two points (not use mathlib)
	inline float GetDistanceSq(const WPJPoint &rhs) const 
	{
		return (*this - rhs).GetLengthSq();
	}

	// Calculates the distance between two points 
	inline float GetDistance(const WPJPoint &rhs) const
	{
		return (*this - rhs).GetLength();
	}

	// Get angle between this and X-axis
	inline float GetAngle() const
	{
		return atan2f(y, x);
	}

	// Get angle between two vectors
	float GetAngle(const WPJPoint &rhs) const;

	// Calculates perpendicular of v, rotated 90 degrees counter-clockwise -- cross(v, GetPerp(v)) >= 0
	inline WPJPoint GetPerp() const 
	{
		return WPJPoint(-y, x);
	}

	// Calculates perpendicular of v, rotated 90 degrees clockwise -- cross(v, GetRPerp(v)) <= 0
	inline WPJPoint GetRPerp() const
	{
		return WPJPoint(y, -x);
	}

	// Get the projection of this over rhs
	inline WPJPoint Projection(const WPJPoint &rhs) const
	{
		return rhs * (Dot(rhs) / rhs.Dot(rhs));
	}

	// Get the Normalize of this
	inline WPJPoint Normalize()
	{
		float t_fLength = GetLength();
		if (t_fLength == 0.) 
			return WPJPoint(1.f ,0);
		else
			return *this / GetLength();
	}

	// Calculates the dot of two vectors
	inline float Dot(const WPJPoint &rhs) const
	{
		return x * rhs.x + y * rhs.y;
	}

	// Calculates the cross of two vectors
	inline float Cross(const WPJPoint &rhs) const
	{
		return x * rhs.y - y * rhs.x;
	}

	// Linear Interpolation between two points a and b
	// @a = 0 is this
	// @b = 0 is rhs
	inline WPJPoint Lerp(const WPJPoint &rhs, float alpha) const
	{
		return *this * (1.f - alpha) + rhs * alpha;
	}

	// Calculates vector rotates by pivot and angle
	// @pviot is rotate point
	// @fAngle is rotate angle
	WPJPoint RotateByAngle(const WPJPoint &pivot, float fAngle) const;

	// Calculates vector rotates by angle (Rotate point is (0,0))
	WPJPoint RotateByAngle(float fAngle) const;

	// Calculates vector rotates (counter-clockwize)
	inline WPJPoint Rotate(const WPJPoint &rhs)
	{
		return WPJPoint(x*rhs.x - y*rhs.y, x*rhs.y + y*rhs.x);
	}

	// Calculates vector rotates (clockwize)
	inline WPJPoint Unrotate(const WPJPoint &rhs)
	{
		return WPJPoint(x*rhs.x + y*rhs.y, x*rhs.y - y*rhs.x);
	}

	// Transform angle to unit vector for rotates
	static inline WPJPoint ForAngle(const float a)
	{
		return WPJPoint(cosf(a), sinf(a));
	}
	
	~WPJPoint();
};

class WPJSize
{
public:
	float width, height;
	WPJSize();
	WPJSize(const WPJSize &rhs);
	WPJSize(const WPJPoint &rhs);
	WPJSize(float fx, float fy);

	void SetSize(float fx, float fy);
	bool Equals(const WPJSize &rhs) const;

	WPJSize &operator= (const WPJSize &rhs);
	WPJSize &operator= (const WPJPoint &rhs);
	WPJSize operator+ (const WPJSize &rhs) const;
	WPJSize operator- (const WPJSize &rhs) const;
	WPJSize operator* (const WPJSize &rhs) const;
	WPJSize operator/ (const WPJSize &rhs) const;

	~WPJSize();
};

class WPJRect
{
public:
	WPJPoint origin;
	WPJSize size;

public:
	WPJRect();
	WPJRect(float x, float y, float width, float height);
	WPJRect(const WPJPoint& obOrigin, const WPJSize& obSize);
	WPJRect(const WPJRect& lhs);
	WPJRect operator= (const WPJRect& lhs);
	
	void SetRect(float x, float y, float width, float height);
	float GetMinX() const;
	float GetMaxX() const;
	float GetMinY() const;
	float GetMaxY() const;
	float GetMidX() const;
	float GetMidY() const;
	bool Equals(const WPJRect& lhs) const;
	bool ContainsPoint(const WPJPoint& point) const;
	bool IntersectRect(const WPJRect& rect) const;
};

#define _npoint(x,y) WPJPoint((float)(x),(float)(y))
#define _nsize(width,height) WPJSize((float)(width),(float)(height))
#define _nRect(x,y,width,height) WPJRect((float)(x),float(y),float(width),float(height))

static WPJPoint WPJPointZero = _npoint(0,0);
static WPJSize WPJSizeZero = _nsize(0,0);
static WPJRect WPJRectZero = _nRect(0,0,0,0);

NS_WPJ_END
#endif