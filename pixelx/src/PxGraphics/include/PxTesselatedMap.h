#ifndef _PIXELX_TESSELATED_MAP_H
#define _PIXELX_TESSELATED_MAP_H

#include "PxTriangleSet.h"
#include "PxRuntimeObject.h"

#include "PxSimplePolygonSet.h"
#include "PxSolidObject.h"

#include <vector>
using std::vector;
class PxTesselatedMap
{
	PxSimplePolygonSet	mPolySet;
	UP<PxTriangleSet>	mTriangleSet;
public:
	vector<PxRuntimeObject> Objects;

	PxTesselatedMap(){}
	
	void Render()
	{
		if( mTriangleSet )
			mTriangleSet->Render();
	}
	void AddObject( string name, PxRuntimeObjectType type, string params, PxSolidObject * pObj );
	void AddPolygon( PxPolygon & );
	PxTriangleSet * GetTriangleSet();
	void SetTriangleSet(UP<PxTriangleSet>&& _pSet);
};
#endif

