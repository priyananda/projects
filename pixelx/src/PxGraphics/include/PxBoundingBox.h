#ifndef _PIXELX_BBOX_H
#define _PIXELX_BBOX_H

#include "PxPolygonCollection.h"

class PxSolidObject;
class PxBoundingBox
{
	bool inited;
	PxPolygon polygons[6];
public:
	PxBoundingBox():inited(false),Parent(NULL){}
	GLfloat x,y,z,length,width,height;
	void Render();
	void Finalize();
	void Register( PxPolygonCollection * pColl );
	bool Contains(GLfloat x,GLfloat y,GLfloat z );
	PxPolygon & operator []( int i ){ Finalize(); return polygons[i]; }

	PxSolidObject * Parent;
};

#endif

