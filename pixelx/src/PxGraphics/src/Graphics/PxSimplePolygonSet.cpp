#include "PxSimplePolygonSet.h"

void PxSimplePolygonSet::AddPolygon( std::unique_ptr<PxPolygon>&& poly )
{
	polygons.push_back( std::move(poly) );
}
void PxSimplePolygonSet::Finalize()
{
	dlist = glGenLists(1);
	glNewList(dlist,GL_COMPILE);
	int size = polygons.size();
	for(int i = 0 ; i < size ; ++i )
		polygons[i]->Render();
	glEndList();
}

void PxSimplePolygonSet::Render(bool isWireFrame)
{
	for(size_t i = 0 ; i < polygons.size(); ++i )
		polygons[i]->Render(isWireFrame);
}

int PxSimplePolygonSet::Count()
{
	return polygons.size();
}

