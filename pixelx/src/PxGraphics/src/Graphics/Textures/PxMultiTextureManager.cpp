#include "PxMultiTextureManager.h"
#include "PxExtensionManager.h"

static int m_CurrentTexture = 1;
static int m_CurrentClientTexture = 1;

void PxMultiTextureManager::ToggleVertexArray( bool enable )
{
	if( enable )
		glEnableClientState(GL_VERTEX_ARRAY);
	else
		glDisableClientState(GL_VERTEX_ARRAY);
}

void PxMultiTextureManager::ToggleTextureArray( int which, bool enable )
{
	int temp = m_CurrentClientTexture;
	if( which & 1 )
	{
		SetClientActive(1);
		if( enable )
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		else
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	if( which & 2 )
	{
		SetClientActive(2);
		if( enable )
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		else
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	SetClientActive(temp);
}

void PxMultiTextureManager::SetActive(int which)
{
	m_CurrentTexture = which;
	switch(which)
	{
		case 1:
			glActiveTextureARB(GL_TEXTURE0_ARB);
			break;
		case 2:
			glActiveTextureARB(GL_TEXTURE1_ARB);
			break;
	}
}

void PxMultiTextureManager::SetClientActive(int which)
{
	m_CurrentClientTexture = which;
	switch(which)
	{
		case 1:
			glClientActiveTextureARB(GL_TEXTURE0_ARB);
			break;
		case 2:
			glClientActiveTextureARB(GL_TEXTURE1_ARB);
			break;
	}
}

void PxMultiTextureManager::SetTexCoordPointer( int which , GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
	int temp = m_CurrentClientTexture;
	SetClientActive(which);
	glTexCoordPointer(
		size,
		type,
		stride,
		pointer
	);
	SetClientActive(temp);
}
void PxMultiTextureManager::SetVertexPointer( GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
	glVertexPointer(
		size,
		type,
		stride,
		pointer
	);
}
void PxMultiTextureManager::Bind( int which , GLuint texid , TextureMode mode )
{
	int temp = m_CurrentTexture;
	SetActive(which);
	PxTextureManager::Bind(texid,mode,false);
	SetActive(temp);
}
void PxMultiTextureManager::Bind( int which , cstrref name , TextureMode mode )
{
	int temp = m_CurrentTexture;
	SetActive(which);
	PxTextureManager::Bind(name,mode,false);
	SetActive(temp);
}
void PxMultiTextureManager::Unbind( int which )
{
	int temp = m_CurrentTexture;
	SetActive(which);
	PxTextureManager::Unbind();
	SetActive(temp);
}

