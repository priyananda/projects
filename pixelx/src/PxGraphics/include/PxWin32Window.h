#ifndef _PIXELX_WIN32WINDOW
#define _PIXELX_WIN32WINDOW

#include "PxWindow.h"

class PxWin32Window : public PxWindow
{
public:
	HDC DeviceContext;
	HWND WindowHandle;
	HGLRC OpenglContext;
private:
	void	CreateTheFuckingWindow();
	bool	SetupPixelFormat(int bpp);
	void	ChangeToFullScreen();
	void	InitOpenGL(int bpp);
public:
	virtual void	InitWindow(int bpp, int fullscreen);
	virtual long	MessageLoop();
	virtual void	Close();
	virtual void	Update();
	virtual void	ShowCursor(bool);
};

#endif
