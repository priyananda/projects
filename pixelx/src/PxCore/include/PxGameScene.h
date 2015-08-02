#ifndef _PIXELX_GAMESCENE
#define _PIXELX_GAMESCENE

#include "ISceneRenderer.h"

class PxWorld;
class PxGameScene : public IScene
{
protected:
	string m_sSceneName;
public:
	PxGameScene(cstrref name);

	cstrref GetSceneName();
	PxSceneType GetSceneType();

	void Initialize();
	void Dispose();

	PxWorld * World;
};

#endif

