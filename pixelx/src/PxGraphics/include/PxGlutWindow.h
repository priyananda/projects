#ifndef _PIXELX_GLUTWINDOW
#define _PIXELX_GLUTWINDOW

#include "PxWindow.h"

class PxGlutWindow : public PxWindow
{
private:
	void	InitOpenGL(int bpp);

	virtual void	InitWindow(int bpp, int fullscreen);
	virtual long	MessageLoop();
	virtual void	Close();
	virtual void	Update();
	virtual void	ShowCursor(bool);
};
#endif