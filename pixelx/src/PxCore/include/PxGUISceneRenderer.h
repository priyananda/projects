#ifndef _PIXELX_GUISCENERENDERER
#define _PIXELX_GUISCENERENDERER

#include "PxGUIScene.h"

class PxGUISceneRenderer : public ISceneRenderer
{
	PxGUIScene * m_pCurrentScene;
	ISceneRegulator * m_pRegulator;
public:
	PxGUISceneRenderer(ISceneRegulator * pReg);

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

