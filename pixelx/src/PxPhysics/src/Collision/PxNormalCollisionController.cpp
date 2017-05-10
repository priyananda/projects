#include "PxNormalCollisionController.h"
#include "PxMath.h"
#include "../../PxGraphics/include/PxCamera.h"
#include "PxBoundingSphere.h"

vector<PxBoundingBox> mBoundingBoxes;
bool PxNormalCollisionController::Collide(PxCamera & camera)
{
	bool ret = false;
	int count = mBoundingBoxes.size();
	PxBoundingSphere & sphere = camera.boundingSphere;

	for(int i = 0 ; i < count ; ++i )
	{
		PxBoundingBox & bbox = mBoundingBoxes[i];
		for( int j = 0 ; j < 6 ; ++j )
		{
			PxPolygon poly = bbox[j];
			PxVector vNormal = poly.Normal;
			vNormal.Normalize();
			float distance = 0.0f;

			int classification = PxMath::ClassifySphere(
				sphere.centre,
				vNormal,
				poly[0],
				sphere.radius,
				distance
			);

			if(classification == eIntIntersects) 
			{
				PxVector vOffset = vNormal * distance;
				PxVector vIntersection = sphere.centre - vOffset;
				if(PxMath::InsidePolygon(vIntersection, poly))// ||
				//PxMath::EdgeSphereCollision(sphere.centre, poly, sphere.radius / 2))
				{
					if( bbox.Parent && ! bbox.Parent->IsCollidable() )
					{
						bbox.Parent->OnCollision();
						return false;
					}
					vOffset = PxMath::GetCollisionOffset(vNormal, sphere.radius, distance);
					sphere.centre = sphere.centre + vOffset;
					ret = true;
				}
			}
		}
	}
	return ret;
}
bool PxNormalCollisionController::IsOnGround()
{
	return true;
}

void PxNormalCollisionController::Register( PxSolidObject * pS )
{
	mBoundingBoxes.push_back( pS->GetBoundingBox() );
}
void PxNormalCollisionController::Register( PxBoundingBox & bBox )
{
	mBoundingBoxes.push_back( bBox );
}
bool PxNormalCollisionController::Collides(const PxVector & lineStart,PxVector & lineEnd, float radius )
{
	int count = mBoundingBoxes.size();
	
	for( int i = 0; i < count ; ++i )
	{
		PxBoundingBox & bbox = mBoundingBoxes[i];
		if( bbox.Parent && ! bbox.Parent->IsCollidable() )
			continue;
		for( int j = 0 ; j < 6 ; ++j )
		{
			if( PxMath::IntersectedPolygon( bbox[j] , lineStart , lineEnd  ))
			{
				if( bbox.Parent )
					bbox.Parent->OnCollision();
				return true;
			}
		}
	}
	return false;
}

