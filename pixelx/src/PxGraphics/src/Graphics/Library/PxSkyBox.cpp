#include "PxSkyBox.h"
#include "..\..\PxPhysics\include\PxVector.h"
#include "PxTextureManager.h"

void PxSkyBox::AddVertices()
{
	SkyboxVertex[0].x = bBox.x;
	SkyboxVertex[0].y = bBox.y;
	SkyboxVertex[0].z = bBox.z + bBox.height;

	SkyboxVertex[1].x = bBox.x;
	SkyboxVertex[1].y = bBox.y;
	SkyboxVertex[1].z = bBox.z;

	SkyboxVertex[2].x = bBox.x+ bBox.length;
	SkyboxVertex[2].y = bBox.y;
	SkyboxVertex[2].z = bBox.z;

	SkyboxVertex[3].x = bBox.x + bBox.length;
	SkyboxVertex[3].y = bBox.y;
	SkyboxVertex[3].z = bBox.z + bBox.height;

	SkyboxVertex[4].x = bBox.x;
	SkyboxVertex[4].y = bBox.y + bBox.width;
	SkyboxVertex[4].z = bBox.z + bBox.height;

	SkyboxVertex[5].x = bBox.x;
	SkyboxVertex[5].y = bBox.y + bBox.width;
	SkyboxVertex[5].z = bBox.z;

	SkyboxVertex[6].x = bBox.x + bBox.length;
	SkyboxVertex[6].y = bBox.y + bBox.width;
	SkyboxVertex[6].z = bBox.z;

	SkyboxVertex[7].x = bBox.x + bBox.length;
	SkyboxVertex[7].y = bBox.y + bBox.width;
	SkyboxVertex[7].z = bBox.z + bBox.height;
}

PxSkyBox::PxSkyBox(float l,float w,float h)
{
	bBox.x = -l/2;bBox.length = l;
	bBox.y = 0;bBox.width = w;
	bBox.z = -h/2;bBox.height = h;

	AddVertices();
}
PxSkyBox::PxSkyBox(float l,float w,float h,float dl,float dw,float dh)
{
	bBox.x = l;bBox.length = dl;
	bBox.y = w;bBox.width = dw;
	bBox.z = h;bBox.height = dh;

	AddVertices();
}
void PxSkyBox::Register( PxPolygonCollection * coll )
{
	PxPolygon * poly;
	
	poly = new PxPolygon();
	poly->SetTexture( "SKYBOX_LEFT" );
	poly->AddVertex( SkyboxVertex[0].x , SkyboxVertex[0].y,SkyboxVertex[0].z,0.0f,0.0f);
	poly->AddVertex( SkyboxVertex[1].x , SkyboxVertex[1].y,SkyboxVertex[1].z,1.0f,0.0f);
	poly->AddVertex( SkyboxVertex[5].x , SkyboxVertex[5].y,SkyboxVertex[5].z,1.0f,1.0f);
	poly->AddVertex( SkyboxVertex[4].x , SkyboxVertex[4].y,SkyboxVertex[4].z,0.0f,1.0f);
	coll->AddPolygon( poly );

	poly = new PxPolygon();
	poly->SetTexture( "SKYBOX_BACK" );
	poly->AddVertex( SkyboxVertex[1].x , SkyboxVertex[1].y,SkyboxVertex[1].z,0.0f,0.0f);
	poly->AddVertex( SkyboxVertex[2].x , SkyboxVertex[2].y,SkyboxVertex[2].z,1.0f,0.0f);
	poly->AddVertex( SkyboxVertex[6].x , SkyboxVertex[6].y,SkyboxVertex[6].z,1.0f,1.0f);
	poly->AddVertex( SkyboxVertex[5].x , SkyboxVertex[5].y,SkyboxVertex[5].z,0.0f,1.0f);
	coll->AddPolygon( poly );

	poly = new PxPolygon();
	poly->SetTexture( "SKYBOX_RIGHT" );
	poly->AddVertex( SkyboxVertex[2].x , SkyboxVertex[2].y,SkyboxVertex[2].z,0.0f,0.0f);
	poly->AddVertex( SkyboxVertex[3].x , SkyboxVertex[3].y,SkyboxVertex[3].z,1.0f,0.0f);
	poly->AddVertex( SkyboxVertex[7].x , SkyboxVertex[7].y,SkyboxVertex[7].z,1.0f,1.0f);
	poly->AddVertex( SkyboxVertex[6].x , SkyboxVertex[6].y,SkyboxVertex[6].z,0.0f,1.0f);
	coll->AddPolygon( poly );

	poly = new PxPolygon();
	poly->SetTexture( "SKYBOX_FRONT" );
	poly->AddVertex( SkyboxVertex[3].x , SkyboxVertex[3].y,SkyboxVertex[3].z,0.0f,0.0f);
	poly->AddVertex( SkyboxVertex[0].x , SkyboxVertex[0].y,SkyboxVertex[0].z,1.0f,0.0f);
	poly->AddVertex( SkyboxVertex[4].x , SkyboxVertex[4].y,SkyboxVertex[4].z,1.0f,1.0f);
	poly->AddVertex( SkyboxVertex[7].x , SkyboxVertex[7].y,SkyboxVertex[7].z,0.0f,1.0f);
	coll->AddPolygon( poly );

	poly = new PxPolygon();
	poly->SetTexture( "SKYBOX_RIGHT" );
	poly->AddVertex( SkyboxVertex[2].x , SkyboxVertex[2].y,SkyboxVertex[2].z,0.0f,0.0f);
	poly->AddVertex( SkyboxVertex[3].x , SkyboxVertex[3].y,SkyboxVertex[3].z,1.0f,0.0f);
	poly->AddVertex( SkyboxVertex[7].x , SkyboxVertex[7].y,SkyboxVertex[7].z,1.0f,1.0f);
	poly->AddVertex( SkyboxVertex[6].x , SkyboxVertex[6].y,SkyboxVertex[6].z,0.0f,1.0f);
	coll->AddPolygon( poly );

	poly = new PxPolygon();
	poly->SetTexture( "SKYBOX_TOP" );
	poly->AddVertex( SkyboxVertex[7].x , SkyboxVertex[7].y,SkyboxVertex[7].z,0.0f,1.0f);
	poly->AddVertex( SkyboxVertex[4].x , SkyboxVertex[4].y,SkyboxVertex[4].z,1.0f,1.0f);
	poly->AddVertex( SkyboxVertex[5].x , SkyboxVertex[5].y,SkyboxVertex[5].z,1.0f,0.0f);
	poly->AddVertex( SkyboxVertex[6].x , SkyboxVertex[6].y,SkyboxVertex[6].z,0.0f,0.0f);
	coll->AddPolygon( poly );
}
void PxSkyBox::Render()
{
}
PxBoundingBox & PxSkyBox::GetBoundingBox()
{
	return bBox;
}

