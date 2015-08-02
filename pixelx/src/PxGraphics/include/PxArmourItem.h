#ifndef _PIXELX_ARMOURITEM
#define _PIXELX_ARMOURITEM

#include "PxBobbingItem.h"
#include "PxModelManager.h"
class PxArmourItem : public PxBobbingItem
{
	int  m_ArmourFactor;
	bool m_isActive;
public:
	PxArmourItem(int hp):
		m_ArmourFactor(hp),
		m_isActive(true),
		PxBobbingItem( PxModelManager::GetModel("ARMOUR") )
	{}
	virtual void OnCollision();
	virtual void Render();
};
#endif

