#ifndef _PIXELX_PLATFORM_H
#define _PIXELX_PLATFORM_H

#define PVAR_WINDOW_WIN32
//#define PVAR_WINDOW_GLUT

class PxWindow;
class PxPlatform
{
public:
	static PxWindow * CreateAWindow();
};
#endif