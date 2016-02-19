#include "PxSceneRegulator.h"
#include "Interfaces.h"
#include "PxGUISceneRenderer.h"
#include "PxGameSceneRenderer.h"
#include "PxIntroSceneRenderer.h"
#include "PxMapChooserGUIScene.h"
#include "PxMapListGUIScene.h"
#include "PxGameScene.h"
#include "..\..\PxGraphics\include\PxWindow.h"
#include "PxEndGameSceneRenderer.h"
#include "PxTeamChooserScene.h"

PxSceneRegulator::PxSceneRegulator()
	:m_currentRenderer(nullptr)
{
	m_renderers.push_back(
		new PxGUISceneRenderer( this )
	);
	m_renderers.push_back(
		new PxGameSceneRenderer( this )
	);
	m_renderers.push_back(
		new PxIntroSceneRenderer( this )
	);
	m_renderers.push_back(
		new PxEndGameSceneRenderer( this )
	);

	AddScene( new PxIntroScene("intro") );
	AddScene( new PxMapListGUIScene("choosemap") );
	//AddScene( new PxTeamChooserScene("choosemap") );
	AddScene( new PxEndGameScene("endgame") );
	//AddScene( new PxMapChooserGUIScene("choosemap") );
	//AddScene( new PxGameScene("game") );
}

void PxSceneRegulator::AddScene(IScene * pScene)
{
	pScene->SetSceneRegulator(this);
	m_scenes[ pScene->GetSceneName() ] = pScene;
}

void PxSceneRegulator::Signal( long condition , void * params )
{
	switch(condition)
	{
		case eScNamedScene:
			string sname((char*)params);
			if( m_scenes.find(sname) == m_scenes.end() )
				return;
			IScene * pScene = m_scenes[sname];
			ISceneRenderer * pSceneRenderer = FindRenderer(pScene);
			if( pSceneRenderer == nullptr)
				return;
			if( m_currentRenderer != nullptr)
				m_currentRenderer->Exit();
			m_currentRenderer = pSceneRenderer;
			m_currentRenderer->Enter();
			m_currentRenderer->SetScene( pScene );
			PxGraphicsRoot::Window->SetInputEventHandler( m_currentRenderer );
	}
}

ISceneRenderer * PxSceneRegulator::FindRenderer( IScene * pScene )
{
	int count = m_renderers.size();
	for( int i = 0 ; i < count ; ++i )
		if( m_renderers[i]->AcceptScene(pScene) )
			return m_renderers[i];
	return nullptr;
}

