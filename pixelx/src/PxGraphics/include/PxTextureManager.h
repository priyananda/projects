#ifndef _PIXELX_TEXMANAGER_H
#define _PIXELX_TEXMANAGER_H
#include "Common.h"

#include <map>
using std::map;

enum TextureMode
{
	eTexModeNoStretch,
	eTexModeStretchX,
	eTexModeStretchY,
	eTexModeStretchBoth
};
class PxTextureManager
{
	static map<string,GLuint> m_textures;
	static map<string,string> m_texturepaths;

	static void _LoadTexture( cstrref sname );
public:
	static void Init();
	static void Bind( cstrref name , TextureMode mode = eTexModeStretchBoth, bool bTexEnv = true );
	static GLuint GetTextureId(cstrref name );
	static void Bind( GLuint texId , TextureMode mode = eTexModeStretchBoth, bool bTexEnv = true );
	static void Unbind();
	static void SetMode(TextureMode mode,bool bTexEnv = true);

	static GLuint LoadTexture( cstrref sname , cstrref path );
	static void LoadAllTextures();
	static void Unload( cstrref name );
};

#endif

