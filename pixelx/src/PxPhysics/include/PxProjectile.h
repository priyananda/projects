#ifndef _PIXELX_PROJECTILE_H
#define _PIXELX_PROJECTILE_H

#include "PxVector.h"

class PxProjectile
{
protected:
	PxVector	m_location;
	PxVector	m_direction;
	float		m_speed;
public:
	PxProjectile( const PxVector & loc, const PxVector & dir , float speed );
	void Move();
	virtual void Render() = 0;
	virtual void HandleCollision() = 0;
};
#endif

