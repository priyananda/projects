#include "PxQuakeMap.h"
#include "PxFrustrum.h"

PxQuakeMap::PxQuakeMap():
	numTextures(0),
	decalTextures(0),
	isTextureLoaded(0),
	isTextureSolid(0),
	numPlanes(0),
	planes(0),
	numNodes(0),
	nodes(0),
	numLeaves(0),
	leaves(0),
	numLeafFaces(0),
	leafFaces(0),
	numLeafBrushes(0),
	leafBrushes(0),
	numModels(0),
	numBrushes(0),
	brushes(0),
	numBrushSides(0),
	brushSides(0),
	numVertices(0),
	vertices(0),
	numMeshIndices(0),
	meshIndices(0),
	numEffect(0),
	numFaces(0),
	numPolygonFaces(0),
	polygonFaces(0),
	numMeshFaces(0),
	meshFaces(0),
	numPatches(0),
	patches(0),
	numLightmaps(0),
	lightmapTextures(0),
	numLightVols(0){}

PxQuakeMap::~PxQuakeMap()
{
	if( decalTextures ) { delete [] decalTextures ; decalTextures = NULL; }
	if( isTextureLoaded ) { delete [] isTextureLoaded;isTextureLoaded = NULL; }
	if( isTextureSolid ) { delete [] isTextureSolid;isTextureSolid = NULL; }
	if( planes ) { delete [] planes; planes= NULL; }
	if( nodes ) { delete [] nodes;nodes = NULL; }
	if( leaves ) { delete [] leaves;leaves = NULL; }
	if( leafFaces ) { delete [] leafFaces;leafFaces = NULL; }
	if( leafBrushes ) { delete [] leafBrushes;leafBrushes = NULL; }
	if( brushes ) { delete [] brushes;brushes = NULL; }
	if( brushSides ) { delete [] brushSides;brushSides = NULL; }
	if( vertices ) { delete [] vertices;vertices = NULL; }
	if( meshIndices ) { delete [] meshIndices;meshIndices = NULL; }
	if( polygonFaces ) { delete [] polygonFaces;polygonFaces = NULL; }
	if( meshFaces ) { delete [] meshFaces;meshFaces = NULL; }
	if( patches ) { delete [] patches;patches = NULL; }
	if( lightmapTextures ) { delete [] lightmapTextures;lightmapTextures = NULL; }
}


int  PxQuakeMap::CalculateCameraLeaf(const PxVector & cameraPosition)
{
	int currentNode = 0;
	
	while(currentNode >= 0)
	{
		if( this->planes[this->nodes[currentNode].planeIndex].ClassifyPoint(cameraPosition) == POINT_IN_FRONT_OF_PLANE)
			currentNode=this->nodes[currentNode].front;
		else
			currentNode=this->nodes[currentNode].back;
	}

	//return leaf index
	return ~currentNode;
}

int  PxQuakeMap::IsClusterVisible(int cameraCluster, int testCluster)
{
	if( this->visibilityData.bytesPerCluster == -1 )
		return true;
	int index =	cameraCluster * this->visibilityData.bytesPerCluster + testCluster/8;
	if(index < 0 )
		return true;
	int returnValue = this->visibilityData.bitset[index] & (1<<(testCluster & 7));
	return returnValue;
}

void PxQuakeMap::CalculateVisibleFaces(const PxVector & cameraPosition,const PxFrustrum & frustum, PxBitSet & facesToDraw)
{
	facesToDraw.ClearAll();
	
	int cameraLeaf = CalculateCameraLeaf(cameraPosition);
	int cameraCluster = this->leaves[cameraLeaf].cluster;

	for(int i = 0 ; i < this->numLeaves; ++i)
	{
		//if the leaf is not in the PVS, continue
		if(!IsClusterVisible(cameraCluster, this->leaves[i].cluster))
			continue;

		//if this leaf does not lie in the frustum, continue
		if(!frustum.IsBoundingBoxInside(this->leaves[i].boundingBoxVertices))
			continue;

		//loop through faces in this leaf and mark them to be drawn
		for(int j = 0; j < this->leaves[i].numFaces; ++j)
		{
			facesToDraw.Set(this->leafFaces[this->leaves[i].firstLeafFace+j]);
		}
	}
}

