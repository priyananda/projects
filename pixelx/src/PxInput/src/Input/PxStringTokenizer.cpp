#include "PxStringTokenizer.h"

int PxStringTokenizer::Tokenize(cstrref input, list<string> & ret)
{
	static char curr[256];
	
	int pos = 0 , len = input.length() , clength = 0;

	if( len == 0 )
		return 0;

	ret.clear();
    curr[0] = 0;

	while( pos < len )
	{
		while(pos < len && isspace( input[pos] ))++pos;
		while(pos < len && !isspace( input[pos] ))
			curr[clength++] = input[pos++];
		curr[clength] = 0;
		if( clength > 0 )
			ret.push_back( curr );
		clength = 0;
	}
	return ret.size();
}

