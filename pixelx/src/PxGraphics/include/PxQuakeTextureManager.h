#ifndef _PIXELX_QUAKETEXMGR_H
#define _PIXELX_QUAKETEXMGR_H

#include "PxTextureManager.h"
class PxQuakeTextureManager
{
	static string MapTexturePath(cstrref name);
public:
	static void Bind( cstrref name , TextureMode mode = TextureMode::StretchBoth, bool bTexEnv = true );
	static GLuint GetTextureId(cstrref name );
	static void Bind( GLuint texId , TextureMode mode = TextureMode::StretchBoth, bool bTexEnv = true );
};
#endif

