#ifndef _PIXELX_STEPS_H
#define _PIXELX_STEPS_H

#include "PxSolidObject.h"

class PxSteps: public PxSolidObject
{
	PxBoundingBox bBox;
	PxDirectionEnum dir;
	float length;
	float numSteps;
	float stepHeight;
public:
	PxSteps( PxDirectionEnum _dir, float len, float num, float height, float x,float y, float z);

	void Register(PxPolygonCollection *);
	void Render();
	PxBoundingBox & GetBoundingBox()
	{
		return bBox;
	}
};

#endif

