#ifndef _PIXELX_AMMOITEM
#define _PIXELX_AMMOITEM

#include "PxBobbingItem.h"
#include "PxModelManager.h"
class PxAmmoItem : public PxBobbingItem
{
	int  m_AmmoFactor;
	bool m_isActive;
public:
	PxAmmoItem(int hp):
		m_AmmoFactor(hp),
		m_isActive(true),
		PxBobbingItem( PxModelManager::GetModel("AMMO") )
	{}
	virtual void OnCollision();
	virtual void Render();
};
#endif

