#ifndef _PIXELX_LOADING_SCENE
#define _PIXELX_LOADING_SCENE

#include "ISceneRenderer.h"

class PxLoadingScene : public IScene
{
	string m_sSceneName;
public:
	PxLoadingScene(cstrref name);

	cstrref GetSceneName();
	PxSceneType GetSceneType();

	virtual void Initialize();
	virtual void Dispose();
};
#endif

