#ifndef _PIXELX_STRINGTOK_H
#define _PIXELX_STRINGTOK_H

#include "Common.h"

#include <list>
using std::list;

class PxStringTokenizer
{
public:
	static int Tokenize( cstrref input , list<string> & ret);
};

#endif

