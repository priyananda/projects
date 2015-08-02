#ifndef _PIXELX_OBJECTFACTORY_H
#define _PIXELX_OBJECTFACTORY_H

#include "PxTesselatedMap.h"
class PxObjectFactory
{
public:
	static PxSolidObject * GetObject( const PxRuntimeObject & ro );
	static vector<PxSolidObject *> GetObjects( const PxTesselatedMap * p );
};
#endif

