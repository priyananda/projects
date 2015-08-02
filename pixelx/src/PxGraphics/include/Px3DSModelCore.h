#ifndef _PIXELX_3DSMODEL_H
#define _PIXELX_3DSMODEL_H

#include "PxModel.h"
#include "l3ds.h"
#include "PxTexturemanager.h"

class Px3DSModelCore : public PxModelCore
{
	L3DS m_scene;
	GLuint dispList;
	GLuint texid;
public:
	Px3DSModelCore( cstrref name );
	void Register(PxPolygonCollection *){}
	void Render();
	void Animate( int StartFrame , int EndFrame , float interp){}
	void SetTexture( cstrref name )
	{
		texid = PxTextureManager::GetTextureId(name);
	}
	~Px3DSModelCore();
};
#endif

