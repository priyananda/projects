#include "PxIntroScene.h"

PxIntroScene::PxIntroScene( cstrref name ): m_sSceneName(name){}

cstrref PxIntroScene::GetSceneName()
{
	return m_sSceneName;
}

PxSceneType PxIntroScene::GetSceneType()
{
	return eSceneIntro;
}

void PxIntroScene::Dispose()
{

}

void PxIntroScene::Initialize()
{

}

