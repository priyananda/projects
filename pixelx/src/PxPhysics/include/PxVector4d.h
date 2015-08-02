//////////////////////////////////////////////////////////////////////////////////////////
//	PxVector4d.h
//	Class declaration for a 4d vector
//	You may use this code however you wish, but if you do, please credit me and
//	provide a link to my website in a readme file or similar
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//	Modified:	8th November 2002	-	Changed Constructor layout
//									-	Some speed Improvements
//									-	Corrected Lerp
//				7th January 2003	-	Added QuadraticInterpolate
//////////////////////////////////////////////////////////////////////////////////////////	

#ifndef _PIXELX_VECTOR4D_H
#define _PIXELX_VECTOR4D_H

#include "PxVector.h"

class PxVector4d
{
public:
	//constructors
	PxVector4d(void)	:	x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{}

	PxVector4d(float newX, float newY, float newZ, float newW)	
		:	x(newX), y(newY), z(newZ), w(newW)
	{}

	PxVector4d(const float * rhs)	:	x(*rhs), y(*(rhs+1)), z(*(rhs+2)), w(*(rhs+3))
	{}

	PxVector4d(const PxVector4d & rhs):	x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w)
	{}

	//convert v3d to v4d
	PxVector4d(const PxVector & rhs):	x(rhs.x), y(rhs.y), z(rhs.z), w(1.0f)
	{}

	~PxVector4d() {}	//empty

	void Set(float newX, float newY, float newZ, float newW)
	{	x=newX;	y=newY;	z=newZ; w=newW;	}
	
	//accessors kept for compatability
	void SetX(float newX) {x = newX;}
	void SetY(float newY) {y = newY;}
	void SetZ(float newZ) {z = newZ;}
	void SetW(float newW) {w = newW;}
	
	float GetX() const {return x;}	//public accessor functions
	float GetY() const {return y;}	//inline, const
	float GetZ() const {return z;}
	float GetW() const {return w;}

	void LoadZero(void)
	{	x=0.0f; y=0.0f; z=0.0f; w=0.0f;	}

	void LoadOne(void)
	{	x=1.0f; y=1.0f; z=1.0f; w=1.0f;	}

	//vector algebra
	float DotProduct(const PxVector4d & rhs)
	{	return x*rhs.x + y*rhs.y + z*rhs.z + w*rhs.w;	}

	//rotations
	void RotateX(double angle);
	PxVector4d GetRotatedX(double angle) const;
	void RotateY(double angle);
	PxVector4d GetRotatedY(double angle) const;
	void RotateZ(double angle);
	PxVector4d GetRotatedZ(double angle) const;
	void RotateAxis(double angle, const PxVector & axis);
	PxVector4d GetRotatedAxis(double angle, const PxVector & axis) const;
	
	PxVector4d lerp(const PxVector4d & v2, float factor) const
	{	return (*this)*(1.0f-factor)+v2*factor;	}

	PxVector4d QuadraticInterpolate(const PxVector4d & v2, const PxVector4d & v3, float factor) const
	{	return (*this)*(1.0f-factor)*(1.0f-factor) + 2*v2*factor*(1.0f-factor) + v3*factor*factor;}

	//binary operators
	PxVector4d operator+(const PxVector4d & rhs) const
	{	return PxVector4d(x+rhs.x, y+rhs.y, z+rhs.z, w+rhs.w);	}

	PxVector4d operator-(const PxVector4d & rhs) const
	{	return PxVector4d(x-rhs.x, y-rhs.y, z-rhs.z, w-rhs.w);	}

	PxVector4d operator*(const float rhs) const
	{	return PxVector4d(x*rhs, y*rhs, z*rhs, w*rhs);	}

	PxVector4d operator/(const float rhs) const
	{	return rhs==0.0f	?	PxVector4d(0.0f, 0.0f, 0.0f, 0.0f)
							:	PxVector4d(x/rhs, y/rhs, z/rhs, w/rhs);	}

	//multiply by a float, eg 3*v
	friend PxVector4d operator*(float scaleFactor, const PxVector4d & rhs);

	bool operator==(const PxVector4d & rhs) const;
	bool operator!=(const PxVector4d & rhs) const
	{	return !((*this)==rhs);	}

	//self-add etc
	void operator+=(const PxVector4d & rhs)
	{	x+=rhs.x; y+=rhs.y; z+=rhs.z; w+=rhs.w;	}

	void operator-=(const PxVector4d & rhs)
	{	x-=rhs.x; y-=rhs.y; z-=rhs.z; w-=rhs.w;	}

	void operator*=(const float rhs)
	{	x*=rhs; y*=rhs; z*=rhs; w*=rhs;	}

	void operator/=(const float rhs)
	{	if(rhs==0.0f)
			return;
		else
		{	x/=rhs; y/=rhs; z/=rhs; w/=rhs;	}
	}

	//unary operators
	PxVector4d operator-(void) const {return PxVector4d(-x, -y, -z, -w);}
	PxVector4d operator+(void) const {return (*this);}

	//cast to pointer to float for glVertex4fv etc
	operator float* () const {return (float*) this;}
	operator const float* () const {return (const float*) this;}

	operator PxVector();							//convert v4d to v3d

	//member variables
	float x;
	float y;
	float z;
	float w;
};

#endif	//PxVector_H

