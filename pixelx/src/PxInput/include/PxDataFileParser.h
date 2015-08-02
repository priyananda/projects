#ifndef _PIXELX_DATAPARSER_H
#define _PIXELX_DATAPARSER_H

#include "PxCommandlist.h"

class PxDataFileParser
{
	static void Process( char * line , PxCommandList * clist );
public:
	static PxCommandList * Parse(cstrref filename);
	static bool Parse(cstrref filename, PxCommandList * pList );
};

#endif

