#ifndef PIXELX_SHADERMGR
#define PIXELX_SHADERMGR

#include "..\..\PxInput\include\PxShaderParser.h"

class PxShaderManager
{
	static PxShaderParser m_parser;
public:
	static void Init();
};

#endif

