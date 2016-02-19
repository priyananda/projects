#include "PxPolygon.h"
#include "PxTextureManager.h"

void PxPolygon::CalculateNormal()
{
	if( vertices.size() < 3 ) return;
	PxVertex* Vertex[3] =
	{
		vertices[0].get(),
		vertices[1].get(),
		vertices[2].get()
	};
	GLfloat ux;
	GLfloat uy;
	GLfloat uz;
	GLfloat vx;
	GLfloat vy;
	GLfloat vz;
	ux = Vertex[1]->x - Vertex[0]->x;
	uy = Vertex[1]->y - Vertex[0]->y;
	uz = Vertex[1]->z - Vertex[0]->z;
	vx = Vertex[2]->x - Vertex[0]->x;
	vy = Vertex[2]->y - Vertex[0]->y;
	vz = Vertex[2]->z - Vertex[0]->z;
	Normal.x = (uy*vz)-(vy*uz);
	Normal.y = (uz*vx)-(vz*ux);
	Normal.z = (ux*vy)-(vx*uy);
	Normal.Normalize();
}

void PxPolygon::AddVertex( const PxVertex & pv )
{
	vertices.emplace_back( new PxVertex(pv) );
	CalculateNormal();
}

void PxPolygon::AddVertex(  GLfloat _x ,GLfloat _y,GLfloat _z,GLuint _u,GLuint _v)
{
	vertices.push_back( std::make_unique<PxVertex>(_x,_y,_z,_u,_v));
	CalculateNormal();
}
void PxPolygon::Render(bool isWireFrame)
{
	if( dList == -1 )
		Finalize();
	if( isWireFrame )
		glPolygonMode( GL_FRONT_AND_BACK , GL_LINE );
	else
		glPolygonMode( GL_FRONT_AND_BACK , GL_FILL );
	glCallList(dList);
}

void PxPolygon::Finalize()
{
	if( dList != -1 )
		return;
	PxVertex * v = vertices.front().get();
	TextureMode mode = GetTextureMode();

	dList = glGenLists(1);

	glNewList( dList , GL_COMPILE );
	if( texture != -1 )
		PxTextureManager::Bind( texture , mode );

	glBegin( GL_POLYGON );
	for(size_t i = 0 ; i < vertices.size(); ++i)
	{
		PxVertex * v = vertices[i].get();
		if( mode == eTexModeNoStretch )
			glTexCoord2f((GLfloat)v->u, (GLfloat)v->v);
		glVertex3f(v->x, v->y, v->z);
	}
	glEnd();
	glEndList();
}

void PxPolygon::SetTexture( cstrref tname)
{
	texturename = tname;
	if( tname.length() > 0 )
		texture = PxTextureManager::GetTextureId( tname );
	else
		texture = -1;
}

PxVector PxPolygon::operator [](int index ) const
{
	PxVector ret;
	ret.x = vertices[index]->x;
	ret.y = vertices[index]->y;
	ret.z = vertices[index]->z;
	return ret;
}

TextureMode PxPolygon::GetTextureMode()
{
	PxVertex * v = vertices.front().get();
	TextureMode mode = eTexModeNoStretch;

	if( v->u == -1 )
		if( v->v == -1 )
			mode = eTexModeStretchBoth;
		else
			mode = eTexModeStretchX;
	else if ( v->v == -1 )
			mode = eTexModeStretchY;
	return mode;
}

