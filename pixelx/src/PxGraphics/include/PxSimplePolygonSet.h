#ifndef _PIXELX_SIMPLEPOLYSET_H
#define _PIXELX_SIMPLEPOLYSET_H

#include "PxPolygonCollection.h"
#include <list>
using std::list;

class PxSimplePolygonSet : public PxPolygonCollection
{
	vector<PxPolygon *> polygons;
	GLuint dlist;
public:
	void AddPolygon( PxPolygon * );
	void Finalize();
	void Render(bool isWireFrame = false);

	PxPolygon operator[]( int index );
	int Count();
	void Clear()
	{
		polygons.clear();
	}

	PxPolygon * Item(int i)
	{
		return polygons[i];
	}
};

#endif

