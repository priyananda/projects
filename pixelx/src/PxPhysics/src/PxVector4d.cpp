//////////////////////////////////////////////////////////////////////////////////////////
//	PxVector4d.cpp
//	Function definitions for 4d vector class
//	You may use this code however you wish, but if you do, please credit me and
//	provide a link to my website in a readme file or similar
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//	Modified:	15th August 2002	-	prevent divide by zero in operator PxVector()
//	Modified:	8th November 2002	-	Changed Constructor layout
//									-	Some speed Improvements
//									-	Corrected Lerp
//////////////////////////////////////////////////////////////////////////////////////////	

#include "PxVector4d.h"

void PxVector4d::RotateX(double angle)
{
	(*this)=GetRotatedX(angle);
}

PxVector4d PxVector4d::GetRotatedX(double angle) const
{
	PxVector v3d(x, y, z);

	v3d.RotateX(angle);

	return PxVector4d(v3d.x, v3d.y, v3d.z, w);
}

void PxVector4d::RotateY(double angle)
{
	(*this)=GetRotatedY(angle);
}

PxVector4d PxVector4d::GetRotatedY(double angle) const
{
	PxVector v3d(x, y, z);

	v3d.RotateY(angle);

	return PxVector4d(v3d.x, v3d.y, v3d.z, w);
}

void PxVector4d::RotateZ(double angle)
{
	(*this)=GetRotatedZ(angle);
}

PxVector4d PxVector4d::GetRotatedZ(double angle) const
{
	PxVector v3d(x, y, z);

	v3d.RotateZ(angle);

	return PxVector4d(v3d.x, v3d.y, v3d.z, w);
}

void PxVector4d::RotateAxis(double angle, const PxVector & axis)
{
	(*this)=GetRotatedAxis(angle, axis);
}

PxVector4d PxVector4d::GetRotatedAxis(double angle, const PxVector & axis) const
{
	PxVector v3d(x, y, z);

	v3d.RotateAxis(angle, axis);

	return PxVector4d(v3d.x, v3d.y, v3d.z, w);
}


PxVector4d operator*(float scaleFactor, const PxVector4d & rhs)
{
	return rhs*scaleFactor;
}

bool PxVector4d::operator==(const PxVector4d & rhs) const
{
	if(x==rhs.x && y==rhs.y && z==rhs.z && w==rhs.w)
		return true;

	return false;
}

PxVector4d::operator PxVector()
{
	if(w==0.0f || w==1.0f)
		return PxVector(x, y, z);
	else
		return PxVector(x/w, y/w, z/w);
}

