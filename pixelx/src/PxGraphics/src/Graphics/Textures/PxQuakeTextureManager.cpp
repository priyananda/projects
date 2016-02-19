#include "PxQuakeTextureManager.h"
#include "..\..\PxInput\include\PxDataFilesManager.h"

#define QUAKE_DIR "data/qbase/"

static map<string,string> mapQuakeTex;
static bool bIsInited = false;
static const string shaders[] =
{
	"_trans",
	"_dark",
	"_shiney"
};
static const int shader_size = 3;
void PxQuakeTextureManager::Bind( cstrref name , TextureMode mode, bool bTexEnv)
{
	string path = MapTexturePath( name );
	if( path != "" )
		PxTextureManager::Bind(
			PxTextureManager::LoadTexture( path, path ),
			mode,
			bTexEnv
		);
	else
		PxTextureManager::Unbind();
}
GLuint PxQuakeTextureManager::GetTextureId(cstrref name )
{
	string path = MapTexturePath( name );
	if( path != "" )
		return PxTextureManager::LoadTexture( path, path );
	return 0;
}
void PxQuakeTextureManager::Bind( GLuint texId , TextureMode mode , bool bTexEnv  )
{
	PxTextureManager::Bind( texId , mode , bTexEnv );
}
static bool _FileExists(string name)
{
	WIN32_FIND_DATA lpFindHandle;
	if( ::FindFirstFile( name.c_str(), &lpFindHandle ) == INVALID_HANDLE_VALUE )
		return false;
	return true;
}
string PxQuakeTextureManager::MapTexturePath( cstrref name )
{
	/*
	* Algorithm:
	* 0) use the mapping config file.
	* 1) prefix QUAKE_DIR to path
	* 2) try first with jpg
	* 3) if jpg doesn't exist, try with tga
	* 4) if that also doesn't work, try removing common shader suffixes
	* 5) return "" if not found
	*/
	if( ! bIsInited )
	{
		bIsInited = true;
		PxCommandList * pList = PxDataFilesManager::Get("data\\qtexmap.pxl");
		if( pList )
		{
			for( const auto& spCmd : *pList)
				mapQuakeTex[ spCmd->Command ] = spCmd->Arguments[0];
		}
	}
	if( mapQuakeTex.find( name ) != mapQuakeTex.end() )
		return mapQuakeTex[ name ];
	
	string file = QUAKE_DIR + name + ".jpg";
	if( ::_FileExists( file ) )
		return file;
	
	file = QUAKE_DIR + name + ".tga";
	if( ::_FileExists( file ) )
		return file;

	string exname = QUAKE_DIR + name;
	for( int i = 0 ; i < shader_size ; ++i )
	{
		int idx = exname.find( shaders[i] );
		if( idx > -1 )
			exname.replace( idx , strlen( shaders[i].c_str() ) , "" );
	}

	file = exname + ".jpg";
	if( ::_FileExists( file ) )
		return file;
	
	file = exname + ".tga";
	if( ::_FileExists( file ) )
		return file;

	return "";
}

