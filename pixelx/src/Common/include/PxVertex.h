#ifndef _PIXELX_VERTEX_H
#define _PIXELX_VERTEX_H

#include "Common.h"

class PxVertex
{
public:
	GLfloat x,y,z;
	GLint  u,v;

	// -1,-1 tex co-ordinates means autogen textures for that axis
	PxVertex( GLfloat _x = 0 ,GLfloat _y = 0 ,GLfloat _z = 0,GLuint _u = -1,GLuint _v = -1)
		:x(_x),y(_y),z(_z),u(_u),v(_v){}
	PxVertex( const PxVertex & pv )
		:x(pv.x),y(pv.y),z(pv.z),u(pv.u),v(pv.v){}
};

#endif