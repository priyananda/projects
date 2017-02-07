#ifndef _PIXELX_QUAKECOLLISIONCONTROLLER_H
#define _PIXELX_QUAKECOLLISIONCONTROLLER_H

#include "ICollisionController.h"
#include "../../PxGraphics/include/PxQuakeMap.h"

class PxQuakeCollisionController
{
	PxQuakeMap * mMap;
	bool mIsCollided;
	bool mIsGrounded;
	bool mHieghtAdjust;
	float mTraceRatio;
	float mTraceRadius;
	PxVector mCollisionNormal;

	PxVector Trace(const PxVector & ,const PxVector & );
	PxVector AdjustHieght(const PxVector & ,const PxVector & );
	void CheckNode( int nodeIndex, float startRatio, float endRatio,const PxVector & startPos,const PxVector & endPos );
	void CheckBrush( PxBSPBrush * brush, const PxVector & , const PxVector &);
public:
	PxQuakeCollisionController( PxQuakeMap * pMap );
	virtual ~PxQuakeCollisionController() = default;
	bool IsInside(const PxVector & point);

	virtual bool Collide(PxCamera & );
	virtual bool Collides(const PxVector & lineStart,PxVector & lineEnd, float radius = 0);
	virtual bool IsOnGround();
};
#endif

