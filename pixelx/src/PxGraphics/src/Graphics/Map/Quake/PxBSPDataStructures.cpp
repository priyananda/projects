#include "PxBSPDataStructures.h"

PxBSPVertex PxBSPVertex::operator+(const PxBSPVertex & rhs) const
{
	PxBSPVertex result;
	result.position=position+rhs.position;
	result.decalS=decalS+rhs.decalS;
	result.decalT=decalT+rhs.decalT;
	result.lightmapS=lightmapS+rhs.lightmapS;
	result.lightmapT=lightmapT+rhs.lightmapT;
	return result;
}

PxBSPVertex PxBSPVertex::operator*(const float rhs) const
{
	PxBSPVertex result;
	result.position=position*rhs;
	result.decalS=decalS*rhs;
	result.decalT=decalT*rhs;
	result.lightmapS=lightmapS*rhs;
	result.lightmapT=lightmapT*rhs;
	return result;
}

PxBSPBiquadraticPatch::~PxBSPBiquadraticPatch()
{
	if(vertices)
		delete [] vertices; 
	vertices=NULL;

	if(indices)
		delete [] indices;
	indices=NULL;
}

PxBSPVisibilityData::~PxBSPVisibilityData()
{
	if(bitset)
		delete [] bitset;
	bitset=NULL;
}

bool PxBSPBiquadraticPatch::Tesselate(int newTesselation)
{
	tesselation=newTesselation;

	float px, py;
	PxBSPVertex temp[3];
	vertices=new PxBSPVertex[(tesselation+1)*(tesselation+1)];

	for(int v=0; v<=tesselation; ++v)
	{
		px=(float)v/tesselation;

		vertices[v]=controlPoints[0]*((1.0f-px)*(1.0f-px))+
					controlPoints[3]*((1.0f-px)*px*2)+
					controlPoints[6]*(px*px);
	}

	for(int u=1; u<=tesselation; ++u)
	{
		py=(float)u/tesselation;

		temp[0]=controlPoints[0]*((1.0f-py)*(1.0f-py))+
				controlPoints[1]*((1.0f-py)*py*2)+
				controlPoints[2]*(py*py);

		temp[1]=controlPoints[3]*((1.0f-py)*(1.0f-py))+
				controlPoints[4]*((1.0f-py)*py*2)+
				controlPoints[5]*(py*py);

		temp[2]=controlPoints[6]*((1.0f-py)*(1.0f-py))+
				controlPoints[7]*((1.0f-py)*py*2)+
				controlPoints[8]*(py*py);

		for(int v=0; v<=tesselation; ++v)
		{
			px=(float)v/tesselation;

			vertices[u*(tesselation+1)+v]=	temp[0]*((1.0f-px)*(1.0f-px))+
											temp[1]*((1.0f-px)*px*2)+
											temp[2]*(px*px);
		}
	}

	//Create indices
	indices=new GLuint[tesselation*(tesselation+1)*2];
	if(!indices)
	{
		PxLog::LogMessage("Unable to allocate memory for surface indices");
		return false;
	}

	for(int row=0; row<tesselation; ++row)
	{
		for(int point=0; point<=tesselation; ++point)
		{
			//calculate indices
			//reverse them to reverse winding
			indices[(row*(tesselation+1)+point)*2+1]=row*(tesselation+1)+point;
			indices[(row*(tesselation+1)+point)*2]=(row+1)*(tesselation+1)+point;
		}
	}


	//Fill in the arrays for multi_draw_arrays
	trianglesPerRow=new int[tesselation];
	rowIndexPointers=new unsigned int *[tesselation];
	if(!trianglesPerRow || !rowIndexPointers)
	{
		PxLog::LogMessage("Unable to allocate memory for indices for multi_draw_arrays");
		return false;
	}

	for(int row=0; row<tesselation; ++row)
	{
		trianglesPerRow[row]=2*(tesselation+1);
		rowIndexPointers[row]=&indices[row*2*(tesselation+1)];
	}

	return true;
}

