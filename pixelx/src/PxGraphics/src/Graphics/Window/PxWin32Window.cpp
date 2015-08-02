#include "PxWin32Window.h"
#include "..\..\PxInput\include\PxConfiguration.h"

static	LRESULT CALLBACK MyFuckedUpWinProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam);
extern HINSTANCE g_hInstance;

void PxWin32Window::InitWindow( int bpp, int fs )
{
	CreateTheFuckingWindow();
	InitOpenGL(bpp);
	if( fs )
		ChangeToFullScreen();
}

void PxWin32Window::ChangeToFullScreen()
{
	DEVMODE dmSettings;
	memset(&dmSettings,0,sizeof(dmSettings));
	if(!EnumDisplaySettings(NULL,-1,&dmSettings))
	{
		MessageBox(NULL, "Could Not Enum Display Settings", "Error", MB_OK);
		return;
	}
	dmSettings.dmPelsWidth	= ScreenWidth;
	dmSettings.dmPelsHeight	= ScreenHeight;
	dmSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
	if(ChangeDisplaySettings(&dmSettings, 4) != DISP_CHANGE_SUCCESSFUL)
	{
		MessageBox(NULL, "Display Mode Not Compatible", "Error", MB_OK);
		PostQuitMessage(0);
	}
}
void PxWin32Window::CreateTheFuckingWindow()
{
	WNDCLASS wndclass;
	
	memset(&wndclass, 0, sizeof(WNDCLASS));
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = MyFuckedUpWinProc;
	wndclass.hInstance = g_hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH) (COLOR_WINDOW+1);
	wndclass.lpszClassName = "KickMyAss";
	
	RegisterClass(&wndclass);
	
	DWORD dwStyle = WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	
	ShowCursor(FALSE);

	RECT rWindow;
	rWindow.left	= 0;
	rWindow.right	= ScreenWidth;
	rWindow.top	    = 0;
	rWindow.bottom	= ScreenHeight;

	AdjustWindowRect( &rWindow, dwStyle, false);

	WindowHandle = CreateWindow(
		"KickMyAss", "ShenoyIsGod", dwStyle, 0, 0,
		rWindow.right  - rWindow.left, rWindow.bottom - rWindow.top, 
		NULL, NULL, g_hInstance, NULL
	);

	ShowWindow(WindowHandle, SW_SHOWNORMAL);
	UpdateWindow(WindowHandle);
	SetFocus(WindowHandle);
}

bool PxWin32Window::SetupPixelFormat(int BitsPerPixel)
{ 
    PIXELFORMATDESCRIPTOR pfd;
    int pixelformat;
 
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;

    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER; 
    pfd.dwLayerMask = PFD_MAIN_PLANE;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = BitsPerPixel;
    pfd.cDepthBits = BitsPerPixel;
    pfd.cAccumBits = 0;
    pfd.cStencilBits = 0;
 
    if ((pixelformat = ChoosePixelFormat(DeviceContext, &pfd)) == FALSE ) 
    { 
        MessageBox(NULL, "ChoosePixelFormat failed", "Error", MB_OK); 
        return FALSE; 
    } 
    if (SetPixelFormat(DeviceContext, pixelformat, &pfd) == FALSE) 
    { 
        MessageBox(NULL, "SetPixelFormat failed", "Error", MB_OK); 
        return FALSE; 
    } 
    return TRUE;
}

void PxWin32Window::InitOpenGL(int bpp) 
{  
	DeviceContext = GetDC(WindowHandle);

	if (!SetupPixelFormat(bpp))
        PostQuitMessage (0);
	OpenglContext = wglCreateContext(DeviceContext);
	wglMakeCurrent(DeviceContext, OpenglContext);
	SizeOpenGLScreen();
}
long PxWin32Window::MessageLoop()
{
	MSG msg;
	while(true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
			if(msg.message == WM_QUIT)
				break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
		else
			pEventHandler->HandlePaint( this );
	}
	return 0;
}
void PxWin32Window::Close()
{
	if (OpenglContext)											
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(OpenglContext);
	}
	if (DeviceContext)
		ReleaseDC(WindowHandle, DeviceContext);
	ChangeDisplaySettings(NULL,0);
	ShowCursor(TRUE);
	UnregisterClass("KickMyAss", g_hInstance);
	PostQuitMessage(0);
}

void PxWin32Window::Update()
{
	SwapBuffers( DeviceContext );
	UpdateFrameRate();
}
void PxWin32Window::ShowCursor( bool show )
{
	::ShowCursor( show ? TRUE : FALSE );
}
LRESULT CALLBACK MyFuckedUpWinProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LONG    lRet = 0; 
    PAINTSTRUCT    ps;

	PxWindow * pWindow = PxWindow::Window();
    switch (uMsg)
	{ 
		case WM_PAINT:
			BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;
		case WM_KEYDOWN:
			pWindow->pEventHandler->HandleKey( wParam , eKeyStateDown );
			break;
		case WM_KEYUP:
			//pWindow->pEventHandler->HandleKey( wParam , eKeyStateUp );
			break;
		case WM_CHAR:
			pWindow->pEventHandler->HandleChar( wParam );
			break;
		case WM_CLOSE:
			PostQuitMessage(0);
			break;
		case WM_LBUTTONDOWN:
			pWindow->pEventHandler->HandleMouse( eMouseLeftClick,LOWORD(lParam),HIWORD(lParam),false );
			break;
		case WM_LBUTTONUP:
			pWindow->pEventHandler->HandleMouse( eMouseLeftClick,LOWORD(lParam),HIWORD(lParam),true );
			break;
		case WM_RBUTTONDOWN:
			pWindow->pEventHandler->HandleMouse( eMouseRightClick,LOWORD(lParam),HIWORD(lParam),false );
			break;
		case WM_RBUTTONUP:
			pWindow->pEventHandler->HandleMouse( eMouseRightClick,LOWORD(lParam),HIWORD(lParam),true );
			break;
		case WM_MOUSEMOVE:
			//pWindow->pEventHandler->HandleMouseMotion( LOWORD(lParam),HIWORD(lParam) );
			break;
		case 0x020A:
			pWindow->pEventHandler->HandleMouseWheel( ((short) HIWORD (wParam)) > 0 );
			break;
		default:
			lRet = DefWindowProc (hWnd, uMsg, wParam, lParam);
			break; 
    } 
	return lRet;
}
