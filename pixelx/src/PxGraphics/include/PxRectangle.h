#ifndef _PIXELX_RECT_H
#define _PIXELX_RECT_H
#include "PxPolygon.h"

class PxRectangle: public PxPolygon
{
public:
	PxRectangle( float x,float y , float z, float x2, float y2 , float z2, cstrref texName = "");
};

#endif

