#include "PxVertex.h"
#include "PxQuakeMapLoader.h"
#include "PxQuakeTextureManager.h"
#include "..\..\PxInput\include\PxConfiguration.h"

#include <stdio.h>

#define CLEAR_AND_RETURNnullptr \
	{\
		delete map; \
		return nullptr; \
	}
DECLARE_VARF(g_debug_bspscale);
PxQuakeMap * PxQuakeMapLoader::Load(char * filename, int curveTesselation)
{
	ASSIGN_VARF(g_debug_bspscale);
	FILE * file = nullptr;
	fopen_s(&file, filename, "rb");
	if(!file)
	{
		PxLog::LogMessage("Unable to open %s", filename);
		return nullptr;
	}

	fread(&header, sizeof(PxBSPHeader), 1, file);

	if(	header.string[0]!='I' || header.string[1]!='B' ||
		header.string[2]!='S' || header.string[3]!='P'
	){
		PxLog::LogMessage("What the fuck is this file: %s ? Not a BSP file", filename);
		fclose(file);
		return nullptr;
	}

	if( header.string[4] != 0x2e )
	{
		PxLog::LogMessage("Oops! BSP version is not right(%x). It should be %x", header.string[4], 0x2e);
	}
	map = new PxQuakeMap();
	
	if(!LoadEntityString(file))
		CLEAR_AND_RETURNnullptr

	if(!LoadTextures(file))
		CLEAR_AND_RETURNnullptr

	if(!LoadPlanes(file))
		CLEAR_AND_RETURNnullptr

	if(!LoadNodes(file))
		CLEAR_AND_RETURNnullptr
	
	if(!LoadLeaves(file))
		CLEAR_AND_RETURNnullptr

	if(!LoadLeafFaces(file))
		CLEAR_AND_RETURNnullptr

	if(!LoadLeafBrushes(file))
		CLEAR_AND_RETURNnullptr

	if(!LoadBrushes(file))
		CLEAR_AND_RETURNnullptr

	if(!LoadBrushSides(file))
		CLEAR_AND_RETURNnullptr

	if(!LoadVertices(file))
		CLEAR_AND_RETURNnullptr

	if(!LoadMeshIndices(file))
		CLEAR_AND_RETURNnullptr

	if(!LoadFaces(file, curveTesselation))
		CLEAR_AND_RETURNnullptr

	if(!LoadLightmaps(file))
		CLEAR_AND_RETURNnullptr

	if(!LoadVisData(file))
		CLEAR_AND_RETURNnullptr

	LoadConfig( filename );
	fclose(file);
	PxLog::LogMessage("%s Loaded successfully", filename);
	return map;
}

bool PxQuakeMapLoader::LoadEntityString(FILE * file)
{
	int numEntities = header.directoryEntries[bspEntities].length;
	fseek(file, header.directoryEntries[bspEntities].offset, SEEK_SET);
	FILE * tempFile = nullptr;
	fopen_s(&tempFile, "temp.ent", "w");
	char ch = 0;
    for( int i = 0 ; i < numEntities; ++i )
	{
		fread(&ch,1,1,file);
		fwrite(&ch,1,1,tempFile );
	}
	fclose( tempFile );
	PxQuake3EntityParser::Parse( "temp.ent" , map->entities );
	return true;
}

bool PxQuakeMapLoader::LoadVertices(FILE * file)
{
	map->numVertices = header.directoryEntries[bspVertices].length/sizeof(PxBSPLoadVertex);
	PxBSPLoadVertex * loadVertices = new PxBSPLoadVertex[map->numVertices];
	fseek(file, header.directoryEntries[bspVertices].offset, SEEK_SET);
	fread(loadVertices, header.directoryEntries[bspVertices].length, 1, file);
	map->vertices = new PxBSPVertex[map->numVertices];
	
	PxVertex min,max;
	bool firstVertex = true;
	for(int i = 0 ; i < map->numVertices; ++i)
	{
		map->vertices[i].position.x=loadVertices[i].position.x;
		map->vertices[i].position.y=loadVertices[i].position.z;
		map->vertices[i].position.z=-loadVertices[i].position.y;
		map->vertices[i].position = map->vertices[i].position / g_debug_bspscale;
		map->vertices[i].decalS=loadVertices[i].decalS;
		map->vertices[i].decalT=loadVertices[i].decalT;
		map->vertices[i].lightmapS=loadVertices[i].lightmapS;
		map->vertices[i].lightmapT=loadVertices[i].lightmapT;

		if( firstVertex )
		{
			min = max = PxVertex(map->vertices[i].position.x,map->vertices[i].position.y,map->vertices[i].position.z );
			firstVertex = false;
		}
		else
		{
			if( map->vertices[i].position.x < min.x ) min.x = map->vertices[i].position.x;
			if( map->vertices[i].position.y < min.y ) min.y = map->vertices[i].position.y;
			if( map->vertices[i].position.z < min.z ) min.z = map->vertices[i].position.z;
			if( map->vertices[i].position.x > max.x ) max.x = map->vertices[i].position.x;
			if( map->vertices[i].position.y > max.y ) max.y = map->vertices[i].position.y;
			if( map->vertices[i].position.z > max.z ) max.z = map->vertices[i].position.z;
		}
	}

	map->boundingBox.x = min.x;
	map->boundingBox.y = min.y;
	map->boundingBox.z = min.z;
	map->boundingBox.length = max.x - min.x;
	map->boundingBox.width = max.y - min.y;
	map->boundingBox.height = max.z - min.z;

	if(loadVertices)
		delete [] loadVertices;
	loadVertices=nullptr;

	return true;
}

bool PxQuakeMapLoader::LoadFaces(FILE * file, int curveTesselation)
{
	map->numFaces = header.directoryEntries[bspFaces].length/sizeof(PxBSPLoadFace);
	PxBSPLoadFace * loadFaces = new PxBSPLoadFace[map->numFaces];
	map->faceDirectory = new PxBSPFaceDirectoryEntry[map->numFaces];
	memset(map->faceDirectory, 0, map->numFaces * sizeof(PxBSPFaceDirectoryEntry));

	fseek(file, header.directoryEntries[bspFaces].offset, SEEK_SET);
	fread(loadFaces, header.directoryEntries[bspFaces].length, 1, file);

	for(int i = 0; i < map->numFaces; ++i)
	{
		if(loadFaces[i].type == bspPolygonFace)
			++map->numPolygonFaces;
		if(loadFaces[i].type == bspPatch)
			++map->numPatches;
		if(loadFaces[i].type == bspMeshFace)
			++map->numMeshFaces;
	}
	map->polygonFaces = new PxBSPPolygonFace[map->numPolygonFaces];
	int currentFace=0;
	for(int i = 0; i < map->numFaces; ++i)
	{
		if(loadFaces[i].type!=bspPolygonFace)		//skip this loadFace if it is not a polygon face
			continue;

		map->polygonFaces[currentFace].firstVertexIndex=loadFaces[i].firstVertexIndex;
		map->polygonFaces[currentFace].numVertices=loadFaces[i].numVertices;
		map->polygonFaces[currentFace].textureIndex=loadFaces[i].texture;
		map->polygonFaces[currentFace].lightmapIndex=loadFaces[i].lightmapIndex;

		map->faceDirectory[i].faceType=bspPolygonFace;
		map->faceDirectory[i].typeFaceNumber=currentFace;

		map->polygonFaces[currentFace].Normal = CalculateNormal( loadFaces[i].firstVertexIndex );
		++currentFace;
	}

	map->meshFaces=new PxBSPMeshFace[map->numMeshFaces];
	int currentMeshFace=0;
	for(int i = 0; i < map->numFaces ; ++i)
	{
		if(loadFaces[i].type!=bspMeshFace)		//skip this loadFace if it is not a mesh face
			continue;

		map->meshFaces[currentMeshFace].firstVertexIndex=loadFaces[i].firstVertexIndex;
		map->meshFaces[currentMeshFace].numVertices=loadFaces[i].numVertices;
		map->meshFaces[currentMeshFace].textureIndex=loadFaces[i].texture;
		map->meshFaces[currentMeshFace].lightmapIndex=loadFaces[i].lightmapIndex;
		map->meshFaces[currentMeshFace].firstMeshIndex=loadFaces[i].firstMeshIndex;
		map->meshFaces[currentMeshFace].numMeshIndices=loadFaces[i].numMeshIndices;

		map->faceDirectory[i].faceType=bspMeshFace;
		map->faceDirectory[i].typeFaceNumber=currentMeshFace;

		++currentMeshFace;
	}

	map->patches = new PxBSPPatch[map->numPatches];
	int currentPatch=0;
	for(int i = 0; i < map->numFaces ; ++i)
	{
		if(loadFaces[i].type!=bspPatch)		//skip this loadFace if it is not a patch
			continue;

		map->patches[currentPatch].textureIndex=loadFaces[i].texture;
		map->patches[currentPatch].lightmapIndex=loadFaces[i].lightmapIndex;
		map->patches[currentPatch].width=loadFaces[i].patchSize[0];
		map->patches[currentPatch].height=loadFaces[i].patchSize[1];
		
		//fill in this entry on the face directory
		map->faceDirectory[i].faceType=bspPatch;
		map->faceDirectory[i].typeFaceNumber=currentPatch;

		//Create space to hold quadratic patches
		int numPatchesWide=(map->patches[currentPatch].width-1)/2;
		int numPatchesHigh=(map->patches[currentPatch].height-1)/2;

		map->patches[currentPatch].numQuadraticPatches=	numPatchesWide*numPatchesHigh;
		map->patches[currentPatch].quadraticPatches = new PxBSPBiquadraticPatch [map->patches[currentPatch].numQuadraticPatches];

		for(int y=0; y<numPatchesHigh; ++y)
		{
			for(int x=0; x<numPatchesWide; ++x)
			{
				for(int row=0; row<3; ++row)
				{
					for(int point=0; point<3; ++point)
					{
						map->patches[currentPatch].quadraticPatches[y*numPatchesWide+x].
							controlPoints[row*3+point]= map->vertices[loadFaces[i].firstVertexIndex+
								(y*2*map->patches[currentPatch].width+x*2)+
									row*map->patches[currentPatch].width+point];
					}
				}
				map->patches[currentPatch].quadraticPatches[y*numPatchesWide+x].Tesselate(curveTesselation);
			}
		}
		++currentPatch;
	}

	if(loadFaces)
		delete [] loadFaces;
	loadFaces=nullptr;

	return true;
}

bool PxQuakeMapLoader::LoadTextures(FILE * file)
{
	map->numTextures = header.directoryEntries[bspTextures].length/sizeof(PxBSPLoadTexture);
	PxBSPLoadTexture * loadTextures = new PxBSPLoadTexture[map->numTextures];

	fseek(file, header.directoryEntries[bspTextures].offset, SEEK_SET);
	fread(loadTextures, 1, header.directoryEntries[bspTextures].length, file);

	map->decalTextures = new GLuint[map->numTextures];
	map->isTextureLoaded = new bool[map->numTextures];
	map->isTextureSolid = new bool[map->numTextures];
	map->isTextureShader = new bool[map->numTextures];

	for(int i = 0; i < map->numTextures; ++i)
	{
		map->decalTextures[i] = PxQuakeTextureManager::GetTextureId( loadTextures[i].name );
        if( map->decalTextures[i] == 0 )
		{
			PxLog::LogMessage( "[QUAKE]Missing tex : %s : " , loadTextures[i].name );
			map->decalTextures[i] = PxTextureManager::GetTextureId( "QUAKE_WALL1" );
		}
		map->isTextureLoaded[i] = (map->decalTextures[i] != 0);
		map->isTextureSolid[i] =(loadTextures[i].contents & 1);
		if( _stricmp( loadTextures[i].name , "textures/sfx/flame1_hell" ) )
			map->isTextureShader[i] = true;
		else
			map->isTextureShader[i] = false;
	}

	if(loadTextures)
		delete [] loadTextures;
	loadTextures=nullptr;

	return true;
}

bool PxQuakeMapLoader::LoadLightmaps(FILE * file)
{
	map->numLightmaps = header.directoryEntries[bspLightmaps].length/sizeof(PxBSPLoadLightMap);
	PxBSPLoadLightMap * loadLightmaps = new PxBSPLoadLightMap[map->numLightmaps];
	fseek(file, header.directoryEntries[bspLightmaps].offset, SEEK_SET);
	fread(loadLightmaps, 1, header.directoryEntries[bspLightmaps].length, file);

	map->lightmapTextures = new GLuint[map->numLightmaps];
	glGenTextures(map->numLightmaps, map->lightmapTextures);
	float gamma = PxConfiguration::GetFloat( "g_gamma" );
	for(int i = 0; i < map->numLightmaps; ++i)
	{
		for(int j = 0 ; j < 128*128 ; ++j)
		{
			float r, g, b;
			r=loadLightmaps[i].lightmapData[j*3+0];
			g=loadLightmaps[i].lightmapData[j*3+1];
			b=loadLightmaps[i].lightmapData[j*3+2];

			r*=gamma/255.0f;
			g*=gamma/255.0f;
			b*=gamma/255.0f;

			float scale=1.0f;
			float temp;
			if(r > 1.0f && (temp = (1.0f/r)) < scale) scale=temp;
			if(g > 1.0f && (temp = (1.0f/g)) < scale) scale=temp;
			if(b > 1.0f && (temp = (1.0f/b)) < scale) scale=temp;

			scale*=255.0f;		
			r*=scale;
			g*=scale;
			b*=scale;

			loadLightmaps[i].lightmapData[j*3+0]=(GLubyte)r;
			loadLightmaps[i].lightmapData[j*3+1]=(GLubyte)g;
			loadLightmaps[i].lightmapData[j*3+2]=(GLubyte)b;
		}
	}

	for(int i = 0; i < map->numLightmaps; ++i)
	{
		glBindTexture(GL_TEXTURE_2D, map->lightmapTextures[i]);
		
		gluBuild2DMipmaps(	GL_TEXTURE_2D, GL_RGBA8, 128, 128,
							GL_RGB, GL_UNSIGNED_BYTE, loadLightmaps[i].lightmapData);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if(loadLightmaps)
		delete [] loadLightmaps;
	loadLightmaps=nullptr;

	return true;
}

bool PxQuakeMapLoader::LoadLeaves(FILE * file)
{
	map->numLeaves = header.directoryEntries[bspLeaves].length/sizeof(PxBSPLoadLeaf);
	PxBSPLoadLeaf * loadLeaves = new PxBSPLoadLeaf[map->numLeaves];
	map->leaves = new PxBSPLeaf[map->numLeaves];

	fseek(file, header.directoryEntries[bspLeaves].offset, SEEK_SET);
	fread(loadLeaves, 1, header.directoryEntries[bspLeaves].length, file);

	for(int i = 0; i < map->numLeaves; ++i)
	{
		map->leaves[i].cluster=loadLeaves[i].cluster;
		map->leaves[i].firstLeafFace=loadLeaves[i].firstLeafFace;
		map->leaves[i].numFaces=loadLeaves[i].numFaces;

		map->leaves[i].boundingBoxVertices[0]= PxVector((float)loadLeaves[i].mins[0], (float)loadLeaves[i].mins[2],-(float)loadLeaves[i].mins[1]);
		map->leaves[i].boundingBoxVertices[1]= PxVector((float)loadLeaves[i].mins[0], (float)loadLeaves[i].mins[2],-(float)loadLeaves[i].maxs[1]);
		map->leaves[i].boundingBoxVertices[2]= PxVector((float)loadLeaves[i].mins[0], (float)loadLeaves[i].maxs[2],-(float)loadLeaves[i].mins[1]);
		map->leaves[i].boundingBoxVertices[3]= PxVector((float)loadLeaves[i].mins[0], (float)loadLeaves[i].maxs[2],-(float)loadLeaves[i].maxs[1]);
		map->leaves[i].boundingBoxVertices[4]= PxVector((float)loadLeaves[i].maxs[0], (float)loadLeaves[i].mins[2],-(float)loadLeaves[i].mins[1]);
		map->leaves[i].boundingBoxVertices[5]= PxVector((float)loadLeaves[i].maxs[0], (float)loadLeaves[i].mins[2],-(float)loadLeaves[i].maxs[1]);
		map->leaves[i].boundingBoxVertices[6]= PxVector((float)loadLeaves[i].maxs[0], (float)loadLeaves[i].maxs[2],-(float)loadLeaves[i].mins[1]);
		map->leaves[i].boundingBoxVertices[7]= PxVector((float)loadLeaves[i].maxs[0], (float)loadLeaves[i].maxs[2],-(float)loadLeaves[i].maxs[1]);

		for(int j=0; j<8; ++j)
			map->leaves[i].boundingBoxVertices[j]= map->leaves[i].boundingBoxVertices[j] / g_debug_bspscale ;
		
		map->leaves[i].firstLeafBrush = loadLeaves[i].firstLeafBrush;
		map->leaves[i].numBrushes = loadLeaves[i].numBrushes;
	}
	if(loadLeaves)
		delete [] loadLeaves;

	return true;
}
bool PxQuakeMapLoader::LoadLeafFaces(FILE * file)
{
	map->numLeafFaces = header.directoryEntries[bspLeafFaces].length/sizeof(int);
	map->leafFaces = new int[map->numLeafFaces];
	fseek(file, header.directoryEntries[bspLeafFaces].offset, SEEK_SET);
	fread(map->leafFaces, 1, header.directoryEntries[bspLeafFaces].length, file);
	return true;
}

bool PxQuakeMapLoader::LoadPlanes(FILE * file)
{
	map->numPlanes = header.directoryEntries[bspPlanes].length/sizeof(PxPlane);
	map->planes = new PxPlane[map->numPlanes];
	fseek(file, header.directoryEntries[bspPlanes].offset, SEEK_SET);
	fread(map->planes, 1, header.directoryEntries[bspPlanes].length, file);
	for(int i=0; i< map->numPlanes; ++i)
	{
		float temp = map->planes[i].normal.y;
		map->planes[i].normal.y = map->planes[i].normal.z;
		map->planes[i].normal.z = -temp;

		//map->planes[i].intercept = -map->planes[i].intercept;
		map->planes[i].intercept /= g_debug_bspscale;	//scale down
	}
	return true;
}

bool PxQuakeMapLoader::LoadNodes(FILE * file)
{
	map->numNodes = header.directoryEntries[bspNodes].length/sizeof(PxBSPNode);
	map->nodes = new PxBSPNode[map->numNodes];
	fseek(file, header.directoryEntries[bspNodes].offset, SEEK_SET);
	fread(map->nodes, 1, header.directoryEntries[bspNodes].length, file);
	return true;
}

bool PxQuakeMapLoader::LoadVisData(FILE * file)
{
	if( header.directoryEntries[bspVisData].length == 0 )
	{
		map->visibilityData.numClusters = -1;
		map->visibilityData.bytesPerCluster = -1;
		map->visibilityData.bitset = nullptr;
		return true;
	}
	fseek(file, header.directoryEntries[bspVisData].offset, SEEK_SET);
	fread(&map->visibilityData, 2, sizeof(int), file);
	int bitsetSize = map->visibilityData.numClusters*map->visibilityData.bytesPerCluster;
	map->visibilityData.bitset = new GLubyte[bitsetSize];
	fread(map->visibilityData.bitset, 1, bitsetSize, file);
	return true;
}

bool PxQuakeMapLoader::LoadLeafBrushes(FILE * file)
{
	map->numLeafBrushes = header.directoryEntries[bspLeafBrushes].length/sizeof(int);
	map->leafBrushes = new int[map->numLeafBrushes];
	fseek(file, header.directoryEntries[bspLeafBrushes].offset, SEEK_SET);
	fread(map->leafBrushes, map->numLeafBrushes, sizeof(int), file);
	return true;
}

bool PxQuakeMapLoader::LoadBrushes(FILE * file)
{
	map->numBrushes = header.directoryEntries[bspBrushes].length / sizeof(PxBSPBrush);
	map->brushes = new PxBSPBrush[map->numBrushes];
	fseek(file, header.directoryEntries[bspBrushes].offset, SEEK_SET);
	fread(map->brushes, map->numBrushes, sizeof(PxBSPBrush), file);
	return true;
}

bool PxQuakeMapLoader::LoadMeshIndices(FILE * file)
{
	map->numMeshIndices = header.directoryEntries[bspMeshIndices].length/sizeof(int);
	map->meshIndices = new int[map->numMeshIndices];
	fseek(file, header.directoryEntries[bspMeshIndices].offset, SEEK_SET);
	fread(map->meshIndices, header.directoryEntries[bspMeshIndices].length, 1, file);
	return true;
}

bool PxQuakeMapLoader::LoadBrushSides(FILE * file)
{
	map->numBrushSides = header.directoryEntries[bspBrushSides].length / sizeof(PxBSPBrushSide);
	map->brushSides = new PxBSPBrushSide [map->numBrushSides];
	fseek(file, header.directoryEntries[bspBrushSides].offset, SEEK_SET);
	fread(map->brushSides, map->numBrushSides, sizeof(PxBSPBrushSide), file);
	return true;
}

PxVector PxQuakeMapLoader::CalculateNormal(int firstVertexIndex)
{
	PxVector Normal;
	GLfloat ux = this->map->vertices[firstVertexIndex+1].position.x - this->map->vertices[firstVertexIndex].position.x;
	GLfloat uy = this->map->vertices[firstVertexIndex+1].position.y - this->map->vertices[firstVertexIndex].position.y;
	GLfloat uz = this->map->vertices[firstVertexIndex+1].position.z - this->map->vertices[firstVertexIndex].position.z;
	GLfloat vx = this->map->vertices[firstVertexIndex+2].position.x - this->map->vertices[firstVertexIndex].position.x;
	GLfloat vy = this->map->vertices[firstVertexIndex+2].position.y - this->map->vertices[firstVertexIndex].position.y;
	GLfloat vz = this->map->vertices[firstVertexIndex+2].position.z - this->map->vertices[firstVertexIndex].position.z;
	Normal.x = (uy*vz)-(vy*uz);
	Normal.y = (uz*vx)-(vz*ux);
	Normal.z = (ux*vy)-(vx*uy);
	Normal.Normalize();
	return Normal;
}

bool PxQuakeMapLoader::LoadConfig(cstrref filename)
{
	string cfgfile = filename;
	int len = cfgfile.length();
	cfgfile[ len - 3 ] = 'p';
	cfgfile[ len - 2 ] = 'x';
	cfgfile[ len - 1 ] = 'l';
	PxConfiguration::ReadCommands(cfgfile);
	return true;
}

