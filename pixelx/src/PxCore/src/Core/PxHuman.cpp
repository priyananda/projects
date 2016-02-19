#include "PxHuman.h"

PxHuman * PxHuman::m_theHuman = nullptr;

void PxHuman::AddHealth(long l)
{
	if( m_theHuman )
		m_theHuman->iPlayerHealth += l;
}

void PxHuman::AddAmmo(long l)
{
	if( m_theHuman )
		m_theHuman->iPlayerAmmo += l;
}

void PxHuman::AddArmour(long l)
{
	if( m_theHuman )
		m_theHuman->iPlayerArmour += l;
}

void PxHuman::AddFragCount(long l)
{
	if( m_theHuman )
		m_theHuman->iFragCount += l;
}

