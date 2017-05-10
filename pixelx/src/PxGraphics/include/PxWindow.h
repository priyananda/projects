#ifndef _PIXELX_WINDOW_H
#define _PIXELX_WINDOW_H

#include "Common.h"
#include "PxInputEventHandler.h"

class PxWindow
{
	static PxWindow		* pSingleInstance;
public:
	long ScreenWidth;
	long ScreenHeight;
	float FrameInterval;
	float FramesPerSecond;

public:	
	PxWindow(){}
	void	Init( int width, int height, int bpp , bool fullscreen );
	void	SetInputEventHandler(PxInputEventhandler * p);
	virtual long	MessageLoop() = 0 ;
	virtual void	Close() = 0;
	virtual void	Update() = 0;
	virtual void	ShowCursor(bool) = 0;
	
	void	SizeOpenGLScreen();
	void	SaveScreenShot(cstrref filename);
	void	EnableVSync();
protected:
	void	UpdateFrameRate();
	void	InitGL();
	virtual void	InitWindow(int bpp, int fullscreen) = 0;
public:
	static PxWindow * Window();
	PxInputEventhandler * pEventHandler;
};
#endif

