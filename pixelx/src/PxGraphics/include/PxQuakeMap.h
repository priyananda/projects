#ifndef _PIXELX_QUAKEMAP_H
#define _PIXELX_QUAKEMAP_H

#include "PxBoundingBox.h"
#include "PxBSPDataStructures.h"
#include "PxBitset.h"
#include "PxFrustrum.h"
#include "PxQuake3EntityParser.h"

struct PxQuakeMap
{
	PxQuakeMap();
	~PxQuakeMap();
	
	int numTextures;
	GLuint * decalTextures;
	bool * isTextureLoaded;
	bool * isTextureSolid;
	bool * isTextureShader;


	int numPlanes;
	PxPlane * planes;

	int numNodes;
	PxBSPNode * nodes;

	int numLeaves;
	PxBSPLeaf * leaves;

	int numLeafFaces;
	int * leafFaces;

	int numLeafBrushes;
	int * leafBrushes;

	int numModels;

	int numBrushes;
	PxBSPBrush * brushes;

	int numBrushSides;
	PxBSPBrushSide * brushSides;

	int numVertices;
	PxBSPVertex * vertices;

	int numMeshIndices;
	int * meshIndices;

	int numEffect;

	int numFaces;
	PxBSPFaceDirectoryEntry * faceDirectory;
	int numPolygonFaces;
	PxBSPPolygonFace * polygonFaces;
	int numMeshFaces;
	PxBSPMeshFace * meshFaces;
	int numPatches;
	PxBSPPatch * patches;

	int numLightmaps;
	GLuint * lightmapTextures;
	
	int numLightVols;
	
	PxBSPVisibilityData visibilityData;
	PxBoundingBox boundingBox;

	PxQuake3EntityCollection entities;
	
	int  CalculateCameraLeaf(const PxVector & cameraPosition);
	void CalculateVisibleFaces(const PxVector & cameraPosition, const PxFrustrum & frustum, PxBitSet & bitset );
	int  IsClusterVisible(int cameraCluster, int testCluster);
};
#endif

