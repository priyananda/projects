#include "PxWindow.h"
#include "..\..\PxInput\include\PxConfiguration.h"
#include "..\..\PxCore\include\PxPlatform.h"
#include <mmsystem.h>

// Singleton Implementation
PxWindow * PxWindow::pSingleInstance = NULL;

PxWindow * PxWindow::Window()
{
	if( pSingleInstance == NULL )
		pSingleInstance = PxPlatform::CreateAWindow();
	return pSingleInstance;
}

void PxWindow::Init( int width, int height, int bpp , bool fullscreen)
{
	ScreenHeight = height;
	ScreenWidth = width;
	InitWindow(bpp,fullscreen);
	InitGL();
}

void PxWindow::SetInputEventHandler( PxInputEventhandler * p )
{
	pEventHandler = p;
}

void PxWindow::UpdateFrameRate()
{
	static float framesPerSecond    = 0.0f;		// This will store our fps
    static float lastTime			= timeGetTime() * 0.001f;		// This will hold the time from the last frame
	static float frameTime			= timeGetTime() * 0.001f;		// This stores the last frame's time

	float currentTime = timeGetTime() * 0.001f;				
	FrameInterval = currentTime - frameTime;
	frameTime = currentTime;
    ++framesPerSecond;

    if( currentTime - lastTime > 1.0f )
    {
	    lastTime = currentTime;
		FramesPerSecond = framesPerSecond;
        framesPerSecond = 0;
    }
}

void PxWindow::SaveScreenShot(cstrref filename)
{
	FILE * file;
	int i  = 0;
	
	PxLog::LogMessage("Saving ScreenShot %s", filename.c_str() );
	
	GLubyte		TGAheader[12]={0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};	//Uncompressed TGA header
	GLubyte		infoHeader[6];

	unsigned char * data=new unsigned char[4*ScreenWidth*ScreenHeight];
	if(!data)
	{
		PxLog::LogMessage("Unable to allocate memory for screen data");
		return;
	}

	//read in the screen data
	glReadPixels(0, 0, ScreenWidth, ScreenHeight, GL_RGBA, GL_UNSIGNED_BYTE, data);

	//data needs to be in BGR format
	//swap b and r
	for(i=0; i<(int)ScreenWidth*ScreenHeight*4; i+=4)
	{	
		//repeated XOR to swap bytes 0 and 2
		data[i] ^= data[i+2] ^= data[i] ^= data[i+2];
	}
	
	//open the file
	file = fopen(filename.c_str(), "wb");

	//save header
	fwrite(TGAheader, 1, sizeof(TGAheader), file);

	//save info header
	infoHeader[0]=(ScreenWidth & 0x00FF);
	infoHeader[1]=(ScreenWidth & 0xFF00) >> 8;
	infoHeader[2]=(ScreenHeight & 0x00FF);
	infoHeader[3]=(ScreenHeight & 0xFF00) >> 8;
	infoHeader[4]=32;
	infoHeader[5]=0;

	//save info header
	fwrite(infoHeader, 1, sizeof(infoHeader), file);

	//save the image data
	fwrite(data, 1,ScreenWidth*ScreenHeight*4, file);
	
	fclose(file);
	
	PxLog::LogMessage("Saved Screenshot: %s", filename.c_str() );
	return;
}

void PxWindow::SizeOpenGLScreen()			// Initialize The GL Window
{
	DEFINE_VARF(w_fov_angle);
	DEFINE_VARF(w_fov_min);
	DEFINE_VARF(w_fov_max);

	if (ScreenHeight==0)
		ScreenHeight=1;
	glViewport(0,0,ScreenWidth,ScreenHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(
		w_fov_angle,
		(GLfloat)ScreenWidth/(GLfloat)ScreenHeight,
		w_fov_min,
		w_fov_max
	);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void PxWindow::InitGL()
{
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
	glHint( GL_PERSPECTIVE_CORRECTION_HINT , GL_NICEST );
	glClearColor(0,0,0,1);
	glDepthFunc(GL_LESS);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
}

#include "PxExtensionManager.h"
void PxWindow::EnableVSync()
{
	DEFINE_VARB(g_vsync);
	if( PxExtensionManager::IsEnabled( EXT_SWAPCONTROL ) && g_vsync )
	{
		wglSwapIntervalEXT(0);
	}
}

