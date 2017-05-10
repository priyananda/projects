#ifndef _PIXELX_NORMALCOLLISIONCONTROLLER_H
#define _PIXELX_NORMALCOLLISIONCONTROLLER_H

#include "ICollisionController.h"
#include "../../PxGraphics/include/PxIndexedPolygonSet.h"
#include "../../PxGraphics/include/PxBoundingBox.h"
#include "PxSolidObject.h"

class PxNormalCollisionController
{
	PxIndexedPolygonSet mPolySet;
public:
	virtual bool Collide(PxCamera & );
	virtual bool IsOnGround();

	void Register( PxSolidObject * pS );
	void Register( PxBoundingBox & bBox );
	bool Collides(const PxVector & lineStart,PxVector & lineEnd,float radius = 0 );
};
#endif

