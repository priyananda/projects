#ifndef _PIXELX_TRIANGLESET_H
#define _PIXELX_TRIANGLESET_H

#include "PxVertex.h"
#include "PxTextureManager.h"

#include <unordered_map>
using std::unordered_map;

#include <vector>
using std::vector;

struct PxTriangle
{
	PxVertex first,second,third;
	PxVertex & operator [](int i)
	{
		if( i == 0 )
			return first;
		if( i == 1 )
			return second;
		if( i == 2 )
			return third;
		throw std::out_of_range("PxTriangle[]");
	}
};
struct PxMesh
{
	string TextureName;
	TextureMode TexMode;

	PxMesh( cstrref texname, TextureMode texmode );
	~PxMesh();

	void AddTriangle( PxTriangle & pt );
	void Finalize();
	void Render();
	long NumTriangles(){ return (long)mTriangles.size(); }
	PxTriangle & operator[](int i){ return mTriangles[i]; }
private:
	vector<PxTriangle> mTriangles;
	PxTriangle * mTriangleArray;
	int mTriangleCount;
};

class PxMeshes
{
public:
	PxMesh * GetMesh( cstrref texname , TextureMode mode );
	long Count(){ return (long)mMeshes.size(); }
	typedef unordered_map<string,PxMesh *>::iterator Iterator;
	Iterator begin(){ return mMeshes.begin(); }
	Iterator end(){ return mMeshes.end(); }

	void Clear();
private:
	unordered_map<string,PxMesh *> mMeshes;
};
class PxTriangleSet
{
public:
	PxTriangleSet();
	~PxTriangleSet();

	void AddTriangle( cstrref texName, TextureMode mode, PxTriangle & pt );
	long NumMeshes(){ return mMeshes.Count(); }
	void Render();
	void Finalize();
	PxMeshes::Iterator begin(){ return mMeshes.begin(); }
	PxMeshes::Iterator end(){ return mMeshes.end(); }
private:
	GLint dispList;
	PxMeshes mMeshes;
};
#endif

