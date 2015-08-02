#ifndef _PIXELX_DIRECTOR_H
#define _PIXELX_DIRECTOR_H

#include "PxWorld.h"
#include "..\..\PxGraphics\include\PxConsoleCommandHandler.h"
#include "ISceneRenderer.h"

class PxConsole;

class PxGameSceneRenderer : 
	public ISceneRenderer,
	public PxConsoleCommandHandler
{
	PxWorld * m_currentWorld;
	bool m_inited;
	bool m_console_mode;
	PxConsole * m_console;
	ISceneRegulator * m_sceneRegulator;

	void CheckForEndGame();
public:
	PxGameSceneRenderer(ISceneRegulator * pReg);
	void Init();

	void WriteStuff(float fpsval,float sw, float sh);

	void HandleKey(int scancode, PxKeyStateEnum eKey );
	void HandleMouse( PxMouseKeyEnum , int x, int y, bool isUp);
	void HandlePaint( PxWindow * p );
	void HandleChar( int charCode );
	void HandleMouseMotion( int x,int y){}
	void HandleMouseWheel( bool isUp ){}
	
	int HandleCommand( const char * );

	void Enter();
	bool AcceptScene( IScene * );
	void SetScene( IScene * );
	void Exit();
};

#endif

