#include "PxGUISceneRenderer.h"
#include "Interfaces.h"
#include "..\..\PxGraphics\include\PxWindow.h"
#include "..\..\PxInput\include\PxConfiguration.h"
#include "..\..\PxGraphics\include\PxTextureManager.h"

#include "glgooey/core/Rectangle.h"
#include "glgooey/WindowManager.h"
#include "glgooey/PropertyScheme.h"

static bool isShiftPressed()
{
	return (GetKeyState( VK_SHIFT ) & 0x80) != 0;
}
static bool isAltPressed()
{
	return (GetKeyState( VK_LMENU ) & 0x80) != 0;
}
static bool isCtrlPressed()
{
	return (GetKeyState( VK_CONTROL ) & 0x80) != 0;
}

PxGUISceneRenderer::PxGUISceneRenderer(ISceneRegulator * pReg)
:m_pRegulator(pReg),m_pCurrentScene(nullptr){}

bool PxGUISceneRenderer::AcceptScene(IScene * pScene)
{
	return pScene->GetSceneType() == eSceneGUI;
}

void PxGUISceneRenderer::Enter()
{
	PxGraphicsRoot::Switch();
	Gooey::WindowManager::instance().initialize("data\\ui\\fonts\\accid___.ttf", isShiftPressed, isAltPressed, isCtrlPressed);
	Gooey::WindowManager::instance().propertyScheme().load("data\\ui\\skins\\tutskin.xml");
	Gooey::WindowManager::instance().applicationResized(
		PxConfiguration::GetLong("g_screenwidth"),
		PxConfiguration::GetLong("g_screenheight")
	);
	ShowCursor(TRUE);
}

void PxGUISceneRenderer::Exit()
{
	if( m_pCurrentScene != nullptr )
	{
		m_pCurrentScene->Dispose();
		m_pCurrentScene = nullptr;
	}
	PxGraphicsRoot::Restore();
}

void PxGUISceneRenderer::SetScene(IScene * pScene)
{
	if( m_pCurrentScene != nullptr )
	{
		m_pCurrentScene->Dispose();
	}
	m_pCurrentScene = (PxGUIScene *)pScene;
	m_pCurrentScene->Initialize();
}

void PxGUISceneRenderer::HandlePaint(PxWindow *pWnd)
{
	static long sw = PxConfiguration::GetLong("g_screenwidth");
	static long sh = PxConfiguration::GetLong("g_screenheight");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	PxTextureManager::Bind("GUIBG", TextureMode::NoStretch  );
	glBegin( GL_POLYGON );
		glTexCoord2f( 0,0);glVertex2i(0,0);
		glTexCoord2f( 1,0);glVertex2i(sw,0);
		glTexCoord2f( 1,1);glVertex2i(sw,sh);
		glTexCoord2f( 0,1);glVertex2i(0,sh);
	glEnd();
	Gooey::WindowManager::instance().update();
	if( m_pCurrentScene )
		m_pCurrentScene->CustomRender();
	pWnd->Update();
}

void PxGUISceneRenderer::HandleMouse(PxMouseKeyEnum me, int x,int y, bool isUp)
{
	if( me == eMouseLeftClick )
	{
        if(isUp)
            Gooey::WindowManager::instance().onLeftButtonUp(x, y);
        else
            Gooey::WindowManager::instance().onLeftButtonDown(x, y);
	}else{
		if(isUp)
            Gooey::WindowManager::instance().onRightButtonUp(x, y);
        else
            Gooey::WindowManager::instance().onRightButtonDown(x, y);
    }
}
void PxGUISceneRenderer::HandleChar( int scancode )
{
	Gooey::WindowManager::instance().onChar(scancode);
}
void PxGUISceneRenderer::HandleKey( int scancode, PxKeyStateEnum k )
{
	if( scancode == VK_ESCAPE )
		PostQuitMessage(0);
	if( k == eKeyStateDown )
		Gooey::WindowManager::instance().onKeyDown(scancode);
}
void PxGUISceneRenderer::HandleMouseMotion(int x,int y)
{
	Gooey::WindowManager::instance().onMouseMove(x, y);
}
void PxGUISceneRenderer::HandleMouseWheel(bool isUp){}

