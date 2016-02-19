#include "PxTriangleSet.h"

static string CreateHash(cstrref tname, TextureMode mode)
{
	static char buff[100];
	sprintf_s(buff, 100, "%s%d", tname.c_str() , mode );
	return string(buff);
}

PxMesh::PxMesh(cstrref texname,TextureMode mode )
	:mTriangleArray(nullptr),TextureName(texname),TexMode(mode),mTriangleCount(0)
{
}

void PxMesh::AddTriangle(PxTriangle & pt )
{
	mTriangles.push_back(pt);
}

void PxMesh::Finalize()
{
	mTriangleCount = mTriangles.size();
	mTriangleArray = new PxTriangle[mTriangleCount];
	for( int i = 0 ; i < mTriangleCount ; ++i )
	{
		mTriangleArray[i] = mTriangles[i];
	}
	mTriangles.clear();
}

void PxMesh::Render()
{
	if( TextureName != "" )
		PxTextureManager::Bind( TextureName , TexMode );
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(	3, GL_FLOAT, sizeof(PxVertex), &mTriangleArray[0].first.x);
	glTexCoordPointer(	2, GL_INT, sizeof(PxVertex), &mTriangleArray[0].first.u);
	glDrawArrays( GL_TRIANGLES , 0 , mTriangleCount * 3 );
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

PxMesh * PxMeshes::GetMesh( cstrref texname , TextureMode mode )
{
	PxMesh * ret = nullptr;
	string hash = CreateHash(texname,mode);
	if( mMeshes.find(hash) == mMeshes.end() )
	{
		ret = new PxMesh(texname,mode);
		mMeshes[hash] = ret;
	}else
		ret = mMeshes[hash];
	return ret;
}
void PxMeshes::Clear()
{
	for(PxMeshes::Iterator iter = begin() ; iter != end(); ++iter)
	{
		PxMesh * pMesh = iter->second;
		delete pMesh;
	}
	mMeshes.clear();
}
PxMesh::~PxMesh()
{
	mTriangles.clear();
	if( mTriangleArray )
	{
		delete [] mTriangleArray;
		mTriangleArray = nullptr;
	}
}
PxTriangleSet::PxTriangleSet( )
{
	dispList = -1;
}

void PxTriangleSet::AddTriangle( cstrref texname , TextureMode mode, PxTriangle & pt )
{
	PxMesh * pMesh = mMeshes.GetMesh(texname,mode);
	if( pMesh != nullptr )
		pMesh->AddTriangle(pt);
}

void PxTriangleSet::Render()
{
	if( dispList == -1 )
	{
		dispList = glGenLists(1);
		glNewList( dispList , GL_COMPILE );
		for(PxMeshes::Iterator iter = mMeshes.begin() ; iter != mMeshes.end(); ++iter)
		{
			PxMesh * pMesh = iter->second;
			pMesh->Render();
		}
		glEndList();
		mMeshes.Clear();
	}
	glCallList(dispList);
}

PxTriangleSet::~PxTriangleSet()
{
}

void PxTriangleSet::Finalize()
{
	for(PxMeshes::Iterator iter = mMeshes.begin() ; iter != mMeshes.end(); ++iter)
	{
		PxMesh * pMesh = iter->second;
		pMesh->Finalize();
	}
}

