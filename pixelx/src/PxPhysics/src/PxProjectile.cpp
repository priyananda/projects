#include "PxProjectile.h"
#include "PxCollisionManager.h"

PxProjectile::PxProjectile( const PxVector & loc, const PxVector & dir, float speed )
	:m_location(loc), m_direction(dir), m_speed( speed )
{
	m_direction.Normalize();
}

void PxProjectile::Move()
{
	if( m_direction.x == 0 && m_direction.y == 0 && m_direction.z == 0 )
		return;
	PxVector new_loc = m_location + m_direction * m_speed;// * PxSystem::FrameInterval;
	if( PxCollisionManager::Collides( m_location , new_loc,0.5f ) )
	{
		m_location = new_loc;
		this->HandleCollision();
	}
	else
	{
		m_location = new_loc;
		m_speed *= 1.1f;
	}
}

