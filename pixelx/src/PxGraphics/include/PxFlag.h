#ifndef _PIXELX_FLAG_H
#define _PIXELX_FLAG_H

#include "PxSolidObject.h"

class PxFlag : public PxSolidObject
{
	PxBoundingBox bBox;
	GLuint dispList;
	float flagwidth;
	string texname;
public:
	PxFlag( float poleHeight , float flagWidth, float flagLength , float x, float y, float z, cstrref country);
	void Register( PxPolygonCollection * pcoll );
	void Render();
	PxBoundingBox & GetBoundingBox()
	{
		return bBox;
	}
};
#endif

