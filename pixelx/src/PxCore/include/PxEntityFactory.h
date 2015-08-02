#ifndef _PIXELX_ENTITYFACTORY
#define _PIXELX_ENTITYFACTORY

#include <list>
using std::list;

#include "..\..\PxGraphics\include\PxQuakeMap.h"

class PxSolidObject;
class PxEntityFactory
{
public:
	static int AddObjects( PxQuake3EntityCollection & entities , list<PxSolidObject *> & mRuntimeObjects , cstrref botname);
};
#endif

