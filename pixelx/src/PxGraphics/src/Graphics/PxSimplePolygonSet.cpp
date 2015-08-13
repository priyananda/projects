#include "PxSimplePolygonSet.h"

void PxSimplePolygonSet::AddPolygon( PxPolygon * poly )
{
	polygons.push_back( poly );
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

PxPolygon PxSimplePolygonSet::operator [](int index)
{
	PxPolygon ret;
	ret = *(polygons[index]);
	return ret;
}

int PxSimplePolygonSet::Count()
{
	return polygons.size();
}

