#include "PxIntrosceneRenderer.h"
#include "..\..\PxGraphics\include\PxWindow.h"
#include "Interfaces.h"
#include "..\..\PxGraphics\include\PxTextureManager.h"
#include "..\..\PxGraphics\include\PxTextWriter.h"
#include "..\..\PxSound\include\PxAudioManager.h"

static float screenWidth, screenHeight;
static bool first = true;
#define TEX_BUFF_WIDTH 512

PxIntroSceneRenderer::PxIntroSceneRenderer(ISceneRegulator * pReg)
:m_pCurrentScene(nullptr)
{
	m_pRegulator = pReg;
}
void PxIntroSceneRenderer::Enter()
{
	glClearColor(0.0f ,0.0f ,0.0f ,0.0f);
	
	CreateBlurTexture();
	CreateDisplayList();

	screenWidth = float(PxWindow::Window()->ScreenWidth);
	screenHeight = float(PxWindow::Window()->ScreenHeight);

	glViewport(0, 0, PxWindow::Window()->ScreenWidth, PxWindow::Window()->ScreenHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, screenWidth / screenHeight, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	PxAudioManager::Loop( "INTRO" );
}
bool PxIntroSceneRenderer::AcceptScene( IScene * scene)
{
	return scene->GetSceneType() == eSceneIntro;
}
void PxIntroSceneRenderer::SetScene( IScene * scene)
{
	if( m_pCurrentScene != nullptr )
		m_pCurrentScene->Dispose();
	m_pCurrentScene = static_cast< PxIntroScene * > (scene);
	m_pCurrentScene->Initialize();
}
void PxIntroSceneRenderer::Exit()
{
	glViewport(0, 0, PxWindow::Window()->ScreenWidth, PxWindow::Window()->ScreenHeight);
	glColor3f(1,1,1);
	glDisable( GL_BLEND );
}
void PxIntroSceneRenderer::HandleKey( int ScanCode, PxKeyStateEnum keyState )
{
	if( ScanCode == VK_ESCAPE )
		PostQuitMessage(0);
	if( ScanCode == VK_SPACE )
		m_pRegulator->Signal( eScNamedScene , "choosemap" );
}
void PxIntroSceneRenderer::HandleChar( int charCode ){}
void PxIntroSceneRenderer::HandleMouse( PxMouseKeyEnum , int x, int y, bool isUp){}
void PxIntroSceneRenderer::HandlePaint( PxWindow * window)
{
	if( first )
	{
		m_ElapsedTime = m_Start = GetTickCount();
		first = false;
	}
	DWORD last = m_ElapsedTime;
	m_ElapsedTime = GetTickCount() - m_Start;
	m_ElapsedTime = (last + m_ElapsedTime)/2;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0, 0.0,-8);
	glRotatef((float)m_ElapsedTime/8, 1.0f, 0, 0);
	glRotatef((float)m_ElapsedTime/12, 0, 1.0f, 0);

	glViewport(0, 0, TEX_BUFF_WIDTH, TEX_BUFF_WIDTH);
	RenderScene();

	glBindTexture(GL_TEXTURE_2D, m_BlurTex);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, TEX_BUFF_WIDTH, TEX_BUFF_WIDTH, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(
		(PxWindow::Window()->ScreenWidth - TEX_BUFF_WIDTH ) / 2,
		(PxWindow::Window()->ScreenHeight - TEX_BUFF_WIDTH ),
		TEX_BUFF_WIDTH,
		TEX_BUFF_WIDTH
		);
	RenderScene();
	RenderLogo();
	glFlush();
	window->Update();
}
void PxIntroSceneRenderer::HandleMouseMotion( int x,int y){}
void PxIntroSceneRenderer::HandleMouseWheel( bool isUp ){}

void PxIntroSceneRenderer::CreateBlurTexture()
{
	void * pData = malloc(TEX_BUFF_WIDTH*TEX_BUFF_WIDTH*3);
	memset( pData , 0 , TEX_BUFF_WIDTH*TEX_BUFF_WIDTH*3 );
	glGenTextures(1, &m_BlurTex);
	glBindTexture(GL_TEXTURE_2D, m_BlurTex);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, TEX_BUFF_WIDTH, TEX_BUFF_WIDTH, 0, GL_RGB, GL_UNSIGNED_BYTE, pData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	free(pData);
}

void PxIntroSceneRenderer::CreateDisplayList()
{
	m_DispList = glGenLists(1);
	glNewList(m_DispList, GL_COMPILE);
	PxTextureManager::Bind( "INTROLOGO" , TextureMode::NoStretch );
	glBegin(GL_QUADS);
	// Front Face
	glTexCoord2f(1.0, 1.0); glVertex3f(-1.0, -1.0,  1.0);
	glTexCoord2f(0.0, 1.0); glVertex3f( 1.0, -1.0,  1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f( 1.0,  1.0,  1.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-1.0,  1.0,  1.0);
	// Back Face
	glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, -1.0, -1.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-1.0,  1.0, -1.0);
	glTexCoord2f(0.0, 1.0); glVertex3f( 1.0,  1.0, -1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f( 1.0, -1.0, -1.0);
	// Top Face
	glTexCoord2f(0.0, 1.0); glVertex3f(-1.0,  1.0, -1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1.0,  1.0,  1.0);
	glTexCoord2f(1.0, 0.0); glVertex3f( 1.0,  1.0,  1.0);
	glTexCoord2f(1.0, 1.0); glVertex3f( 1.0,  1.0, -1.0);
	// Bottom Face
	glTexCoord2f(1.0, 1.0); glVertex3f(-1.0, -1.0, -1.0);
	glTexCoord2f(0.0, 1.0); glVertex3f( 1.0, -1.0, -1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f( 1.0, -1.0,  1.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, -1.0,  1.0);
	// Right face
	glTexCoord2f(1.0, 0.0); glVertex3f( 1.0, -1.0, -1.0);
	glTexCoord2f(1.0, 1.0); glVertex3f( 1.0,  1.0, -1.0);
	glTexCoord2f(0.0, 1.0); glVertex3f( 1.0,  1.0,  1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f( 1.0, -1.0,  1.0);
	// Left Face
	glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, -1.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, -1.0,  1.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-1.0,  1.0,  1.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1.0,  1.0, -1.0);
	glEnd();
	glEndList();
}

void PxIntroSceneRenderer::RenderScene()
{
	glPushMatrix();
	glDisable(GL_DEPTH_TEST);           // disable Depth testing
	glEnable(GL_BLEND);                 // enable blending

	// set the previous scene to be 1-1/frames the brightness give frames amount of blur
	glColor4f(1.0, 1.0, 1.0, 1.0f - 1.0f/(float)FRAMES);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	// go to orthogonal view
	glLoadIdentity();
	glOrtho( 0, screenWidth, screenHeight, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Display the previous rendered scene
	glBindTexture(GL_TEXTURE_2D, m_BlurTex);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); 
	glVertex2f(0, 0);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(0, screenHeight);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(screenWidth, screenHeight);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(screenWidth, 0);
	glEnd();
	// go back to 3D view
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);          // disable blending

	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.3f, 0.0f, 0.0f);
	glCallList(m_DispList);

	//glTranslatef(2.6, 0.0, 0.0);
	//glCallList(DispList);
	glPopMatrix();
}

void PxIntroSceneRenderer::RenderLogo()
{
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glOrtho( 0, screenWidth, 0, screenHeight, 0, 1);
	glViewport(0, 0, (long)screenWidth, (long)screenHeight);
	glDisable( GL_BLEND );
	PxTextureManager::Bind( "INTRO_PXLOGO" , TextureMode::NoStretch );
	glBegin( GL_QUADS );
	glTexCoord2f(0,1);glVertex2f(0,20);
	glTexCoord2f(1,1);glVertex2f(screenWidth,20);
	glTexCoord2f(1,0);glVertex2f(screenWidth,120);
	glTexCoord2f(0,0);glVertex2f(0,120);
	glEnd();

	glPopMatrix();

	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();
}

