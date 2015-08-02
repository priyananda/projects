#include "PxAmmoItem.h"
#include "..\..\PxCore\include\PxHuman.h"

void PxAmmoItem::OnCollision()
{
	if( m_isActive )
	{
		PxHuman::AddAmmo( m_AmmoFactor );
		m_isActive = false;
	}
}

void PxAmmoItem::Render()
{
	if( m_isActive )
		PxBobbingItem::Render();
}

