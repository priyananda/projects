#ifndef _PIXELX_CMDLIST_H
#define _PIXELX_CMDLIST_H
#include "PxCommand.h"

#include <list>
using std::list;

class PxCommandList
{
public:
	string Type;
	list<PxCommand *> Commands;
	~PxCommandList();

	typedef list<PxCommand *>::iterator Iterator;
};

#define FOR_EACH_CLIST(pList,iter)	\
	for( PxCommandList::Iterator iter = pList->Commands.begin();	\
		iter != pList->Commands.end();								\
		++iter														\
	)

#endif

