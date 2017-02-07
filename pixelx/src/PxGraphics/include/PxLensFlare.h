#ifndef _PIXELX_LENSFLARE_H
#define _PIXELX_LENSFLARE_H

#include "PxVertex.h"
#include "../../PxPhysics/include/PxVector.h"

class PxFlareElement
{
public:
	float distance;
	float size;
	unsigned int ARGB;
	GLuint textureID;
};

struct PxFlare
{
	float scale = 1;
	float maxSize = 0;
	int numElements = 0;
	PxFlareElement * elements = nullptr;

	PxFlare()
	{
	}
	PxFlare(int _numElements):
		numElements(_numElements),
		elements( new PxFlareElement[_numElements] )
	{
	}
};
class PxLensFlareRenderer
{
public:
	PxLensFlareRenderer( PxVertex & sunPosition );
	void Render( PxVector & cameraPosition );
private:
	long cx , cy;//Center of the screen
	PxFlare m_flare;
	long screenWidth, screenHeight;
	PxVertex m_sunPosition;
	float m_sunProjection[3];

	void RenderFlare( long lx, long ly);
	void DrawQuad( int x, int y, int width, int height, GLuint texID, unsigned int colour );
};

#endif

