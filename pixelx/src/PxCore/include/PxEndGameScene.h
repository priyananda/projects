#ifndef _PIXELX_ENDGAMESCENE_H
#define _PIXELX_ENDGAMESCENE_H

#include "ISceneRenderer.h"

class PxEndGameScene : public IScene
{
	string m_sSceneName;
public:
	PxEndGameScene(cstrref name);

	cstrref GetSceneName();
	PxSceneType GetSceneType();

	virtual void Initialize();
	virtual void Dispose();
};

#endif

