#ifndef _PIXELX_LINE_H
#define _PIXELX_LINE_H

#include "PxVector.h"

class PxLine
{
public:
	float Magnitude;
	PxVector Direction;
	PxVector Location;

	PxLine( const PxVector & dir, const PxVector & pos, float len );
	void Render();
};
#endif

