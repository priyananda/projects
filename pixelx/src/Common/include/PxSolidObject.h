#ifndef _PIXELX_SOLIDOBJECT_H
#define _PIXELX_SOLIDOBJECT_H
#include "..\..\PxGraphics\include\PxBoundingBox.h"
#include "..\..\PxGraphics\include\PxPolygonCollection.h"

class PxSolidObject
{
public:
	virtual void Register( PxPolygonCollection * coll ) = 0;
	virtual void Render() = 0;
	virtual PxBoundingBox & GetBoundingBox() = 0;

	virtual void OnCollision(){}
	virtual bool IsCollidable(){return true;}
};

#endif