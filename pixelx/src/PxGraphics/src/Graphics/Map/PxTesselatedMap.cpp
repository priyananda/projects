#include "PxTesselatedMap.h"
#include "PxTesselator.h"

void PxTesselatedMap::AddObject( string name, PxRuntimeObjectType type, string params, PxSolidObject * pObj)
{
	PxRuntimeObject ro;
	ro.Name = name;
	ro.Params = params;
	ro.Type = type;
	PxBoundingBox & bb = pObj->GetBoundingBox();
	ro.x = bb.x; ro.y = bb.y; ro.z = bb.z;
	ro.dx = bb.length ; ro.dy = bb.width ; ro.dz = bb.height;
	pObj->Register(& mPolySet );
	Objects.push_back( ro );
}

void PxTesselatedMap::AddPolygon( PxPolygon & p )
{
	mPolySet.AddPolygon(new PxPolygon(p));
}
PxTriangleSet * PxTesselatedMap::GetTriangleSet()
{
	if( mPolySet.Count() == 0 )
		return mTriangleSet;
	
	delete mTriangleSet;
	mTriangleSet = PxTesselator::Tesselate(&mPolySet);
	return mTriangleSet;
}

void PxTesselatedMap::SetTriangleSet( PxTriangleSet * _pSet )
{
	if( mTriangleSet )
		delete mTriangleSet;
	mTriangleSet = _pSet;
}

