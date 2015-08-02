#ifndef PIXELX_COLLISIONCONTROLLER_H
#define PIXELX_COLLISIONCONTROLLER_H

class PxCamera;
class ICollisionController
{
public:
	virtual void Collide(PxCamera & ) = 0;
	virtual bool IsOnGround() = 0;
};
#endif