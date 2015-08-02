#ifndef _PIXELX_QUAKEMAPLOADER_H
#define _PIXELX_QUAKEMAPLOADER_H

#include "PxQuakeMap.h"

class PxBSPDirectoryEntry
{
public:
	int offset;
	int length;
};

enum PxBSPDirectoryEntryType
{
	bspEntities=0,
	bspTextures,
	bspPlanes,
	bspNodes,
	bspLeaves,
	bspLeafFaces,
	bspLeafBrushes,
	bspModels,
	bspBrushes,
	bspBrushSides,
	bspVertices,
	bspMeshIndices,
	bspEffect,
	bspFaces,
	bspLightmaps,
	bspLightVols,
	bspVisData
};

class PxBSPHeader
{
public:
	char string[4];
	int version;
	PxBSPDirectoryEntry directoryEntries[17];
};

class PxBSPLoadVertex
{
public:
	PxVector position;
	float decalS, decalT;
	float lightmapS, lightmapT;
	PxVector normal;
	GLubyte color[4];
};

class PxBSPLoadFace
{
public:
	int texture;
	int effect;
	int type;
	int firstVertexIndex;
	int numVertices;
	int firstMeshIndex;
	int numMeshIndices;
	int lightmapIndex;
	int lightmapStart[2];
	int lightmapSize[2];
	PxVector lightmapOrigin;
	PxVector sTangent, tTangent;
	PxVector normal;
	int patchSize[2];
};

class PxBSPLoadTexture
{
public:
	char name[64];
	int flags, contents;
};

class PxBSPLoadLightMap
{
public:
	GLubyte lightmapData[128*128*3];
};

class PxBSPLoadLeaf
{
public:
	int cluster;
	int area;
	int mins[3];
	int maxs[3];
	int firstLeafFace;
	int numFaces;
	int firstLeafBrush;
	int numBrushes;
};

class PxQuakeMapLoader
{
public:
	PxQuakeMap * Load(char * filename, int curveTesselation);
private:
	bool LoadConfig(cstrref filename );
	bool LoadFaces(FILE * file, int curveTesselation);
	bool LoadMeshIndices(FILE * file);
	bool LoadVertices(FILE * file);
	bool LoadPlanes(FILE * file);
	bool LoadNodes(FILE * file);
	bool LoadLeaves(FILE * file);
	bool LoadLeafFaces(FILE * file);
	bool LoadVisData(FILE * file);
	bool LoadTextures(FILE * file);
	bool LoadLightmaps(FILE * file);
	bool LoadBrushes(FILE * file);
	bool LoadBrushSides(FILE * file);
	bool LoadLeafBrushes(FILE * file);
	bool LoadEntityString(FILE * file);
	
	PxQuakeMap * map;
	PxBSPHeader header;

	PxVector CalculateNormal(int firstVertexIndex);
};

#endif

