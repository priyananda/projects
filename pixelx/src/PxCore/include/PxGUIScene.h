#ifndef _PIXELX_GUISCENE
#define _PIXELX_GUISCENE

#include "ISceneRenderer.h"

class PxGUIScene : public IScene
{
	string m_sSceneName;
public:
	PxGUIScene(cstrref name);

	cstrref GetSceneName();
	PxSceneType GetSceneType();

	virtual void Initialize();
	virtual void Dispose();

	virtual void CustomRender(){}
};

#endif

