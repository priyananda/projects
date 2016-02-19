#include "PxDataFilesManager.h"
#include "PxDataFileParser.h"

static string StdDataFiles[] = 
{
	"data\\textures.pxl",
	"data\\models.pxl",
	"data\\config.pxl",
	"data\\audio.pxl"
};

unordered_map<string, std::unique_ptr<PxCommandList>> PxDataFilesManager::m_map;

void PxDataFilesManager::Init()
{
	for (const auto& strFileName : StdDataFiles)
		Load(strFileName);
}

void PxDataFilesManager::Load(cstrref filename)
{
	std::unique_ptr<PxCommandList> clist = PxDataFileParser::Parse( filename );
	if( clist == nullptr )
		return;
	m_map[ clist->Type ] = std::move(clist);
}

PxCommandList * PxDataFilesManager::Get( cstrref filename )
{
	if( m_map.find(filename) != m_map.end() )
		return m_map[filename].get();
	std::unique_ptr<PxCommandList> clist = PxDataFileParser::Parse( filename );
	if( clist == nullptr )
		return nullptr;
	m_map[ clist->Type ] = std::move(clist);
	return clist.get();
}

