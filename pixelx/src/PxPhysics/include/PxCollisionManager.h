#ifndef _PIXELX_COLLMANAGER_H
#define _PIXELX_COLLMANAGER_H

#include "PxSolidObject.h"

#include <list>
using std::list;

struct PxQuakeMap;
class PxCamera;
class PxBoundingSphere;

class PxCollisionManager
{
	
public:
	static void Register( PxSolidObject * pS );
	static void Register( PxBoundingBox & bBox );
	static bool Collides( PxCamera & camera );
	static bool Collides(const PxVector & lineStart,PxVector & lineEnd , float radius = 0);
	static bool IsOnGround( PxCamera & camera );
	static void Render();
private:
	static bool CollideBSP(PxBoundingSphere & sphere);
	static bool CollideNormal(PxBoundingSphere & sphere);
public:
	static void Register(PxQuakeMap * p);
};
#endif

