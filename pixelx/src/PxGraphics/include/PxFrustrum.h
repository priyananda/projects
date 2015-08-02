#ifndef _PIXELX_FRUSTRUM_H
#define _PIXELX_FRUSTRUM_H

#include "..\..\PxPhysics\include\PxPlane.h"

enum PxFrustrumPlanes
{
	LEFT_PLANE=0,
	RIGHT_PLANE,
	TOP_PLANE,
	BOTTOM_PLANE,
	NEAR_PLANE,
	FAR_PLANE
};

enum PxFrustrumClassification
{
	OUTSIDE_FRUSTUM=0,
	IN_FRUSTUM
};

class PxBoundingBox;
class PxFrustrum
{
public:
	void Update();
	bool IsPointInside(const PxVector & point);
	bool IsBoundingBoxInside(const PxVector * vertices) const;
	bool IsBoundingBoxInside(const PxBoundingBox & ) const;
protected:
	PxPlane planes[6];
};

#endif

