#ifndef _PIXELX_POLYCOLL_H
#define _PIXELX_POLYCOLL_H

#include "PxPolygon.h"

class PxPolygonCollection
{
public:
	virtual void AddPolygon( PxPolygon * ) = 0;
	virtual void Finalize() = 0;
	virtual void Render(bool isWireFrame = false) = 0;
	virtual PxPolygon operator[](int index) = 0;
	virtual int Count() = 0;
};

#endif