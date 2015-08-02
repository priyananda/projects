#include "PxPointProjectile.h"
#include "..\..\PxGraphics\include\PxTextureManager.h"

#include "gl/glut.h"

void PxPointProjectile::Render()
{
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glTranslatef(m_location.x,m_location.y, m_location.z);
	glColor4f( 1,1,1,0.05f );
    PxTextureManager::Bind( "BULLET" );
	//auxSolidSphere(0.05f);
	glColor3f(1,1,1);
	glPopMatrix();
}

#include "..\..\PxSound\include\PxAudioManager.h"
void PxPointProjectile::HandleCollision()
{
	PxAudioManager::Play( "EXPLOSION" );
	m_direction = PxVector();
	PxLog::LogMessage( "Collided" );
}

