#ifndef _PIXELX_BSPDATASTR_H
#define _PIXELX_BSPDATASTR_H

#include "PxBitset.h"
#include "..\..\PxPhysics\include\PxPlane.h"

struct PxBSPNode
{
	int planeIndex;
	int front, back;
	int mins[3];
	int maxs[3];
};

struct PxBSPLeaf
{
	int cluster;
	PxVector boundingBoxVertices[8];
	int firstLeafFace;
	int numFaces;

	int firstLeafBrush;
	int numBrushes;
};

struct PxBSPBrush 
{
	int brushSide;
	int numOfBrushSides;
	int textureID;
}; 

struct PxBSPBrushSide 
{
	int Plane;
	int textureID;
};

struct PxBSPVertex
{
	PxVector position;
	float decalS, decalT;
	float lightmapS, lightmapT;

	PxBSPVertex operator+(const PxBSPVertex & rhs) const;
	PxBSPVertex operator*(const float rhs) const;
};

class PxBSPPolygonFace
{
public:
	int firstVertexIndex;
	int numVertices;
	int textureIndex;
	int lightmapIndex;
	PxVector Normal;
};

class PxBSPMeshFace
{
public:
	int firstVertexIndex;
	int numVertices;
	int textureIndex;
	int lightmapIndex;
	int firstMeshIndex;
	int numMeshIndices;
};

struct PxBSPBiquadraticPatch
{
	bool Tesselate(int newTesselation);
	PxBSPVertex controlPoints[9];
		
	int tesselation;
	PxBSPVertex * vertices;
	GLuint * indices;
	int * trianglesPerRow;
	unsigned int ** rowIndexPointers;

	PxBSPBiquadraticPatch() : vertices(nullptr){}
	~PxBSPBiquadraticPatch();
};
struct PxBSPPatch
{
	int textureIndex;
	int lightmapIndex;
	int width, height;

	int numQuadraticPatches;
	PxBSPBiquadraticPatch * quadraticPatches;
};
class PxBSPVisibilityData
{
public:
	int numClusters;
	int bytesPerCluster;
	GLubyte * bitset;

	PxBSPVisibilityData(){}
	~PxBSPVisibilityData();
};


enum PxBSPFaceType
{
	bspPolygonFace=1,
	bspPatch,
	bspMeshFace,
	bspBillboard
};

class PxBSPFaceDirectoryEntry
{
public:
	PxBSPFaceType faceType;
	int typeFaceNumber;
};
#endif

