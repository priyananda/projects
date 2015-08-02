#ifndef _PIXELX_BOUNDINGSPEHERE_H
#define _PIXELX_BOUNDINGSPEHERE_H

#include "PxVector.h"

class PxBoundingBox;
class PxPlane;

class PxBoundingSphere
{
public:
	void Set(const PxVector & newCentre, const float newRadius);

	bool IsPointInside(const PxVector & point) const;
	bool IsAABoundingBoxInside(const PxBoundingBox & box) const;
	bool IsBoundingSphereInside(const PxBoundingSphere & sphere) const;
	virtual bool IsPolygonInside(const PxPlane & planeEquation, int numVertices, const PxVector * vertices) const;

	PxVector centre;
	float radius;
};

#endif

