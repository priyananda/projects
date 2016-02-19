#pragma once
#include "PxCommandlist.h"

class PxDataFileParser
{
	static void Process( char * line , PxCommandList * clist );
public:
	static std::unique_ptr<PxCommandList> Parse(cstrref filename);
	static bool Parse(cstrref filename, PxCommandList * pList );
};