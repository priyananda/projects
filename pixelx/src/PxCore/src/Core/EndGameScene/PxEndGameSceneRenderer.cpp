#include "PxEndGameSceneRenderer.h"
#include "Interfaces.h"
#include "..\..\PxGraphics\include\PxTextureManager.h"
#include "..\..\PxGraphics\include\PxWindow.h"

extern bool g_debug_win;
static int g_tex_id = 0;
PxEndGameSceneRenderer::PxEndGameSceneRenderer( ISceneRegulator * pReg )
	: m_pRegulator(pReg), m_pCurrentScene(NULL)
{}

bool PxEndGameSceneRenderer::AcceptScene( IScene * p )
{
	return p->GetSceneType() == eSceneEndGame;
}

void PxEndGameSceneRenderer::Enter()
{
	PxGraphicsRoot::Switch();
}

void PxEndGameSceneRenderer::Exit()
{
	PxGraphicsRoot::Restore();
}

void PxEndGameSceneRenderer::SetScene( IScene * pScene )
{
	if( m_pCurrentScene )
		m_pCurrentScene->Dispose();
	m_pCurrentScene = static_cast< PxEndGameScene * >( pScene );
	m_pCurrentScene->Initialize();
	g_tex_id = PxTextureManager::GetTextureId( g_debug_win ? "ENDGAME_WIN" : "ENDGAME_LOSE" );
	PxTextureManager::Bind( g_tex_id, eTexModeNoStretch );
}

void PxEndGameSceneRenderer::HandlePaint(PxWindow * pWindow)
{
	glBegin( GL_QUADS );
		glTexCoord2f( 0, 1 );glVertex2i( 0 , 0 );
		glTexCoord2f( 0, 0 );glVertex2i( 0 , pWindow->ScreenHeight );
		glTexCoord2f( 1, 0 );glVertex2i( pWindow->ScreenWidth , pWindow->ScreenHeight );
		glTexCoord2f( 1, 1 );glVertex2i( pWindow->ScreenWidth , 0 );
	glEnd();
	pWindow->Update();
}
void PxEndGameSceneRenderer::HandleKey( int ScanCode, PxKeyStateEnum keyState )
{
	if( ScanCode == VK_ESCAPE || ScanCode == VK_SPACE)
		PostQuitMessage(0);
}
void PxEndGameSceneRenderer::HandleChar( int charCode ){}
void PxEndGameSceneRenderer::HandleMouse( PxMouseKeyEnum , int x, int y, bool isUp){}
void PxEndGameSceneRenderer::HandleMouseMotion( int x,int y){}
void PxEndGameSceneRenderer::HandleMouseWheel( bool isUp ){}

