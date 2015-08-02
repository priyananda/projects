#include "PxTextureManager.h"
#include "PxImageProvider.h"
#include "..\..\PxInput\include\PxDataFilesManager.h"

#define TEXTURE_NOT_LOADED -1

void PxTextureManager::Init()
{
	PxCommandList * clist = PxDataFilesManager::Get( "TEXTURE_LIST" );
	if( clist == NULL )
		return;
	for( PxCommandList::Iterator iter = clist->Commands.begin(); iter != clist->Commands.end(); ++iter )
	{
		if( (*iter)->Command == "tex" )
		{
			string _name = (*iter)->Arguments[0];
			string _path = string("data\\") + (*iter)->Arguments[1];
			if( m_textures.find(_name) == m_textures.end() )
			{
				m_textures[_name] = TEXTURE_NOT_LOADED;
				m_texturepaths[_name] = _path;
			}
		}
	}
}

void PxTextureManager::_LoadTexture( cstrref name )
{
	if( m_textures.find( name ) != m_textures.end() )
		if( m_textures[ name ] == TEXTURE_NOT_LOADED )
			m_textures[ name ] = PxImageProvider::CreateTexture( m_texturepaths[name] , false );
}

void PxTextureManager::LoadAllTextures()
{
	for( map<string,GLuint>::iterator iter = m_textures.begin() ; iter != m_textures.end() ; ++iter )
		_LoadTexture( (*iter).first );
}

GLuint PxTextureManager::GetTextureId(cstrref name)
{
	GLuint texID = 0;
	if( m_textures.find(name) != m_textures.end() )
	{
		_LoadTexture( name );
		texID = m_textures[name];
	}
	return texID;
}
void PxTextureManager::Bind( cstrref name , TextureMode _m, bool bTexEnv)
{
	Bind( GetTextureId(name) , _m , bTexEnv);
}
void PxTextureManager::Bind( GLuint texID , TextureMode mode,bool bTexEnv)
{
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D , texID);
	SetMode(mode,bTexEnv);
}
void PxTextureManager::Unbind()
{
	glBindTexture( GL_TEXTURE_2D , 0 );
}
void PxTextureManager::SetMode(TextureMode mode,bool bTexEnv)
{
	glDisable( GL_TEXTURE_GEN_S );
	glDisable( GL_TEXTURE_GEN_T );
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if(bTexEnv)
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	static GLint sv[4] = { 1,0,1,0 } , tv[4] = {0,-1,1,0};

	if( mode == eTexModeStretchX || mode == eTexModeStretchBoth ){ 
		glTexGeni( GL_S , GL_TEXTURE_GEN_MODE , GL_OBJECT_LINEAR );
		glTexGeniv( GL_S , GL_OBJECT_PLANE , sv );
		glEnable( GL_TEXTURE_GEN_S );
	}
	if( mode == eTexModeStretchY || mode == eTexModeStretchBoth ){
		glTexGeni( GL_T , GL_TEXTURE_GEN_MODE , GL_OBJECT_LINEAR );
		glTexGeniv( GL_T , GL_OBJECT_PLANE , tv );
		glEnable( GL_TEXTURE_GEN_T );
	}
}

void PxTextureManager::Unload( cstrref sname )
{
	if( m_textures.find( sname ) == m_textures.end())
		return;
	glDeleteTextures(1, &m_textures[sname] );
	m_textures.erase( sname );
}

GLuint PxTextureManager::LoadTexture( cstrref name , cstrref path)
{
	m_textures[ name ] = TEXTURE_NOT_LOADED;
	m_texturepaths[ name ] = path;
	return GetTextureId( name );
}
map<string,GLuint> PxTextureManager::m_textures;
map<string,string> PxTextureManager::m_texturepaths;

