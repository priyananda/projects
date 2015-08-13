#include "PxIndexedPolygonSet.h"
#include "PxSimplePolygonSet.h"

void PxIndexedPolygonSet::AddPolygon( size_t index , PxPolygon * poly )
{
	if( index < polygons.size() )
	{
		polygons[index].push_back(poly);
	}else
	{
		vector<PxPolygon *> p;
		p.push_back(poly);
		polygons.push_back(p);
	}
}

void PxIndexedPolygonSet::AddPolygonsFrom( PxBoundingBox & box )
{
	static PxSimplePolygonSet pSet;
	pSet.Clear();
	box.Register(&pSet);
	int index = polygons.size();
	int count = pSet.Count();
	for(int i = 0 ; i < count ; ++i )
		this->AddPolygon( index , pSet.Item(i) );
}

std::vector<PxPolygon *>& PxIndexedPolygonSet::GetPolygons( int index )
{
	return polygons[index];
}

