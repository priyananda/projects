#ifndef _PIXELX_POiNTPROJECTILE
#define _PIXELX_POiNTPROJECTILE

#include "PxProjectile.h"

class PxPointProjectile : public PxProjectile
{
public:
	PxPointProjectile(  const PxVector & loc, const PxVector & dir , float speed )
		: PxProjectile(loc,dir,speed){}
	virtual void Render();
	virtual void HandleCollision();
};
#endif

