#ifndef _PIXELX_OBJECTFACTORY_H
#define _PIXELX_OBJECTFACTORY_H

#include "PxTesselatedMap.h"
class PxObjectFactory
{
public:
	static UP<PxSolidObject> GetObject( const PxRuntimeObject & ro );
	static vector<UP<PxSolidObject>> GetObjects(const PxTesselatedMap&);
};
#endif

