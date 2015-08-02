#include "Common.h"
#include "Interfaces.h"

extern HINSTANCE g_hInstance;
void PxEngineRoot::Init(HINSTANCE h)
{
	g_hInstance = h;
	inputRoot.Init();
	soundRoot.Init();
	graphicsRoot.Init();
	physicsRoot.Init();
}

void PxEngineRoot::Close()
{
	graphicsRoot.Close();
}

void PxEngineRoot::Process()
{
	PxGraphicsRoot::MessageLoop();
}

