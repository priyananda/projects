#include "PxTesselator.h"

#include <list>
using std::list;

#include <vector>
using std::vector;

static void Tesselate( PxPolygon & p , PxTriangleSet * pts )
{
	vector<std::unique_ptr<PxVertex>> & pverts = p.GetVertices();
	bool isAllZero = true;
	int numTriangles = pverts.size() - 2;
	bool isGrass = p.GetTexture() == "GRASS";
	for( int i = 1 ; i <= numTriangles; ++i )
	{
		PxTriangle tri;
		tri[0] = *pverts[0];
		tri[1] = *pverts[i];
		tri[2] = *pverts[i+1];
		if( !isGrass && tri[0].y == 0 && tri[1].y == 0 && tri[2].y == 0 )
			continue;
		pts->AddTriangle( p.GetTexture() , p.GetTextureMode() , tri );
	}
}
PxTriangleSet * PxTesselator::Tesselate( PxPolygonCollection * poly )
{
	int len = poly->Count();
	PxTriangleSet * pTS = new PxTriangleSet();
	for( int i = 0 ; i < len ; ++i )
	{
		PxPolygon p = poly->operator [](i);
		::Tesselate(p,pTS);
	}
	return pTS;
}

