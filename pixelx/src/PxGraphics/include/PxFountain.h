#ifndef _PIXELX_FOUNTAIN_H
#define _PIXELX_FOUNTAIN_H

#include "PxSolidObject.h"
#include "PxParticleBase.h"

#define NUMBER_OF_STREAMS 4
#define FOUNTAIN_HEIGHT 12.25
class PxFountain : public PxSolidObject
{
	PxBoundingBox bBox;
	void AddParticles();
	void DeleteParticles();
	void MoveParticles();
	void DrawFountain();
	void DrawWater();
	PxParticle * stream[NUMBER_OF_STREAMS];
	GLuint texID;

	static PxVector upv;
public:
	PxFountain( float x,float y, float z );
	void Render();
	void Register( PxPolygonCollection * pcoll );
	void OnCollision();

	PxBoundingBox & GetBoundingBox()
	{
		return bBox;
	}
};

#endif

