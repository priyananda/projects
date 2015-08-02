#include "PxWeaponItem.h"

extern int g_debug_health;
void PxWeaponItem::OnCollision()
{
	if( m_isActive )
	{
		m_isActive = false;
	}
}

void PxWeaponItem::Render()
{
	if( m_isActive )
		PxBobbingItem::Render();
}

