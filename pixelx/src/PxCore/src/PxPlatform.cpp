#include "PxPlatform.h"
#include "..\..\PxGraphics\include\PxWin32Window.h"
#include "..\..\PxGraphics\include\PxGlutWindow.h"

PxWindow * PxPlatform::CreateAWindow()
{
	//#ifdef PVAR_WINDOW_WIN32
		return new PxWin32Window();
	//#endif
	//#ifdef PVAR_WINDOW_GLUT
	//	return new PxGlutWindow();
	//#endif
	
}