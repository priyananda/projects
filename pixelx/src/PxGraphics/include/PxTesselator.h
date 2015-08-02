#ifndef _PIXELX_TESSELATOR_H
#define _PIXELX_TESSELATOR_H

#include "PxPolygonCollection.h"
#include "PxTriangleSet.h"

class PxTesselator
{
public:
	static PxTriangleSet * Tesselate( PxPolygonCollection * poly );
};
#endif

