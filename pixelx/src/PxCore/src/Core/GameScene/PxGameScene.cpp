#include "PxGameScene.h"

PxGameScene::PxGameScene( cstrref name ): m_sSceneName(name){}

cstrref PxGameScene::GetSceneName()
{
	return m_sSceneName;
}

PxSceneType PxGameScene::GetSceneType()
{
	return eSceneGame;
}

