#include "PxCollisionManager.h"
#include "../../PxGraphics/include/PxCamera.h"
#include "PxQuakeCollisionController.h"
#include "PxNormalCollisionController.h"

PxNormalCollisionController * pNormal = new PxNormalCollisionController;
PxQuakeCollisionController  * pQuake  = nullptr;

void PxCollisionManager::Register( PxSolidObject * p )
{
	pNormal->Register(p);
}

void PxCollisionManager::Register( PxBoundingBox & bbox )
{
	pNormal->Register(bbox);
}

bool PxCollisionManager::Collides(PxCamera & camera)
{
	bool ret;
	if( pQuake )
		ret = pQuake->Collide(camera);
	return pNormal->Collide(camera) || ret;
}

bool PxCollisionManager::Collides(const PxVector & lineStart,PxVector & lineEnd , float radius)
{
	bool ret;
	if( pQuake )
		ret = pQuake->Collides(lineStart, lineEnd, radius);
	return pNormal->Collides(lineStart,lineEnd, radius) || ret;
}

void PxCollisionManager::Render()
{
}

void PxCollisionManager::Register( PxQuakeMap * p )
{
	if ( pQuake )
		delete pQuake;
	pQuake = new PxQuakeCollisionController(p);
}

bool PxCollisionManager::IsOnGround( PxCamera & camera )
{
	if( pQuake && pQuake->IsInside(camera.boundingSphere.centre) )
		return pQuake->IsOnGround();
	return true;
}

