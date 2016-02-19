#include "PxGameSceneRenderer.h"
#include "PxGameScene.h"
#include "..\..\PxGraphics\include\PxConsole.h"
#include "..\..\PxGraphics\include\PxTextureManager.h"
#include "Interfaces.h"
#include "..\..\PxGraphics\include\PxTextWriter.h"
#include "..\..\PxInput\include\PxConfiguration.h"
#include "..\..\PxSound\include\PxAudioManager.h"
#include "..\..\PxPhysics\include\PxPointProjectile.h"
#include "..\..\PxGraphics\include\PxExtensionManager.h"
#include "..\..\PxGraphics\include\PxShaderManager.h"
#include "..\..\PxGraphics\include\PxImageProvider.h"
#include <mmsystem.h>

PxPointProjectile * proj;
bool proj_move = true;
int g_debug_tricount = 0;
bool g_debug_collision;
DECLARE_VARF(g_debug_bulletspeed);
DECLARE_VARF(g_debug_wireframe);
DECLARE_VARB(g_debug_timed);
bool g_debug_drawbsp = true;
static DWORD g_startTime = 0;
static int g_minutes = 0;
static int g_seconds = 0;
bool g_debug_win = false;

PxGameSceneRenderer::PxGameSceneRenderer(ISceneRegulator * pReg)
	: m_inited(false), m_console_mode(false), m_sceneRegulator( pReg )
{
}

void PxGameSceneRenderer::Init()
{
	if( m_inited )
		return;
	ASSIGN_VARB(g_debug_collision);
	ASSIGN_VARF(g_debug_bulletspeed) / 1000.0f;
	ASSIGN_VARB(g_debug_timed);
	ASSIGN_VARB(g_debug_drawbsp);
	ASSIGN_VARB(g_debug_wireframe);

	if( ! m_currentWorld )
		m_currentWorld = new PxWorld( "data\\worlds\\first.pxw" );
	m_currentWorld->Initialize();
	m_console = new PxConsole( PxWindow::Window()->ScreenWidth,PxWindow::Window()->ScreenHeight,200 , this);
	PxWindow::Window()->SizeOpenGLScreen();
	m_inited= true;
	PxTextureManager::LoadAllTextures();
	PxShaderManager::Init();
	g_startTime = timeGetTime();
}

void LoadingScreen(float sw, float sh)
{
	PxGraphicsRoot::Switch();
	glColor4f(1,1,1,1);
	glDisable(GL_BLEND);
	PxTextureManager::Bind(	"LOADING", eTexModeNoStretch  );
	glBegin( GL_POLYGON );
		glTexCoord2f( 0,1);glVertex2i(0,0);
		glTexCoord2f( 1,1);glVertex2i((GLint)sw,0);
		glTexCoord2f( 1,0);glVertex2i((GLint)sw,(GLint)sh);
		glTexCoord2f( 0,0);glVertex2i(0,(GLint)sh);
	glEnd();
	PxGraphicsRoot::Restore();
	glFlush();
}
void PxGameSceneRenderer::WriteStuff(float fpsval,float sw, float sh)
{
    static char fps[100];

	DWORD now = timeGetTime();
	DWORD diff = (now - g_startTime) / 1000;
	g_minutes = diff / 60;
	g_seconds = diff % 60;

	PxGraphicsRoot::Switch();
	
	PxTextureManager::Bind( "HUD" , eTexModeNoStretch );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );
	glBegin( GL_POLYGON );
		glTexCoord2f( 0,1);glVertex2i(0,0);
		glTexCoord2f( 1,1);glVertex2i((GLint)sw,0);
		glTexCoord2f( 1,0);glVertex2i((GLint)sw,(GLint)sh);
		glTexCoord2f( 0,0);glVertex2i(0,(GLint)sh);
	glEnd();

	sprintf_s( fps , _countof(fps), "FPS : %2.2f" , fpsval );
	PxTextWriter::Write( int(sw - 400) ,int(sh - 50), fps , 1, 255,255,255 );
	sprintf_s( fps , _countof(fps), "Position: %2.2f, %2.2f ,%2.2f" , m_currentWorld->GetCamera().Position().x,m_currentWorld->GetCamera().Position().y,m_currentWorld->GetCamera().Position().z );
	PxTextWriter::Write( int(sw - 400) ,int(sh - 100), fps , 1, 255,255,255 );
	sprintf_s( fps , _countof(fps), "View: %2.2f, %2.2f ,%2.2f" , m_currentWorld->GetCamera().View().x,m_currentWorld->GetCamera().View().y,m_currentWorld->GetCamera().View().z );
	PxTextWriter::Write( int(sw - 400) ,int(sh - 150), fps , 1, 255,255,255 );
	sprintf_s( fps , _countof(fps), "Triangles Drawn: %d " , m_currentWorld->GetRenderedTrianglesCount() + g_debug_tricount);
	PxTextWriter::Write( int(sw - 400) ,int(sh - 200), fps , 1, 255,255,255 );
	sprintf_s( fps , _countof(fps), "%d " , m_currentWorld->GetHuman().iPlayerAmmo );
	PxTextWriter::Write( 280 ,70, fps , 3, 0,0,255 );
	sprintf_s( fps , _countof(fps), "%d " , m_currentWorld->GetHuman().iPlayerHealth );
	PxTextWriter::Write( 420 ,70, fps , 3, 0,0,255 );
	sprintf_s( fps , _countof(fps), "Frags: %ld/%ld" , m_currentWorld->GetHuman().iFragCount, m_currentWorld->GetWorldFragCount() );
	PxTextWriter::Write( 100 , int(sh - 70), fps , 1, 255,255,255 );
	sprintf_s( fps , _countof(fps), "Time: %2d:%2d" , g_minutes , g_seconds );
	PxTextWriter::Write( 100 , int(sh - 100), fps , 1, 255,255,255 );
	PxGraphicsRoot::Restore();
}
void PxGameSceneRenderer::HandlePaint(PxWindow * pWindow )
{
	g_debug_tricount = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if( ! m_inited )
	{
		PxImageProvider::Reset();
		LoadingScreen(float(pWindow->ScreenWidth), float(pWindow->ScreenHeight));
		pWindow->Update();
		PxAudioManager::Play( "LAUGH" );
		Init();
	}

	if(! m_console_mode )
	{
		glLoadIdentity();
		m_currentWorld->GetCamera().Update(pWindow->FrameInterval);
		m_currentWorld->GetCamera().Look();
	}
	
	if(!g_debug_wireframe)
		glPolygonMode( GL_FRONT_AND_BACK , GL_FILL );
	else
		glPolygonMode( GL_FRONT_AND_BACK , GL_LINE );
	
	if( proj ){
		if( proj_move )
			proj->Move();
		proj->Render();
	}
	m_currentWorld->Render(pWindow);
	WriteStuff( pWindow->FramesPerSecond,(float)pWindow->ScreenWidth, (float)pWindow->ScreenHeight );
	if( m_console_mode )
	{
		PxGraphicsRoot::Switch();
		m_console->Update(long(pWindow->FrameInterval*1000));
		PxGraphicsRoot::Restore();
	}
	glDisable( GL_LIGHTING );
	glFlush();
	pWindow->Update();
	CheckForEndGame();
}

string GetShotFileName()
{
	static char buff[30];
	for( int i = 0; i < 99 ; ++i )
	{
		sprintf_s(buff, _countof(buff), "data\\shots\\shot%d.tga" , i );
		FILE * fp = nullptr;
		fopen_s(&fp, buff, "rb");
		if( fp == nullptr )
			return string(buff);
		else
			fclose(fp);
	}
	return "data\\shots\\shot01.tga";
}
void PxGameSceneRenderer::HandleKey( int ScanCode , PxKeyStateEnum key )
{
	if( ScanCode == VK_ESCAPE )
	{
		PostQuitMessage(0);
		return;
	}
	if( ScanCode == VK_SPACE )
	{
		m_currentWorld->GetCamera().Jump();
	}
	if( ScanCode == VK_F11 && key == eKeyStateDown )
	{
		PxWindow::Window()->SaveScreenShot( GetShotFileName() );
		return;
	}
	if( ScanCode == VK_NUMPAD0 && key == eKeyStateDown )
	{
		HandleCommand( "clip" );
		return;
	}
	if( ScanCode == PxConfiguration::MapKey(eKeyConsole) && key == eKeyStateDown )
	{
		m_console_mode = ! m_console_mode;
		m_console->Toggle();
		return;
	}
	if( m_console_mode )
	{
		m_console->TranslateKey( ScanCode , true );
	}
	switch( key )
	{
		case eKeyStateDown:
			PxConfiguration::SetKey( ScanCode );
			break;
	}
}

void PxGameSceneRenderer::HandleMouse( PxMouseKeyEnum which, int x, int y, bool isUp)
{
	if( isUp || m_currentWorld->GetHuman().iPlayerAmmo == 0)
		return;
	if( which == eMouseRightClick )
	{
		proj_move = ! proj_move;
		return;
	}
	--m_currentWorld->GetHuman().iPlayerAmmo;
	PxAudioManager::Play( "SHOT" );
	if( proj )
		delete proj;
	proj = new PxPointProjectile(m_currentWorld->GetCamera().Position() , m_currentWorld->GetCamera().View() - m_currentWorld->GetCamera().Position() , g_debug_bulletspeed );
}
void PxGameSceneRenderer::HandleChar( int charCode )
{
	if( m_console_mode )
	{
		m_console->HandleKey(eKeyStateDown,charCode);
	}
}

int PxGameSceneRenderer::HandleCommand( const char * cmd )
{
	if( _stricmp( cmd, "wireframe" ) == 0 )
		g_debug_wireframe = !g_debug_wireframe;
	if( _stricmp( cmd, "q!" ) == 0 )
		PostQuitMessage(0);
	if( _stricmp( cmd, "giveall" ) == 0 )
	{
		m_currentWorld->GetHuman().iPlayerHealth = 100;
		m_currentWorld->GetHuman().iPlayerAmmo = 42;
	}
	if(_stricmp( cmd , "resettime" ) == 0 )
		g_startTime = timeGetTime();	
	if(_stricmp( cmd, "drawbsp" ) == 0 )
		g_debug_drawbsp = !g_debug_drawbsp;
	if(_stricmp( cmd, "clip" ) == 0 )
		g_debug_collision = !g_debug_collision;
	if( strstr( cmd, "pos" ) )
	{
		float x,y,z;
		sscanf_s( cmd , "pos %f %f %f" , 
			&x,
			&y,
			&z
		);
		m_currentWorld->GetCamera().PositionCamera(
			x,y,z,
			x + 10,y,z,
			0,1,0
		);
	}
	if( cmd[0] == '+' )
	{
		char which;
		float x,y,z,det;
		sscanf_s( cmd , "+%c %f" ,
			&which, 1,
			&det
		);
		x = m_currentWorld->GetCamera().Position().x;
		y = m_currentWorld->GetCamera().Position().y;
		z = m_currentWorld->GetCamera().Position().z;
		switch( which )
		{
			case 'x': x += det;break;
			case 'y': y += det;break;
			case 'z': z += det;break;
		}
		m_currentWorld->GetCamera().PositionCamera(
			x,y,z,
			x + 10,y,z,
			0,1,0
		);
	}
	return 0;
}
void PxGameSceneRenderer::Enter()
{
	PxWindow::Window()->ShowCursor(false);
}
bool PxGameSceneRenderer::AcceptScene( IScene * pScene)
{
	return pScene->GetSceneType() == eSceneGame;
}
void PxGameSceneRenderer::SetScene( IScene * scene)
{
	PxGameScene * pScene = static_cast< PxGameScene *>(scene);
	m_currentWorld = pScene->World;
}
void PxGameSceneRenderer::Exit()
{
	PxWindow::Window()->ShowCursor(true);
}

void PxGameSceneRenderer::CheckForEndGame()
{
	if( !g_debug_timed )
		return;
	if( g_minutes >= 2 )
	{
		g_debug_win = false;
		m_sceneRegulator->Signal( eScNamedScene , "endgame" );
	}
	if( m_currentWorld->GetHuman().iFragCount >= m_currentWorld->GetWorldFragCount() )
	{
		g_debug_win = true;
		m_sceneRegulator->Signal( eScNamedScene , "endgame" );
	}
}

