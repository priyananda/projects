#include "PxDataFileParser.h"
#include "PxStringTokenizer.h"

#include <fstream>
using std::ifstream;

list<string> line;

std::unique_ptr<PxCommandList> PxDataFileParser::Parse(cstrref filename)
{
	std::unique_ptr<PxCommandList> clist(new PxCommandList());
	if( ! Parse( filename , clist.get() ) )
		clist = nullptr;
	return clist;
}

static inline bool IsComment(char * buff)
{
	return buff[0] == '#'  || buff[0] == 0;
}

static inline bool IsInclude(char * buff)
{
	int x = _strnicmp( buff , "%include" , 8 );
	return x == 0;
}

static inline string GetIncludeFile(char * buff)
{
	char * start = strchr(buff, '"');
	char * end = strrchr(buff, '"');
	*end = 0;
	return string( start + 1 );
}

bool PxDataFileParser::Parse( cstrref filename , PxCommandList * clist )
{
	char buff[255];

	ifstream fs( filename.c_str() );
	if( ! fs )
		return false;
	while( fs.getline( buff, 254 ))
		Process(buff,clist);
	fs.close();
	return true;
}

void PxDataFileParser::Process( char * buff , PxCommandList * clist )
{
	if( IsInclude(buff) )
	{
		Parse( GetIncludeFile(buff) , clist );
		return;
	}
	PxStringTokenizer::Tokenize( buff, line );
	if(line.front() == "#!TYPE" )
	{
		clist->Type = *(++line.begin());
		return;
	}
	if( IsComment(buff) )
		return;
	
	std::unique_ptr<PxCommand> pcmd ( new PxCommand() );
	pcmd->Command = line.front();
	line.pop_front();
	pcmd->SetArguments( line );
	clist->Commands.push_back(std::move(pcmd));
}

