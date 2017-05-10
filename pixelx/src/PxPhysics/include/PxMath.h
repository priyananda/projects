#ifndef _PIXELX_MATH_H
#define _PIXELX_MATH_H

#include "PxVector.h"
#include "../../PxGraphics/include/PxPolygon.h"
#include "../../PxGraphics/include/PxQuakeMap.h"

enum PxIntersectionEnum
{
	eIntBehind,
	eIntIntersects,
	eIntFront
};

class PxMath
{
public:
	static PxVector ClosestPointOnLine(const PxVector & lineStart, const PxVector & lineEnd, const PxVector & vPoint);
	static float PlaneDistance( const PxVector & normal,const PxVector & point );
	static bool IntersectedPlane(
		const PxPolygon &poly,
		const PxVector  &lineStart,
		const PxVector  &lineEn,
		PxVector & vNormal,
		float & originDistance);
	static double AngleBetweenVectors( const PxVector &, const PxVector &);
	static PxVector IntersectionPoint(
		const PxVector & vNormal,
		const PxVector & lineStart,
		const PxVector & lineEnd,
		double distance);
	static bool InsidePolygon(
		const PxVector & vIntersection,
		const PxPolygon & poly
	);
	static bool InsidePolygon(
		const PxVector & vIntersection,
		const PxBSPPolygonFace & poly,
		PxQuakeMap * map
	);
	static bool IntersectedPolygon(
		const PxPolygon & vPoly,
		const PxVector & lineStart,
		const PxVector & lineEnd
	);
	static bool EdgeSphereCollision(
		const PxVector &vCenter, 
		const PxPolygon &vPolygon,
		float radius
	);
	static int ClassifySphere(
		const PxVector &vCenter, 
		const PxVector &vNormal,
		const PxVector &vPoint,
		float radius,
		float &distance
	);
	static bool SpherePolygonCollision(
		const PxPolygon &vPolygon,
		const PxVector &vCenter,
		float radius);
	static PxVector GetCollisionOffset(
		const PxVector &vNormal,
		float radius,
		float distance
	);
};

#endif

