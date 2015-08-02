#include "PxLine.h"

void PxLine::Render()
{
	PxVector other = Location + Direction * Magnitude;
	glLineWidth(5.0f);
	glBegin( GL_LINES );
		glVertex3f( Location.x , Location.y , Location.z );
		glVertex3f( other.x , other.y , other.z );
	glEnd();
	glLineWidth(1.0f);
	glDisable( GL_LIGHTING );
}
PxLine::PxLine( const PxVector & dir, const PxVector & pos, float len )
	:Direction(dir),Location(pos),Magnitude(len)
{
	Direction.Normalize();
}

