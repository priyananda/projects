#include "PxGlutWindow.h"
#include "GL/glut.h"
#include "..\..\PxInput\include\PxConfiguration.h"

static PxWindow * g_theWindow = nullptr;

static void __display_func()
{
	g_theWindow->pEventHandler->HandlePaint( g_theWindow );
}
static void __key_func(unsigned char sc,int,int)
{
	g_theWindow->pEventHandler->HandleKey( sc , eKeyStateDown );
}
static void __mouse_func(int button,int state,int x,int y)
{
	g_theWindow->pEventHandler->HandleMouse(
		button == GLUT_LEFT_BUTTON ? eMouseLeftClick : eMouseRightClick,
		x,y,
		state == GLUT_UP ? true:false
	);
}
static void __idle_func()
{
	g_theWindow->pEventHandler->HandlePaint(g_theWindow);
}
void PxGlutWindow::InitWindow( int bpp, int fs )
{
	char * argv[] = {"test.exe","a"};
	int argc = 1;
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize (ScreenWidth, ScreenHeight);
	glutCreateWindow ("PixelX");
	if( fs )
		glutFullScreen();
	g_theWindow = this;
	glutDisplayFunc(__display_func);
	glutKeyboardFunc (__key_func);
	glutMouseFunc(__mouse_func);
	glutIdleFunc(__idle_func);
}

long PxGlutWindow::MessageLoop()
{
	glutMainLoop();
	return 0;
}
void PxGlutWindow::Update()
{
	glutSwapBuffers();
	PxWindow::UpdateFrameRate();
}

void PxGlutWindow::Close()
{
	PostQuitMessage(0);
}

void PxGlutWindow::ShowCursor( bool show )
{
	if(show)
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	else
		glutSetCursor(GLUT_CURSOR_NONE);
}