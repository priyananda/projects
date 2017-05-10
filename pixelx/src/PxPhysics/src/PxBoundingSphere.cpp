#include "PxBoundingSphere.h"
#include "../../PxGraphics/include/PxBoundingBox.h"
#include "PxPlane.h"

void PxBoundingSphere::Set(const PxVector & newCentre, const float newRadius)
{
	centre = newCentre;
	radius = newRadius;
}

bool PxBoundingSphere::IsAABoundingBoxInside(const PxBoundingBox & box) const
{
	return false;
}

bool PxBoundingSphere::IsPointInside(const PxVector & point) const
{ 
	float squaredDistance = ( point - centre).GetSquaredLength();
	if( squaredDistance <= radius * radius )
		return true;
	return false;
}

bool PxBoundingSphere::IsBoundingSphereInside(const PxBoundingSphere & sphere) const
{
	float squaredDistance =( sphere.centre - centre ).GetSquaredLength();
	if( squaredDistance <= ( radius + sphere.radius )*( radius + sphere.radius ))
		return true;
	return false;
}

bool PxBoundingSphere::IsPolygonInside(	const PxPlane & plane,
										int numVertices,
										const PxVector * vertices) const
{
	float distance = plane.GetDistance(centre);
	if( distance > radius || distance < -radius)
		return false;
	PxVector projectedCentre = centre - plane.normal * distance;
	double angle = 0.0;
	int i;
	for(i = 0; i< numVertices; ++i)
	{
		const PxVector & vA = vertices[i]-projectedCentre;
		const PxVector & vB = vertices[(i+1) % numVertices]-projectedCentre;
		angle += acos(PxVector::Dot(vA,vB)/(vA.Magnitude() * vB.Magnitude()));
	}
	if(angle >= 1.99*M_PI)
		return true;
	
	for(i = 0; i < numVertices; ++i)
	{
		PxVector closestPoint;
		const PxVector & v1 = vertices[i];
		const PxVector & v2 = vertices[(i+1) % numVertices];
		float edgeLength=(v2-v1).Magnitude();
		PxVector edgeDirection=v2-v1;
		edgeDirection.Normalize();
		PxVector vertexToCentre=centre-v1;
		float t = PxVector::Dot( vertexToCentre,edgeDirection);
		if(t <= 0)
			closestPoint=v1;
		else if( t >= edgeLength)
			closestPoint=v2;
		else
			closestPoint=v1.LinearInterpolate(v2, t/edgeLength);
		if((closestPoint-centre).GetSquaredLength()<radius*radius)
			return true;
	}

	return false;
}

