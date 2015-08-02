#ifndef _PIXELX_IPEVTHDLR
#define _PIXELX_IPEVTHDLR

enum PxKeyStateEnum
{
	eKeyStatePressed,
	eKeyStateUp,
	eKeyStateDown
};

enum PxMouseKeyEnum
{
	eMouseLeftClick,
	eMouseRightClick,
	eMouseLeftDoubleClick,
	eMouseRightDoubleClick
};

class PxWindow;
class PxInputEventhandler
{
public:
	virtual void HandleKey( int ScanCode, PxKeyStateEnum keyState ) = 0;
	virtual void HandleChar( int charCode ) = 0;
	virtual void HandleMouse( PxMouseKeyEnum , int x, int y, bool isUp) = 0;
	virtual void HandlePaint( PxWindow *) = 0;
	virtual void HandleMouseMotion( int x,int y) = 0;
	virtual void HandleMouseWheel( bool isUp ) = 0;
};
#endif