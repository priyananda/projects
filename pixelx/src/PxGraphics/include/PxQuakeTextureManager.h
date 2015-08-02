#ifndef _PIXELX_QUAKETEXMGR_H
#define _PIXELX_QUAKETEXMGR_H

#include "PxTextureManager.h"
class PxQuakeTextureManager
{
	static string MapTexturePath(cstrref name);
public:
	static void Bind( cstrref name , TextureMode mode = eTexModeStretchBoth, bool bTexEnv = true );
	static GLuint GetTextureId(cstrref name );
	static void Bind( GLuint texId , TextureMode mode = eTexModeStretchBoth, bool bTexEnv = true );
};
#endif

