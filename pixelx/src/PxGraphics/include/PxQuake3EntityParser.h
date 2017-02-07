#ifndef _PIXELX_ENTITYPARSER_H
#define _PIXELX_ENTITYPARSER_H

#include "../../PxPhysics/include/PxVector.h"

#include <map>
using std::map;

#include <vector>
using std::vector;

class PxQuake3Entity
{
	map< string , string> m_Params;
public:
	string ClassName;
	PxVector Origin;

	void AddParam( cstrref name , cstrref value );
	string operator []( cstrref name );
};

typedef vector< PxQuake3Entity > PxQuake3EntityCollection;

class PxQuake3EntityParser
{
public:
	static void Parse( cstrref filename , PxQuake3EntityCollection & coll );
	static void Parse( FILE * file , PxQuake3EntityCollection & coll );
};
#endif

