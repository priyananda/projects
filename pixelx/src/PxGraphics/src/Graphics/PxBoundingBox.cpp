#include "PxBoundingBox.h"
#include "PxTextureManager.h"

void PxBoundingBox::Render()
{
	PxTextureManager::Unbind();
	glColor4f(1,1,1,1);
	glBegin( GL_LINE_LOOP );
		glVertex3f( x, y , z );
		glVertex3f( x + length, y , z );
		glVertex3f( x + length, y + width , z );
		glVertex3f( x, y + width , z );
	glEnd();
	glBegin( GL_LINE_LOOP );
		glVertex3f( x, y , z + height );
		glVertex3f( x + length, y , z + height );
		glVertex3f( x + length, y + width , z + height );
		glVertex3f( x, y + width , z + height );
	glEnd();
	glBegin( GL_LINE_LOOP );
		glVertex3f( x, y , z );
		glVertex3f( x + length, y , z );
		glVertex3f( x + length, y , z + height );
		glVertex3f( x, y , z + height );
	glEnd();
	glBegin( GL_LINE_LOOP );
		glVertex3f( x, y + width , z );
		glVertex3f( x + length, y + width , z );
		glVertex3f( x + length, y + width , z + height );
		glVertex3f( x, y + width , z + height );
	glEnd();
	glBegin( GL_LINE_LOOP );
		glVertex3f( x, y , z );
		glVertex3f( x, y + width , z );
		glVertex3f( x, y + width , z + height );
		glVertex3f( x, y , z + height );
	glEnd();
	glBegin( GL_LINE_LOOP );
		glVertex3f( x + length, y , z );
		glVertex3f( x + length, y + width , z );
		glVertex3f( x + length, y + width , z + height );
		glVertex3f( x + length, y , z + height );
	glEnd();
}

void PxBoundingBox::Register( PxPolygonCollection * pColl )
{
	if( ! inited )
	{
		Finalize();
	}
	for( int i = 0; i < 6 ; ++i )
	{
		pColl->AddPolygon(std::make_unique<PxPolygon>(polygons[i]));
	}
}

bool PxBoundingBox::Contains(GLfloat vx,GLfloat vy,GLfloat vz)
{
	if( vx < x || vx > x + length )
		return false;
	if( vy < y || vy > y + width )
		return false;
	if( vz < z || vz > z + height )
		return false;
	return true;
}

void PxBoundingBox::Finalize()
{
	if( inited )
		return;

	polygons[0].AddVertex( x, y , z );
	polygons[0].AddVertex( x + length, y , z );
	polygons[0].AddVertex( x + length, y + width , z );
    polygons[0].AddVertex( x, y + width , z );
	
	polygons[1].AddVertex( x, y , z + height );
	polygons[1].AddVertex( x + length, y , z + height );
	polygons[1].AddVertex( x + length, y + width , z + height );
	polygons[1].AddVertex( x, y + width , z + height );
	
	polygons[2].AddVertex( x, y , z );
	polygons[2].AddVertex( x + length, y , z );
	polygons[2].AddVertex( x + length, y , z + height );
	polygons[2].AddVertex( x, y , z + height );
	
	polygons[3].AddVertex( x, y + width , z );
	polygons[3].AddVertex( x + length, y + width , z );
	polygons[3].AddVertex( x + length, y + width , z + height );
	polygons[3].AddVertex( x, y + width , z + height );
	
	polygons[4].AddVertex( x, y , z );
	polygons[4].AddVertex( x, y + width , z );
	polygons[4].AddVertex( x, y + width , z + height );
	polygons[4].AddVertex( x, y , z + height );
	
	polygons[5].AddVertex( x + length, y , z );
	polygons[5].AddVertex( x + length, y + width , z );
	polygons[5].AddVertex( x + length, y + width , z + height );
	polygons[5].AddVertex( x + length, y , z + height );

	inited = true;
}

