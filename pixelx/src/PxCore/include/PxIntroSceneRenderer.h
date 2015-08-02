#ifndef _PIXELX_INTROSCENERENDERER_H
#define _PIXELX_INTROSCENERENDERER_H

#include "PxIntroScene.h"

const int FRAMES = 10;

class PxIntroSceneRenderer : public ISceneRenderer
{
	PxIntroScene * m_pCurrentScene;
	ISceneRegulator * m_pRegulator;

	GLuint m_BlurTex;
	GLuint m_DispList;
	int	m_ElapsedTime;
	DWORD m_Start;

	void CreateBlurTexture();
	void CreateDisplayList();
	void RenderScene();
	void RenderLogo();
public:
	PxIntroSceneRenderer(ISceneRegulator * pReg);

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

