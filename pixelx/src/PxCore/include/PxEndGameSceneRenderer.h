#ifndef _PIXELX_ENDGAMESCENERENDERER_H
#define _PIXELX_ENDGAMESCENERENDERER_H

#include "PxEndGameScene.h"

class PxEndGameSceneRenderer : public ISceneRenderer
{
	PxEndGameScene * m_pCurrentScene;
	ISceneRegulator * m_pRegulator;

public:
	PxEndGameSceneRenderer(ISceneRegulator * pReg);

	void Enter();
	bool AcceptScene( IScene * );
	void SetScene( IScene * );
	void Exit();

	void HandleKey( int ScanCode, PxKeyStateEnum keyState );
	void HandleChar( int charCode );
	void HandleMouse( PxMouseKeyEnum , int x, int y, bool isUp);
	void HandlePaint( PxWindow *);
	void HandleMouseMotion( int x,int y);
	void HandleMouseWheel( bool isUp );
};
#endif

