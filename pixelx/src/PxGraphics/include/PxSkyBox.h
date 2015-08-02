#ifndef _PIXELX_SKYBOX_H
#define _PIXELX_SKYBOX_H

#include "PxCamera.h"
#include "PxSolidObject.h"

class PxSkyBox : public PxSolidObject
{
	PxVector SkyboxVertex[8];
	PxBoundingBox bBox;

	void AddVertices();
public:
	PxSkyBox(float l,float w,float h);
	PxSkyBox(float l,float w,float h,float dl,float dw,float dh);
	void Register( PxPolygonCollection * coll );
	void Render();
	PxBoundingBox & GetBoundingBox();
};	

#endif

