#ifndef _PIXELX_DATAMANAGER_H
#define _PIXELX_DATAMANAGER_H

#include "PxCommandList.h"

#include <hash_map>
using std::hash_map;

class PxDataFilesManager
{
	static hash_map<string,PxCommandList *> m_map;
public:
	static void Init();
	static void Load(cstrref filename);
	static PxCommandList * Get(cstrref name );
};

#endif

