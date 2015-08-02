#ifndef _PIXELX_TEXTWRITER_H
#define _PIXELX_TEXTWRITER_H

#include "Common.h"

class PxTextWriter
{
	static GLuint m_texid;
	static GLuint m_r,m_g,m_b,m_a;
	static GLuint m_size;
	static GLuint m_base;
public:
	static void Init();
	static void SetTexture( cstrref name );
	static void SetTexture( GLuint id );
	static void SetColor( GLuint r,GLuint g, GLuint b, GLuint a = 1 );
	static void SetFont( cstrref name );
	static void SetSize( GLuint size );
	static void Write( int x, int y, cstrref text );
	static void Write( int x, int y, cstrref text, GLuint size );
	static void Write( int x, int y, cstrref text, GLuint size,GLuint r,GLuint g, GLuint b, GLuint a = 1 );
	static void Write( int x, int y, cstrref text, GLuint size,cstrref texname );
};

#endif

