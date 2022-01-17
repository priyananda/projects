#ifndef _PIXELX_MULTITEXMGR_H
#define _PIXELX_MULTITEXMGR_H

#include "PxTextureManager.h"

class PxMultiTextureManager
{
public:
	static void ToggleVertexArray( bool enable );
	static void ToggleTextureArray( int which, bool enable );
	static void SetTexCoordPointer( int which , GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	static void SetVertexPointer( GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	static void SetActive(int which);
	static void SetClientActive(int which);
	static void Bind( int which , cstrref name , TextureMode mode = TextureMode::NoStretch );
	static void Bind( int which , GLuint texid , TextureMode mode = TextureMode::NoStretch );
	static void Unbind(int which );
};
#endif

