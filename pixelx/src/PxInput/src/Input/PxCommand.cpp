#include "PxCommand.h"

void PxCommand::SetArguments( list<string> & args )
{
	if( ArgCount != 0 )
		delete [] Arguments;
	int len = args.size();
	if( len == 0 )
		return;
	Arguments = new string[ len ];
	int i = 0;
	for( list<string>::iterator iter = args.begin(); iter != args.end(); ++iter, ++i )
		Arguments[i] = *iter;
	ArgCount = i;
}

