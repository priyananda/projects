#ifndef _PIXELX_VECTOR_H
#define _PIXELX_VECTOR_H
#include "Common.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265
#endif

//This is the basic Point/Vector class
class PxVector
{
public:
	PxVector(float X = 0 , float Y = 0 , float Z = 0 );
	PxVector operator+(const PxVector & vVector) const;
	PxVector operator-(const PxVector & vVector) const;
	PxVector operator*(float num) const;
	PxVector operator/(float num) const;
	bool operator==(const PxVector & v ) const;

	PxVector operator-() const;
	float GetSquaredLength() const;
    float Magnitude() const;
	void Normalize();

	float x, y, z;

	static PxVector Cross(const PxVector & vVector1,const PxVector & vVector2);
	static float Distance(const PxVector & , const PxVector & );
	static float Dot(const PxVector & vVector1,const PxVector & vVector2);

	void RotateX(double angle);
	PxVector GetRotatedX(double angle) const;
	void RotateY(double angle);
	PxVector GetRotatedY(double angle) const;
	void RotateZ(double angle);
	PxVector GetRotatedZ(double angle) const;
	void RotateAxis(double angle, const PxVector & axis);
	PxVector GetRotatedAxis(double angle, const PxVector & axis) const;

	PxVector LinearInterpolate(const PxVector & v2, float factor) const
	{	
		return (*this)*(1.0f-factor) + v2*factor;
	}

	PxVector QuadraticInterpolate(const PxVector & v2, const PxVector & v3, float factor) const
	{	
		return (*this)*(1.0f-factor)*(1.0f-factor) + v2*factor*(1.0f-factor)*2 + v3*factor*factor;
	}
};


#endif

