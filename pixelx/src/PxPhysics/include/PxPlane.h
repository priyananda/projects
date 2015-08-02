#ifndef _PIXELX_PLANE_H
#define _PIXELX_PLANE_H

#include "PxVector.h"

#define EPSILON 0.01f
class PxPlane
{
public:
	PxPlane()	:	normal(PxVector(0.0f, 0.0f, 0.0f)), intercept(0.0f)
	{}
	PxPlane(PxVector newNormal, float newIntercept)	: normal(newNormal), intercept(newIntercept)
	{}
	PxPlane(const PxPlane & rhs)
	{	normal=rhs.normal;	intercept=rhs.intercept;	}

	~PxPlane() {}
	
	void SetNormal(const PxVector & rhs) { normal=rhs; }
	void SetIntercept(float newIntercept) { intercept=newIntercept; }
	void SetFromPoints(const PxVector & p0, const PxVector & p1, const PxVector & p2);

	void CalculateIntercept(const PxVector & pointOnPlane) { intercept=-PxVector::Dot( normal,pointOnPlane ); }
	
	void Normalize(void);

	PxVector GetNormal()
	{
		//normal.Normalize();
		return normal;
	}
	float GetIntercept() { return intercept; }
	
	//find point of intersection of 3 planes
	bool Intersect3(const PxPlane & p2, const PxPlane & p3, PxVector & result);

	float GetDistance(const PxVector & point) const;
	int ClassifyPoint(const PxVector & point) const;
	
	PxPlane lerp(const PxPlane & p2, float factor);

	//operators
	bool operator==(const PxPlane & rhs) const;
	bool operator!=(const PxPlane & rhs) const
	{		return!((*this)==rhs);	}

	//unary operators
	PxPlane operator-(void) const {return PxPlane(-normal, -intercept);}
	PxPlane operator+(void) const {return (*this);}

	//member variables
	PxVector normal;	//X.N+intercept=0
	float intercept;
};

//constants for ClassifyPoint()
const int POINT_ON_PLANE=0;
const int POINT_IN_FRONT_OF_PLANE=1;
const int POINT_BEHIND_PLANE=2;

#endif

