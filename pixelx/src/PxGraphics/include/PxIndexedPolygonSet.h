#ifndef _PIXELX_INDEXDPOLYGONSET_H
#define _PIXELX_INDEXDPOLYGONSET_H

#include "PxSimplePolygonSet.h"
#include "PxBoundingBox.h"

#include <vector>
using std::vector;

class PxCollisionElement
{
	PxBoundingBox box;
	PxSimplePolygonSet polySet;
public:
	PxCollisionElement( PxBoundingBox & box );
	PxPolygonCollection * GetCollection()
	{
		return &polySet;
	}
};
class PxIndexedPolygonSet
{
	vector< PxBoundingBox > boxes;
	vector< vector< PxPolygon *> > polygons;
public:
	void AddPolygon( int index, PxPolygon * );
	void AddPolygonsFrom( PxBoundingBox & box );
	vector<PxPolygon*>& GetPolygons(int index);
	int Count()
	{
		return polygons.size();
	}
};
#endif

