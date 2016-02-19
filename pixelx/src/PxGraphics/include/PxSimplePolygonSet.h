#ifndef _PIXELX_SIMPLEPOLYSET_H
#define _PIXELX_SIMPLEPOLYSET_H

#include "PxPolygonCollection.h"
#include <list>
using std::list;

class PxSimplePolygonSet : public PxPolygonCollection
{
	vector<std::unique_ptr<PxPolygon>> polygons;
	GLuint dlist;
public:
	PxSimplePolygonSet() = default;
	PxSimplePolygonSet(const PxSimplePolygonSet&) = delete;

	void AddPolygon( std::unique_ptr<PxPolygon>&& spPoly);
	void Finalize();
	void Render(bool isWireFrame = false);

	PxPolygon& operator[](int index)
	{
		return *Item(index);
	}
	int Count();
	void Clear()
	{
		polygons.clear();
	}

	PxPolygon * Item(int i)
	{
		return polygons[i].get();
	}
};

#endif

