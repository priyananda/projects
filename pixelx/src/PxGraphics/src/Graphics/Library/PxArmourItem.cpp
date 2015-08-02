#include "PxArmourItem.h"
#include "..\..\PxCore\include\PxHuman.h"

void PxArmourItem::OnCollision()
{
	if( m_isActive )
	{
		PxHuman::AddArmour( m_ArmourFactor );
		m_isActive = false;
	}
}

void PxArmourItem::Render()
{
	if( m_isActive )
		PxBobbingItem::Render();
}

