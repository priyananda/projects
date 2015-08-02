#ifndef _PIXELX_HEALTHITEM
#define _PIXELX_HEALTHITEM

#include "PxBobbingItem.h"
#include "PxModelManager.h"
class PxHealthItem : public PxBobbingItem
{
	int  m_HealthFactor;
	bool m_isActive;
public:
	PxHealthItem(int hp):
		m_HealthFactor(hp),
		m_isActive(true),
		PxBobbingItem( PxModelManager::GetModel("HEALTH") )
	{}
	virtual void OnCollision();
	virtual void Render();
};
#endif

