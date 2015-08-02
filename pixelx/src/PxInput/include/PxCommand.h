#ifndef _PIXELX_CMD_H
#define _PIXELX_CMD_H

#include "Common.h"

#include <list>
using std::list;

class PxCommand
{
public:
	string Command;
	string *Arguments;
	int ArgCount;

	PxCommand(): Arguments(NULL),ArgCount(0){}
	void SetArguments( list<string> & args );
	~PxCommand()
	{
		if( ArgCount > 0 )
			delete [] Arguments;
	}
};

#endif

