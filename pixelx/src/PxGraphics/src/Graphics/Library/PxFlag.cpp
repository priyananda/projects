#include "PxFlag.h"
#include "PxRectangle.h"

PxFlag::PxFlag( float ph, float fw, float fl, float x , float y , float z, cstrref country )
{
	bBox.x = x; bBox.y = y; bBox.z = z;
	bBox.length = fl; bBox.width = ph; bBox.height = 0.5f;

	flagwidth = fw;
	texname = "FLAG_" + country;
	dispList = glGenLists(1);
	glNewList(dispList, GL_COMPILE );
		glColor3ub(0,224,116);
		glLineWidth(5.0f);
		glBegin( GL_LINES );
			glVertex3f( x, y , z );
			glVertex3f( x, y + ph, z );
		glEnd();
		glLineWidth(1.0f);
		glColor3ub(255,255,255);
	glEndList();
}

void PxFlag::Register(PxPolygonCollection * pColl)
{
	//PxRectangle * rect = new PxRectangle( bBox.x, bBox.y + bBox.width - flagwidth , bBox.z, bBox.length , flagwidth, 0 );
	auto poly = std::make_unique<PxPolygon>();
	poly->AddVertex(bBox.x , bBox.width	- flagwidth , bBox.z,1,1 );
	poly->AddVertex(bBox.x , bBox.width , bBox.z,1,0 );
	poly->AddVertex(bBox.x + bBox.length , bBox.width, bBox.z,0,0 );
	poly->AddVertex(bBox.x + bBox.length , bBox.width - flagwidth , bBox.z,0,1 );
	poly->SetTexture(texname);
	pColl->AddPolygon( std::move(poly) );
}

void PxFlag::Render()
{
	glCallList(dispList);
}

