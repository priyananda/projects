#include "..\..\PxInput\include\PxConfiguration.h"
#include "Interfaces.h"
#include "PxTextWriter.h"
#include "PxModelManager.h"
#include "PxExtensionManager.h"
#include "PxWindow.h"
#include "..\..\PxCore\include\PxSceneRegulator.h"
#include "PxTextureManager.h"
#include "PxImageProvider.h"

PxWindow * PxGraphicsRoot::Window;

#include "..\..\PxCore\include\PxGameScene.h"
#include "..\..\PxCore\include\PxWorld.h"
void SetStartState(PxSceneRegulator * pRegulator)
{
	char buff[100] = "intro";
	LPSTR pCmd = GetCommandLine();
	if( pCmd == NULL || pCmd[0] == 0 )
		return;
	char * pArg;
	pArg = strstr( pCmd, "--map" );
	if( pArg != NULL && *pArg != 0 )
	{
		sscanf_s(pArg,"--map=%s", buff, sizeof(buff));
		PxGameScene * pGameScene = new PxGameScene("game");
		PxWorld * theWorld = new PxWorld;
		theWorld->Deserialize( string("data\\worlds\\") + buff );
		pGameScene->World = theWorld;
		pRegulator->AddScene( pGameScene );
	}
	pArg = strstr( pCmd, "--start-state" );
	if( pArg != NULL && *pArg != 0)
		sscanf_s(pArg,"--start-state=%s" , buff, sizeof(buff));
	pRegulator->Signal( eScNamedScene , buff );
}
void PxGraphicsRoot::Init()
{
	Window = PxWindow::Window();
	Window->Init(
		PxConfiguration::GetLong("g_screenwidth"),
		PxConfiguration::GetLong("g_screenheight"),
		PxConfiguration::GetLong("g_bpp"),
		PxConfiguration::GetLong("g_debug_window" ) == 0
	);
	PxExtensionManager::Init();
	PxImageProvider::Init();
	PxTextureManager::Init();
	PxTextWriter::Init();
	PxModelManager::Init();
	PxSceneRegulator * pRegulator = new PxSceneRegulator();
	Window->EnableVSync();
	SetStartState(pRegulator);
}

void PxGraphicsRoot::Switch()
{
	glPushAttrib( GL_COLOR_BUFFER_BIT|GL_ENABLE_BIT );
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(0,Window->ScreenWidth,0, Window->ScreenHeight,-1,1);		// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void PxGraphicsRoot::Restore()
{
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDisable(GL_BLEND);
	glPopAttrib();
}

void PxGraphicsRoot::MessageLoop()
{
	Window->MessageLoop();
}

void PxGraphicsRoot::Close()
{
	Window->Close();
}

