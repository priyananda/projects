#ifndef _PIXELX_ISCENERENDERER
#define _PIXELX_ISCENERENDERER

#include "Common.h"
#include "PxInputEventHandler.h"

enum PxSceneType
{
	eSceneGUI,
	eSceneGame,
	eSceneIntro,
	eSceneLoading,
	eSceneEndGame
};
enum PxSceneSignal
{
	eScAdvance,
	eScPrevious,
	eScNamedScene
};

class ISceneRegulator;
class IScene
{
protected:
	ISceneRegulator * m_pSceneRegulator;
public:
	virtual cstrref GetSceneName() = 0;
	virtual PxSceneType GetSceneType() = 0;

	void SetSceneRegulator(ISceneRegulator * p)
	{
		m_pSceneRegulator = p;
	}
};
class ISceneRenderer : public PxInputEventhandler
{
public:
	virtual void Enter() = 0;
	virtual bool AcceptScene( IScene * ) = 0;
	virtual void SetScene( IScene * ) = 0;
	virtual void Exit() = 0;
};

class ISceneRegulator
{
public:
	virtual void AddScene( IScene * ) = 0;
	virtual void Signal( long condition , void * params = NULL) = 0;
};
#endif