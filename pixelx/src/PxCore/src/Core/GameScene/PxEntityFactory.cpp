#include "PxEntityFactory.h"
#include "..\..\PxGraphics\include\PxQuakeMapLoader.h"
#include "..\..\PxGraphics\include\PxQuakeMapRenderer.h"
#include "..\..\PxGraphics\include\PxModelManager.h"
#include "..\..\PxPhysics\include\PxCollisionManager.h"
#include "..\..\PxGraphics\include\PxHealthItem.h"
#include "..\..\PxGraphics\include\PxArmourItem.h"
#include "..\..\PxGraphics\include\PxAmmoItem.h"
#include "..\..\PxGraphics\include\PxWeaponItem.h"
#include "..\..\PxGraphics\include\PxBot.h"

#define QUAKE_START_POS		"info_player_start"
#define QUAKE_AMMO			"ammo_"
#define QUAKE_ARMOUR		"item_armor_body"
#define QUAKE_HEALTH_SMALL	"item_health_small"
#define QUAKE_HEALTH		"item_health"
#define QUAKE_HEALTH_LARGE	"item_health_large"
#define QUAKE_WEAPON		"weapon_"
#define QUAKE_ARMOUR_SHARD	"item_armor_shard"
#define QUAKE_PLAYER		"info_player_deathmatch"

int PxEntityFactory::AddObjects( PxQuake3EntityCollection & entities , list<UP<PxSolidObject>>& mRuntimeObjects , cstrref botname)
{
	int ret = 0;
	for (PxQuake3Entity& entity : entities) {
		PxModel * pModel = nullptr;
		float yfactor = 0, yangle = 0;
		if( _strnicmp( entity.ClassName.c_str() , QUAKE_AMMO , 5 ) == 0 )
		{
			pModel = new PxAmmoItem(10);
		}
		if( _strnicmp( entity.ClassName.c_str() , QUAKE_WEAPON , 7 ) == 0 )
		{
			pModel = new PxWeaponItem();
		}
		if( _stricmp( entity.ClassName.c_str() , QUAKE_ARMOUR ) == 0 )
		{
			pModel = new PxArmourItem(10);
		}
		if( _stricmp( entity.ClassName.c_str() , QUAKE_ARMOUR_SHARD ) == 0 )
		{
			pModel = new PxBobbingItem( PxModelManager::GetModel( "QUAD" ) );
		}
		if( 
			_stricmp( entity.ClassName.c_str() , QUAKE_HEALTH_SMALL ) == 0 ||
			_stricmp( entity.ClassName.c_str() , QUAKE_HEALTH ) == 0 ||
			_stricmp( entity.ClassName.c_str() , QUAKE_HEALTH_LARGE ) == 0
		)
		{
			pModel = new PxHealthItem(10);
		}
		if( _stricmp( entity.ClassName.c_str() , QUAKE_PLAYER ) == 0 )
		{
			pModel = new PxBot( botname );
			yfactor = 1.5f;
			yangle = float(atof( entity[ "angle" ].c_str() ));
			++ret;
		}
		if( pModel )
		{
			
			pModel->SetLocation( entity.Origin.x,entity.Origin.y - yfactor ,entity.Origin.z );
			if( yangle )
				pModel->Turn( yangle );
			pModel->SetScale(0.1f);
			PxCollisionManager::Register( pModel );
			mRuntimeObjects.push_back(UP<PxSolidObject>{pModel});
		}
	}
	if( ret == 0 )
		ret = 1;
	return ret;
}

