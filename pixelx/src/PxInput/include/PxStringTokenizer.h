#pragma once
#include "Common.h"

#include <list>
using std::list;

class PxStringTokenizer
{
public:
	static int Tokenize( cstrref input , list<string> & ret);
};
