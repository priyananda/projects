#include "PxEndGameScene.h"

PxEndGameScene::PxEndGameScene( cstrref name ): m_sSceneName(name){}

cstrref PxEndGameScene::GetSceneName()
{
	return m_sSceneName;
}

PxSceneType PxEndGameScene::GetSceneType()
{
	return eSceneEndGame;
}

void PxEndGameScene::Dispose()
{

}

void PxEndGameScene::Initialize()
{

}

