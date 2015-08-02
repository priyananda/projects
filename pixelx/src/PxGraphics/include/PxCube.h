#ifndef _PIXELX_CUBE_H
#define _PIXELX_CUBE_H

#include "PxSolidObject.h"

class PxCube : public PxSolidObject
{
	PxBoundingBox m_box;
	GLuint m_texId;
	string m_texname;
public:
	PxCube( PxVertex & location , PxVertex & dimensions );
	PxCube( GLfloat x = 0,GLfloat y = 0,GLfloat z = 0,GLfloat length = 0,GLfloat width =0 ,GLfloat height =0);

	void SetTexture(cstrref name);

	void Register( PxPolygonCollection * coll );
	void Render()
	{
	}
	PxBoundingBox & GetBoundingBox(){ return m_box; }
};

#endif

