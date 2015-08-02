#ifndef _PIXELX_BOT_H
#define _PIXELX_BOT_H

#include "PxModelManager.h"

class PxBot : public PxModel
{
	bool m_isActive;
public:
	PxBot( cstrref name ):
	  PxModel( PxModelManager::GetModel(name) ),
	  m_isActive(true)
	{}
	virtual void OnCollision();
	virtual void Render();
	virtual bool IsCollidable(){ return m_isActive; }
};
#endif

