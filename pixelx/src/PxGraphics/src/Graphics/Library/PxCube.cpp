#include "PxCube.h"
#include "PxTextureManager.h"

PxCube::PxCube(PxVertex &location, PxVertex & dimensions )
{
	m_box.x = location.x; m_box.y = location.y; m_box.z = location.z;
	m_box.length = dimensions.x;m_box.width = dimensions.y;m_box.height = dimensions.z;
}

PxCube::PxCube(GLfloat px,GLfloat py,GLfloat pz,GLfloat l,GLfloat w,GLfloat h)
{
	m_box.x=px;m_box.y=py;m_box.z=pz;
	m_box.length = l;m_box.width=w;m_box.height=h;
}

void PxCube::SetTexture(cstrref name)
{
	m_texname = name;
	m_texId = PxTextureManager::GetTextureId(name);
}

void PxCube::Register(PxPolygonCollection * coll)
{
	PxPolygon * poly = new PxPolygon();
	poly->AddVertex( m_box.x, m_box.y , m_box.z ,  m_box.x, m_box.y );
	poly->AddVertex( m_box.x + m_box.length, m_box.y , m_box.z , m_box.x + m_box.length, m_box.y);
	poly->AddVertex( m_box.x + m_box.length, m_box.y + m_box.width , m_box.z,m_box.x + m_box.length, m_box.y + m_box.width );
	poly->AddVertex( m_box.x, m_box.y + m_box.width , m_box.z , m_box.x, m_box.y + m_box.width);
	poly->SetTexture( m_texname );
	coll->AddPolygon( poly );

	poly = new PxPolygon();
	poly->AddVertex( m_box.x, m_box.y , m_box.z + m_box.height ,m_box.x, m_box.y);
	poly->AddVertex( m_box.x + m_box.length, m_box.y , m_box.z + m_box.height,m_box.x + m_box.length, m_box.y );
	poly->AddVertex( m_box.x + m_box.length, m_box.y + m_box.width , m_box.z + m_box.height,m_box.x + m_box.length, m_box.y + m_box.width );
	poly->AddVertex( m_box.x, m_box.y + m_box.width , m_box.z + m_box.height , m_box.x, m_box.y + m_box.width);
	poly->SetTexture( m_texname );
	coll->AddPolygon( poly );

	poly = new PxPolygon();
	poly->AddVertex( m_box.x, m_box.y , m_box.z ,m_box.x,m_box.z);
	poly->AddVertex( m_box.x + m_box.length, m_box.y , m_box.z ,m_box.x + m_box.length,m_box.z);
	poly->AddVertex( m_box.x + m_box.length, m_box.y , m_box.z + m_box.height ,m_box.x + m_box.length, m_box.z + m_box.height);
	poly->AddVertex( m_box.x, m_box.y , m_box.z + m_box.height,m_box.x, m_box.z + m_box.height );
	poly->SetTexture(  m_texname );
	coll->AddPolygon( poly );

	poly = new PxPolygon();
	poly->AddVertex( m_box.x, m_box.y + m_box.width , m_box.z ,m_box.x,m_box.z);
	poly->AddVertex( m_box.x + m_box.length, m_box.y + m_box.width , m_box.z ,m_box.x + m_box.length, m_box.z );
	poly->AddVertex( m_box.x + m_box.length, m_box.y + m_box.width , m_box.z + m_box.height,m_box.x + m_box.length,m_box.z + m_box.height );
	poly->AddVertex( m_box.x, m_box.y + m_box.width , m_box.z + m_box.height, m_box.x, m_box.z + m_box.height);
	poly->SetTexture(  m_texname );
	coll->AddPolygon( poly );

	poly = new PxPolygon();
	poly->AddVertex( m_box.x, m_box.y , m_box.z, m_box.y , m_box.z  );
	poly->AddVertex( m_box.x, m_box.y + m_box.width , m_box.z,m_box.y + m_box.width , m_box.z );
	poly->AddVertex( m_box.x, m_box.y + m_box.width , m_box.z + m_box.height,m_box.y + m_box.width , m_box.z + m_box.height );
	poly->AddVertex( m_box.x, m_box.y , m_box.z + m_box.height,m_box.y , m_box.z + m_box.height );
	poly->SetTexture(  m_texname );
	coll->AddPolygon( poly );

	poly = new PxPolygon();
	poly->AddVertex( m_box.x + m_box.length, m_box.y , m_box.z , m_box.y , m_box.z );
	poly->AddVertex( m_box.x + m_box.length, m_box.y + m_box.width , m_box.z, m_box.y + m_box.width , m_box.z );
	poly->AddVertex( m_box.x + m_box.length, m_box.y + m_box.width , m_box.z + m_box.height,m_box.y + m_box.width , m_box.z + m_box.height );
	poly->AddVertex( m_box.x + m_box.length, m_box.y , m_box.z + m_box.height,m_box.y , m_box.z + m_box.height );
	poly->SetTexture(  m_texname );
	coll->AddPolygon( poly );
}

