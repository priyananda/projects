#ifndef _PIXELX_SCENERENDERER
#define _PIXELX_SCENERENDERER

#include "PxGUIScene.h"

#include <vector>
using std::vector;

#include <hash_map>
using std::hash_map;

class PxSceneRegulator : public ISceneRegulator
{
	vector<ISceneRenderer *> m_renderers;
	hash_map<string,IScene *> m_scenes;
	ISceneRenderer * m_currentRenderer;
public:
	PxSceneRegulator();
	
	void AddScene( IScene * );
	void Signal( long condition , void * params = NULL);
private:
	ISceneRenderer * FindRenderer( IScene * );
};

#endif

