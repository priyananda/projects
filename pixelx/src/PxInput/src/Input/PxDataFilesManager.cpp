#include "PxDataFilesManager.h"
#include "PxDataFileParser.h"

static string StdDataFiles[] = 
{
	"data\\textures.pxl",
	"data\\models.pxl",
	"data\\config.pxl",
	"data\\audio.pxl"
};
static const int StdDataFilesCount = 5;
unordered_map<string,PxCommandList *> PxDataFilesManager::m_map;

void PxDataFilesManager::Init()
{
	for( int i = 0 ; i < StdDataFilesCount ; ++i )
		Load( StdDataFiles[i] );
}

void PxDataFilesManager::Load(cstrref filename)
{
	PxCommandList * clist = PxDataFileParser::Parse( filename );
	if( clist == NULL )
		return;
	m_map[ clist->Type ] = clist;
}

PxCommandList * PxDataFilesManager::Get( cstrref filename )
{
	if( m_map.find(filename) != m_map.end() )
		return m_map[filename];
	PxCommandList * clist = PxDataFileParser::Parse( filename );
	if( clist == NULL )
		return NULL;
	m_map[ clist->Type ] = clist;
	return clist;
}

