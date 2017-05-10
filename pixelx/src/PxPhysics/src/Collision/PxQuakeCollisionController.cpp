#include "PxQuakeCollisionController.h"
#include "PxMath.h"
#include "../../PxGraphics/include/PxCamera.h"
#include "PxBoundingSphere.h"

PxBitSet collidableFaces;

#define BSP_EPSILON 0.003125f
#define BSP_MAXSTEPS 2.0f

PxQuakeCollisionController::PxQuakeCollisionController( PxQuakeMap * pMap )
{
	mMap = pMap;
}
bool PxQuakeCollisionController::IsInside(const PxVector & point)
{
	return mMap->boundingBox.Contains(point.x,point.y,point.z);
}
bool PxQuakeCollisionController::IsOnGround()
{
	return mIsGrounded;
}

bool PxQuakeCollisionController::Collides(const PxVector & lineStart,PxVector & lineEnd, float radius )
{
	mIsCollided = false;
	bool _mIsGrounded = mIsGrounded;
	mIsGrounded = false;
	mHieghtAdjust = false;
	mTraceRadius = radius;
	PxVector newPosition = Trace( lineStart , lineEnd );
	mIsGrounded = _mIsGrounded;
	lineEnd = newPosition;
	return mIsCollided;
}

bool PxQuakeCollisionController::Collide( PxCamera & camera )
{
	mIsCollided = false;
	mIsGrounded = false;
	mHieghtAdjust = false;
	mTraceRadius = camera.boundingSphere.radius;
	PxVector currentPosition = camera.boundingSphere.centre;
	PxVector oldPosition = camera.OldPosition();
	PxVector newPosition = Trace( oldPosition , currentPosition );
	PxVector adjPosition = newPosition;
	
	if( mIsCollided && mHieghtAdjust )
		adjPosition = AdjustHieght( newPosition , currentPosition );

	camera.boundingSphere.centre = adjPosition;

	return mIsCollided;
}

PxVector PxQuakeCollisionController::Trace(const PxVector & start ,const PxVector & end)
{
	mTraceRatio	= 1.0f;
	CheckNode(0, 0.0f, 1.0f, start, end);

	if( mTraceRatio == 1.0f )
		return end;
	
	PxVector newPos = start + ( end - start ) * mTraceRatio;
	PxVector move = end - newPos;
	float distance = PxVector::Dot( move , mCollisionNormal );
	PxVector endPos = end - mCollisionNormal * distance;
	newPos = Trace( newPos , endPos );
	
	if( mCollisionNormal.y >= 0.2f || mIsGrounded )
		mIsGrounded = true;
	else
		mIsGrounded = false;
	return newPos;
}

void PxQuakeCollisionController::CheckNode( int nodeIndex, float startRatio, float endRatio,const PxVector & startPos,const PxVector & endPos )
{
	if( nodeIndex < 0 )
	{
		PxBSPLeaf * leaf = &mMap->leaves[-(nodeIndex + 1)];
		for( int i = 0 ; i < leaf->numBrushes; ++i )
		{
			PxBSPBrush * brush = &mMap->brushes[ mMap->leafBrushes[leaf->firstLeafBrush + i] ];
			if( (brush->numOfBrushSides > 0) && mMap->isTextureSolid[ brush->textureID ] )
			{
				CheckBrush(brush,startPos,endPos);
			}
		}
		return;
	}
	PxBSPNode * node = &mMap->nodes[nodeIndex];
	PxPlane * plane = &mMap->planes[node->planeIndex];
	float startDistance = PxVector::Dot( startPos, plane->normal ) - plane->intercept;
	float endDistance = PxVector::Dot( endPos, plane->normal ) - plane->intercept;
	if( startDistance >= mTraceRadius && endDistance >= mTraceRadius )
	{
		CheckNode(node->front, startRatio ,endRatio,startPos, endPos);
	}
	else if(startDistance < -mTraceRadius && endDistance < -mTraceRadius)
	{
		CheckNode(node->back, startRatio,endRatio,startPos, endPos);
	}
	else
	{
		float ratio1 = 1, ratio2 = 0,middleRatio =0;
		int side = node->front;

		if( startDistance < endDistance )
		{
			side = node->back;

			float inverseDistance = 1.0f / ( startDistance - endDistance );
			ratio1 = ( startDistance - mTraceRadius + BSP_EPSILON ) * inverseDistance;
			ratio2 = ( startDistance + mTraceRadius + BSP_EPSILON ) * inverseDistance;
		}
		else if( startDistance > endDistance )
		{
			float inverseDistance = 1.0f / (startDistance - endDistance);
			ratio1 = ( startDistance + mTraceRadius + BSP_EPSILON ) * inverseDistance;
			ratio2 = ( startDistance - mTraceRadius - BSP_EPSILON ) * inverseDistance;
		}

		if( ratio1 < 0.0f ) ratio1 = 0.0f;
		if( ratio2 < 0.0f ) ratio2 = 0.0f;
		if( ratio1 > 1.0f ) ratio1 = 1.0f;
		if( ratio2 > 1.0f ) ratio2 = 1.0f;

		middleRatio = startRatio + (( endRatio - startRatio) * ratio1 );
		PxVector middle = startPos + ( (endPos - startPos) * ratio1 );

		CheckNode(side, startRatio, middleRatio, startPos , middle );

		middleRatio = startRatio + ((endRatio - startRatio) * ratio2);
		middle = startPos + ((endPos - startPos) * ratio2);

		if(side == node->back)
			CheckNode(node->front, middleRatio, endRatio, middle, endPos);
		else
			CheckNode(node->back, middleRatio, endRatio, middle, endPos);
	}
}

void PxQuakeCollisionController::CheckBrush( PxBSPBrush * brush, const PxVector & startPos , const PxVector & endPos )
{
	float startRatio = -1.0f;
    float endRatio = 1.0f;
    bool startsOut = false;

	for( int i = 0 ; i < brush->numOfBrushSides ; ++i )
	{
		PxBSPBrushSide * brushSide = & mMap->brushSides[ brush->brushSide + i ];
		PxPlane * plane = & mMap->planes [ brushSide->Plane ];

		//plane->normal.Normalize();
		float startDistance = PxVector::Dot( startPos , plane->normal ) - (mTraceRadius + plane->intercept);
		float endDistance = PxVector::Dot( endPos , plane->normal ) - (mTraceRadius + plane->intercept);

		if( startDistance > 0 )
			startsOut = true;

		if( startDistance > 0 && endDistance > 0 )
			return;

		if( startDistance <= 0 && endDistance <= 0 )
			continue;
		
		if( startDistance > endDistance )
		{
			float ratio1 = ( startDistance - BSP_EPSILON ) / (startDistance - endDistance);

			if( ratio1 > startRatio )
			{
				startRatio = ratio1;
				mIsCollided = true;
				mCollisionNormal = plane->normal;

				if( ( startPos.x != endPos.x || startPos.z != endPos.z) && plane->normal.y != 1.0f )
					this->mHieghtAdjust = true;

				if( mCollisionNormal.y >= 0.2f )
					mIsGrounded = true;
			}
		}
		else
		{
			float ratio = ( startDistance + BSP_EPSILON ) / ( startDistance - endDistance );
			if( ratio < endRatio )
				endRatio = ratio;
		}

		if( ! startsOut )
			return;

		if( startRatio < endRatio )
		{
			if( startRatio > -1 && startRatio < mTraceRatio )
			{
				if( startRatio < 0 ) startRatio = 0;
				mTraceRatio = startRatio;
			}
		}
	}
}

PxVector PxQuakeCollisionController::AdjustHieght( const PxVector & startPos , const PxVector & endPos )
{
	for( float height = 0.2f ; height <= BSP_MAXSTEPS ; height += 0.2f )
	{
		mIsCollided = false;
		mHieghtAdjust = false;

		PxVector start( startPos.x, startPos.y + height, startPos.z);
		PxVector end( endPos.x, endPos.y + height, endPos.z);

		PxVector newpos = Trace( start , end );

		if(! mIsCollided )
		{
			return newpos;
		}
	}
	return startPos;
}

