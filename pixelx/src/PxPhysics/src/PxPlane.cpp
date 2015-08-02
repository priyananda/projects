#include "PxPlane.h"


void PxPlane::SetFromPoints(const PxVector & p0, const PxVector & p1, const PxVector & p2)
{
	normal= PxVector::Cross( (p1-p0),(p2-p0) );

	CalculateIntercept(p0);
}

void PxPlane::Normalize()
{
	float normalLength=normal.Magnitude();
	normal= normal/normalLength;
	intercept = intercept/normalLength;
}

bool PxPlane::Intersect3(const PxPlane & p2, const PxPlane & p3, PxVector & result)//find point of intersection of 3 planes
{
	float denominator= PxVector::Dot(
			normal,
			PxVector::Cross( p2.normal ,p3.normal)
		);
	if(denominator==0.0f)									//if zero
		return false;										//no intersection

	PxVector temp1, temp2, temp3;
	temp1=(PxVector::Cross(p2.normal,p3.normal))*intercept;
	temp2=(PxVector::Cross(p3.normal,normal))*p2.intercept;
	temp3=(PxVector::Cross(normal,p2.normal))*p3.intercept;

	result=(temp1+temp2+temp3)/(denominator);

	return true;
}

float PxPlane::GetDistance(const PxVector & point) const
{
	return point.x*normal.x + point.y*normal.y + point.z*normal.z - intercept;
}

int PxPlane::ClassifyPoint(const PxVector & point) const
{
	float distance=point.x*normal.x + point.y*normal.y + point.z*normal.z - intercept;

	if(distance>EPSILON)	//==0.0f is too exact, give a bit of room
		return POINT_IN_FRONT_OF_PLANE;
	
	if(distance<-EPSILON)
		return POINT_BEHIND_PLANE;

	return POINT_ON_PLANE;	//otherwise
}

PxPlane PxPlane::lerp(const PxPlane & p2, float factor)
{
	PxPlane result;
	result.normal=normal*(1.0f-factor) + p2.normal*factor;
	result.normal.Normalize();

	result.intercept = intercept*(1.0f-factor) + p2.intercept*factor;

	return result;
}

bool PxPlane::operator ==(const PxPlane & rhs) const
{
	if(normal==rhs.normal && intercept==rhs.intercept)
		return true;

	return false;
}

