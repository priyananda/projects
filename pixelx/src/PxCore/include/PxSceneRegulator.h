#ifndef _PIXELX_SCENERENDERER
#define _PIXELX_SCENERENDERER

#include "PxGUIScene.h"

#include <vector>
using std::vector;

#include <unordered_map>
using std::unordered_map;

class PxSceneRegulator : public ISceneRegulator
{
	vector<ISceneRenderer *> m_renderers;
	unordered_map<string,IScene *> m_scenes;
	ISceneRenderer * m_currentRenderer;
public:
	PxSceneRegulator();
	
	void AddScene( IScene * );
	void Signal( long condition , void * params = nullptr);
private:
	ISceneRenderer * FindRenderer( IScene * );
};

#endif

