#include "Interfaces.h"
#include "PxConfiguration.h"
#include "PxDataFilesManager.h"

void PxInputRoot::Init()
{
	PxDataFilesManager::Init();
	PxConfiguration::Init();
}

