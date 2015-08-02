#include "PxGUIScene.h"

PxGUIScene::PxGUIScene( cstrref name ): m_sSceneName(name){}

cstrref PxGUIScene::GetSceneName()
{
	return m_sSceneName;
}

PxSceneType PxGUIScene::GetSceneType()
{
	return eSceneGUI;
}

void PxGUIScene::Dispose()
{

}

void PxGUIScene::Initialize()
{

}

