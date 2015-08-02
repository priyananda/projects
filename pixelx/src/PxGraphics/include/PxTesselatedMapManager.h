#ifndef _PIXELX_TESSELATED_MAP_MANAGER_H
#define _PIXELX_TESSELATED_MAP_MANAGER_H

#include "PxTesselatedMap.h"
class PxTesselatedMapManager
{
public:
	static void Persist( PxTesselatedMap * pTS, cstrref filename );
	static PxTesselatedMap * Restore( cstrref name );
};
#endif

