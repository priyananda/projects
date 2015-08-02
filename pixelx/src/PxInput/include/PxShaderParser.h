#ifndef PIXELX_SHADERPARSER_H
#define PIXELX_SHADERPARSER_H

#include "PxCommandList.h"

#include <map>
using std::map;
#include <vector>
using std::vector;

class PxShaderData
{
public:
	string Name;
	PxCommandList Commands;
	vector< PxCommandList > Stages;

	PxShaderData( cstrref name = "" ) : Name(name){}
};
class PxShaderParser
{
	map<string,PxShaderData> m_shaders;
	FILE * m_file;

	string getNextToken(bool ignoreNewline);
	bool ignoreWhiteSpace(bool ignorenl);
	void _ReadShaders();
public:
	void Parse( cstrref filename );
	typedef map<string,PxShaderData>::iterator Iterator;
    const PxShaderData & operator [] ( cstrref name );
	Iterator begin(){ return m_shaders.begin(); }
	Iterator end(){ return m_shaders.end(); }
};

#define FOR_EACH_SHADER(iter,shaders)	\
	for( PxShaderParser::Iterator iter = shaders.begin(); iter != shaders.end() ; ++iter )

#endif

