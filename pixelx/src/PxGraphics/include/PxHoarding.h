#ifndef _PIXELX_HOARDING_H
#define _PIXELX_HOARDING_H

#include "PxSolidObject.h"

class PxHoarding : public PxSolidObject
{
	PxBoundingBox bbox;
	string m_texname;
public:
	PxHoarding( float x,float y,float z, float length,float width, float height, cstrref texname );
	void Register(PxPolygonCollection * coll);
	void Render();
	PxBoundingBox & GetBoundingBox();
};
#endif

