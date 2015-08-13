#ifndef _PIXELX_DATAMANAGER_H
#define _PIXELX_DATAMANAGER_H

#include "PxCommandList.h"

#include <unordered_map>
using std::unordered_map;

class PxDataFilesManager
{
	static unordered_map<string,PxCommandList *> m_map;
public:
	static void Init();
	static void Load(cstrref filename);
	static PxCommandList * Get(cstrref name );
};

#endif

