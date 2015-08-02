#ifndef _PIXELX_HUMAN_H
#define _PIXELX_HUMAN_H

#include "..\..\PxGraphics\include\PxCamera.h"

class PxHuman
{
	static PxHuman * m_theHuman;
public:
	long	iPlayerHealth,
			iPlayerArmour,
			iPlayerAmmo,
			iFragCount;

	PxCamera Camera;

	PxHuman():
		iPlayerHealth(100),
		iPlayerArmour(0),
		iPlayerAmmo(0),
		iFragCount(0)
	{
		m_theHuman = this;
	}
	void Register(){ m_theHuman = this; }

	static void AddHealth(long l);
	static void AddArmour(long l);
	static void AddAmmo(long l);
	static void AddFragCount(long l);
};
#endif

