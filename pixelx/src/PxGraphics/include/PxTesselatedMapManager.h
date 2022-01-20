#ifndef _PIXELX_TESSELATED_MAP_MANAGER_H
#define _PIXELX_TESSELATED_MAP_MANAGER_H

#include "PxTesselatedMap.h"
class PxTesselatedMapManager
{
public:
	static void Persist(PxTesselatedMap&, cstrref filename );
	static UP<PxTesselatedMap> Restore( cstrref name );
};
#endif

