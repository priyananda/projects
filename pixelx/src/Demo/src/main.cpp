#include "Interfaces.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprev, PSTR cmdline, int ishow)
{
	PxEngineRoot root;
	root.Init(hInstance);
	root.Process();
	root.Close();
	return 0;
}