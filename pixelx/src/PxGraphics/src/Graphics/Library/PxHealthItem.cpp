#include "PxHealthItem.h"
#include "..\..\PxCore\include\PxHuman.h"

void PxHealthItem::OnCollision()
{
	if( m_isActive )
	{
		PxHuman::AddHealth( m_HealthFactor );
		m_isActive = false;
	}
}

void PxHealthItem::Render()
{
	if( m_isActive )
		PxBobbingItem::Render();
}

