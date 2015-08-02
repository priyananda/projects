#include "PxBot.h"
#include "..\..\PxSound\include\PxAudioManager.h"
#include "..\..\PxCore\include\PxHuman.h"

void PxBot::OnCollision()
{
	if( m_isActive )
	{
		m_isActive = false;
		PxHuman::AddFragCount(1);
		PxAudioManager::Play( "HOMER_JUMP" );
	}
}

void PxBot::Render()
{
	if( m_isActive )
	{
		PxModel::Animate( 0, 38,0.2f );
	}
}

