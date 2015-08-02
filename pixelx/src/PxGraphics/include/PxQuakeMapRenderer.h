#ifndef _PIXELX_QUAKEMAPRENDERER_H
#define _PIXELX_QUAKEMAPRENDERER_H

#include "PxQuakeMap.h"
#include "PxFrustrum.h"
#include "PxBitset.h"

class PxQuakeMapRenderer
{
	PxQuakeMap * mMap;
	PxBitSet facesToDraw;
	GLuint whiteTexture;
public:
	int numTris;
	PxQuakeMapRenderer( PxQuakeMap * pMap );
	void Render(const PxVector & cameraPosition, const PxFrustrum & frustum);
	void RenderBoundingBox();
private:

	void DrawFace(int faceNumber);
	void DrawPolygonFace(int polygonFaceNumber);
	void DrawMeshFace(int meshFaceNumber);
	void DrawPatch(int patchNumber);
	void DrawBiquadraticPatch(PxBSPBiquadraticPatch * pQuad);
	void DrawEntities();
};
#endif

