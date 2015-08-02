#ifndef _PIXELX_INTROSCENE_H
#define _PIXELX_INTROSCENE_H

#include "ISceneRenderer.h"

class PxIntroScene : public IScene
{
	string m_sSceneName;
public:
	PxIntroScene(cstrref name);

	cstrref GetSceneName();
	PxSceneType GetSceneType();

	virtual void Initialize();
	virtual void Dispose();
};

#endif

