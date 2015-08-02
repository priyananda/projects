#include "PxMath.h"
#include <cmath>
#include <cfloat>

PxVector PxMath::ClosestPointOnLine(
	const PxVector & lineStart,
	const PxVector & lineEnd,
	const PxVector & vPoint)
{
	PxVector vVector1 = vPoint - lineStart;
    PxVector vVector2 = lineEnd - lineStart;
	vVector2.Normalize();
	float d = PxVector::Distance(lineStart, lineEnd);
	float t = PxVector::Dot(vVector2, vVector1);
    if (t <= 0)
		return lineStart;
    if (t >= d) 
		return lineEnd;
    PxVector vVector3 = vVector2 * t;
    PxVector vClosestPoint = lineStart + vVector3;
	return vClosestPoint;
}
float PxMath::PlaneDistance(const PxVector & Normal,const PxVector& Point)
{	
	return - ((Normal.x * Point.x) + (Normal.y * Point.y) + (Normal.z * Point.z));
}

bool PxMath::IntersectedPlane(
	const PxPolygon & vPoly,
	const PxVector & lineStart,
	const PxVector & lineEnd,
	PxVector & vNormal,//out
	float & originDistance)
{
	float distance1=0, distance2=0;						// The distances from the 2 points of the line from the PxVector
	vNormal = vPoly.Normal;							// We need to get the normal of our PxVector to go any further
	vNormal.Normalize();
	// Let's find the distance our PxVector is from the origin.  We can find this value
	// from the normal to the PxVector (polygon) and any point that lies on that PxVector (Any vertex)
	PxVector v0 = vPoly[0];
	originDistance = PlaneDistance(vNormal, v0 );
	// Get the distance from point1 from the PxVector using: Ax + By + Cz + D = (The distance from the PxVector)
	distance1 = ((vNormal.x * lineStart.x)  +					// Ax +
		         (vNormal.y * lineStart.y)  +					// Bx +
				 (vNormal.z * lineStart.z)) + originDistance;	// Cz + D
	// Get the distance from point2 from the PxVector using Ax + By + Cz + D = (The distance from the PxVector)
	distance2 = ((vNormal.x * lineEnd.x)  +					// Ax +
		         (vNormal.y * lineEnd.y)  +					// Bx +
				 (vNormal.z * lineEnd.z)) + originDistance;	// Cz + D
	// Now that we have 2 distances from the PxVector, if we times them together we either
	// get a positive or negative number.  If it's a negative number, that means we collided!
	// This is because the 2 points must be on either side of the PxVector (IE. -1 * 1 = -1).
	if(distance1 * distance2 >= 0)			// Check to see if both point's distances are both negative or both positive
	   return false;						// Return false if each point has the same sign.  -1 and 1 would mean each point is on either side of the PxVector.  -1 -2 or 3 4 wouldn't...
	return true;							// The line intersected the PxVector, Return TRUE
}

double PxMath::AngleBetweenVectors( const PxVector & Vector1,const PxVector & Vector2)
{							
	// Get the dot product of the vectors
	float dotProduct = PxVector::Dot(Vector1, Vector2);				

	// Get the product of both of the vectors magnitudes
	float vectorsMagnitude = Vector1.Magnitude() * Vector2.Magnitude() ;

	// Get the angle in radians between the 2 vectors
	double angle = acos( dotProduct / vectorsMagnitude );

	// Here we make sure that the angle is not a -1.#IND0000000 number, which means indefinate
	if(_isnan(angle))
		return 0;
	
	// Return the angle in radians
	return( angle );
}

PxVector PxMath::IntersectionPoint(
	const PxVector & vNormal,
	const PxVector & lineStart,
	const PxVector & lineEnd,
	double distance)
{
	PxVector vPoint, vLineDir;					// Variables to hold the point and the line's direction
	double Numerator = 0.0, Denominator = 0.0, dist = 0.0;

	// 1)  First we need to get the vector of our line, Then normalize it so it's a length of 1
	vLineDir = lineEnd - lineStart;		// Get the Vector of the line
	vLineDir.Normalize();				// Normalize the lines vector


	// 2) Use the PxVector equation (distance = Ax + By + Cz + D) to find the 
	// distance from one of our points to the PxVector.
	Numerator = - (vNormal.x * lineStart.x +		// Use the PxVector equation with the normal and the line
				   vNormal.y * lineStart.y +
				   vNormal.z * lineStart.z + distance);

	// 3) If we take the dot product between our line vector and the normal of the polygon,
	Denominator = PxVector::Dot(vNormal, vLineDir);		// Get the dot product of the line's vector and the normal of the PxVector
				  
	// Since we are using division, we need to make sure we don't get a divide by zero error
	// If we do get a 0, that means that there are INFINATE points because the the line is
	// on the PxVector (the normal is perpendicular to the line - (Normal.Vector = 0)).  
	// In this case, we should just return any point on the line.

	if( Denominator == 0.0)						// Check so we don't divide by zero
		return lineStart;						// Return an arbitrary point on the line

	dist = Numerator / Denominator;				// Divide to get the multiplying (percentage) factor
	
	// Now, like we said above, we times the dist by the vector, then add our arbitrary point.
	vPoint.x = (float)(lineStart.x + (vLineDir.x * dist));
	vPoint.y = (float)(lineStart.y + (vLineDir.y * dist));
	vPoint.z = (float)(lineStart.z + (vLineDir.z * dist));

	return vPoint;								// Return the intersection point
}
#define PI 3.14159f

bool PxMath::InsidePolygon(
	const PxVector & vIntersection,
	const PxBSPPolygonFace & poly,
	PxQuakeMap * map
)
{
	const double MATCH_FACTOR = 0.99;
	double Angle = 0.0;
	PxVector vA, vB;
	
	for (int i = 0; i < poly.numVertices ; i++)
	{	
		vA = map->vertices[poly.firstVertexIndex + i].position - vIntersection;
		vB = map->vertices[poly.firstVertexIndex + (i + 1) % poly.numVertices].position - vIntersection;
		Angle += AngleBetweenVectors(vA, vB);
	}
	if(Angle >= (MATCH_FACTOR * (2.0 * PI)) )
		return true;
	return false;
}


bool PxMath::InsidePolygon(
	const PxVector & vIntersection,
	const PxPolygon & poly
)
{
	const double MATCH_FACTOR = 0.99;		// Used to cover up the error in floating point
	double Angle = 0.0;						// Initialize the angle
	PxVector vA, vB;						// Create temp vectors
	int verticeCount = poly.GetVertexCount();
	
	for (int i = 0; i < verticeCount; i++)	// Go in a circle to each vertex and get the angle between
	{	
		vA = poly[i] - vIntersection;			// Subtract the intersection point from the current vertex
												// Subtract the point from the next vertex
		vB = poly[(i + 1) % verticeCount] - vIntersection;
												
		Angle += AngleBetweenVectors(vA, vB);	// Find the angle between the 2 vectors and add them all up as we go along
	}
											
	if(Angle >= (MATCH_FACTOR * (2.0 * PI)) )	// If the angle is greater than 2 PI, (360 degrees)
		return true;							// The point is inside of the polygon
		
	return false;								// If you get here, it obviously wasn't inside the polygon, so Return FALSE
}



bool PxMath::IntersectedPolygon(
	const PxPolygon & vPoly,
	const PxVector & lineStart,
	const PxVector & lineEnd
)
{
	PxVector vNormal;
	float originDistance = 0;

	// First, make sure our line intersects the PxVector
									 // Reference   // Reference
	if(!IntersectedPlane(vPoly, lineStart, lineEnd, vNormal, originDistance))
		return false;

	// Now that we have our normal and distance passed back from IntersectedPlane(), 
	// we can use it to calculate the intersection point.  
	PxVector vIntersection = IntersectionPoint(vNormal, lineStart,lineEnd, originDistance);

	// Now that we have the intersection point, we need to test if it's inside the polygon.
	if(InsidePolygon(vIntersection, vPoly))
		return true;							// We collided!	  Return success

	return false;								// There was no collision, so return false
}

int PxMath::ClassifySphere(
	const PxVector &vCenter, 
	const PxVector &vNormal,
	const PxVector &vPoint,
	float radius,
	float &distance)
{
	// First we need to find the distance our polygon PxVector is from the origin.
	float d = (float)PlaneDistance(vNormal, vPoint);

	// Here we use the famous distance formula to find the distance the center point
	// of the sphere is from the polygon's PxVector.  
	distance = (vNormal.x * vCenter.x + vNormal.y * vCenter.y + vNormal.z * vCenter.z + d);

	// If the absolute value of the distance we just found is less than the radius, 
	// the sphere intersected the PxVector.
	if(fabs(distance) < radius)
		return eIntIntersects;
	// Else, if the distance is greater than or equal to the radius, the sphere is
	// completely in FRONT of the PxVector.
	else if(fabs(distance) >= radius)
		return eIntFront;
	
	// If the sphere isn't intersecting or in FRONT of the PxVector, it must be BEHIND
	return eIntBehind;
}

bool PxMath::EdgeSphereCollision(const PxVector &vCenter, 
						 const PxPolygon &vPolygon,
						 float radius)
{
	PxVector vPoint;

	// This function takes in the sphere's center, the polygon's vertices, the vertex count
	// and the radius of the sphere.  We will return true from this function if the sphere
	// is intersecting any of the edges of the polygon.  

	// Go through all of the vertices in the polygon
	int vertexCount = vPolygon.GetVertexCount();
	for(int i = 0; i < vertexCount; i++)
	{
		// This returns the closest point on the current edge to the center of the sphere.
		vPoint = ClosestPointOnLine(vPolygon[i], vPolygon[(i + 1) % vertexCount], vCenter);
		
		// Now, we want to calculate the distance between the closest point and the center
		float distance = PxVector::Distance(vPoint, vCenter);

		// If the distance is less than the radius, there must be a collision so return true
		if(distance < radius)
			return true;
	}

	return false;
}


/////	This returns true if our sphere collides with the polygon passed in
bool PxMath::SpherePolygonCollision(const PxPolygon &vPolygon,
							const PxVector &vCenter,
							float radius)
{
	// 1) STEP ONE - Finding the sphere's classification
	
	// Let's use our Normal() function to return us the normal to this polygon
	PxVector vNormal = vPolygon.Normal;

	// This will store the distance our sphere is from the PxVector
	float distance = 0.0f;

	// This is where we determine if the sphere is in FRONT, BEHIND, or INTERSECTS the PxVector
	int classification = ClassifySphere(vCenter, vNormal, vPolygon[0], radius, distance);

	// If the sphere intersects the polygon's PxVector, then we need to check further
	if(classification == eIntIntersects) 
	{
		// 2) STEP TWO - Finding the psuedo intersection point on the PxVector

		// Now we want to project the sphere's center onto the polygon's PxVector
		PxVector vOffset = vNormal * distance;

		// Once we have the offset to the PxVector, we just subtract it from the center
		// of the sphere.  "vPosition" now a point that lies on the PxVector of the polygon.
		PxVector vPosition = vCenter - vOffset;

		// 3) STEP THREE - Check if the intersection point is inside the polygons perimeter

		// If the intersection point is inside the perimeter of the polygon, it returns true.
		// We pass in the intersection point, the list of vertices and vertex count of the poly.
		if(InsidePolygon(vPosition, vPolygon))
			return true;	// We collided!
		else
		{
			// 4) STEP FOUR - Check the sphere intersects any of the polygon's edges

			// If we get here, we didn't find an intersection point in the perimeter.
			// We now need to check collision against the edges of the polygon.
			if(EdgeSphereCollision(vCenter, vPolygon, radius))
			{
				return true;	// We collided!
			}
		}
	}

	// If we get here, there is obviously no collision
	return false;
}

/////	This returns the offset to move the center of the sphere off the collided polygon
PxVector PxMath::GetCollisionOffset(
	const PxVector &vNormal,
	float radius,
	float distance
)
{
	PxVector vOffset = PxVector(0, 0, 0);

	// Once we find if a collision has taken place, we need make sure the sphere
	// doesn't move into the wall.  In our app, the position will actually move into
	// the wall, but we check our collision detection before we render the scene, which
	// eliminates the bounce back effect it would cause.  The question is, how do we
	// know which direction to move the sphere back?  In our collision detection, we
	// account for collisions on both sides of the polygon.  Usually, you just need
	// to worry about the side with the normal vector and positive distance.  If 
	// you don't want to back face cull and have 2 sided planes, I check for both sides.
	//
	// Let me explain the math that is going on here.  First, we have the normal to
	// the PxVector, the radius of the sphere, as well as the distance the center of the
	// sphere is from the PxVector.  In the case of the sphere colliding in the front of
	// the polygon, we can just subtract the distance from the radius, then multiply
	// that new distance by the normal of the PxVector.  This projects that leftover
	// distance along the normal vector.  For instance, say we have these values:
	//
	//	vNormal = (1, 0, 0)		radius = 5		distance = 3
	//
	// If we subtract the distance from the radius we get: (5 - 3 = 2)
	// The number 2 tells us that our sphere is over the PxVector by a distance of 2.
	// So basically, we need to move the sphere back 2 units.  How do we know which
	// direction though?  This part is easy, we have a normal vector that tells us the
	// direction of the PxVector.  
	// If we multiply the normal by the left over distance we get:  (2, 0, 0)
	// This new offset vectors tells us which direction and how much to move back.
	// We then subtract this offset from the sphere's position, giving is the new
	// position that is lying right on top of the PxVector.  Ba da bing!
	// If we are colliding from behind the polygon (not usual), we do the opposite
	// signs as seen below:
	
	// If our distance is greater than zero, we are in front of the polygon
	if(distance > 0)
	{
		// Find the distance that our sphere is overlapping the PxVector, then
		// find the direction vector to move our sphere.
		float distanceOver = radius - distance;
		vOffset = vNormal * distanceOver;
	}
	else // Else colliding from behind the polygon
	{
		// Find the distance that our sphere is overlapping the PxVector, then
		// find the direction vector to move our sphere.
		float distanceOver = radius + distance;
		vOffset = vNormal * -distanceOver;
	}

	// There is one problem with check for collisions behind the polygon, and that
	// is if you are moving really fast and your center goes past the front of the
	// polygon, it will then assume you were colliding from behind and not let
	// you back in.  Most likely you will take out the if / else check, but I
	// figured I would show both ways in case someone didn't want to back face cull.

	// Return the offset we need to move back to not be intersecting the polygon.
	return vOffset;
}

