#ifndef _PIXELX_WEAPONITEM
#define _PIXELX_WEAPONITEM

#include "PxBobbingItem.h"
#include "PxModelManager.h"
class PxWeaponItem : public PxBobbingItem
{
	bool m_isActive;
public:
	PxWeaponItem():
		m_isActive(true),
		PxBobbingItem( PxModelManager::GetModel("SUPERGUN") )
	{}
	virtual void OnCollision();
	virtual void Render();
};
#endif

