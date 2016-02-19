#pragma once
#include "PxCommandList.h"

#include <unordered_map>
using std::unordered_map;

class PxDataFilesManager
{
	static unordered_map<string, std::unique_ptr<PxCommandList> > m_map;
public:
	static void Init();
	static void Load(cstrref filename);
	static PxCommandList * Get(cstrref name );
};