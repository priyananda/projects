#include "PxQuakeMapRenderer.h"
#include "PxMultiTextureManager.h"
#include "PxExtensionManager.h"
#include "PxQuake3EntityParser.h"
#include "..\..\PxInput\include\PxConfiguration.h"
#include "gl\glut.h"

PxQuakeMapRenderer::PxQuakeMapRenderer( PxQuakeMap * pMap ) :mMap(pMap)
{
	facesToDraw.Init(mMap->numFaces);
	whiteTexture = PxTextureManager::GetTextureId( "WHITE" );
	PxMultiTextureManager::ToggleVertexArray(true);
	PxMultiTextureManager::ToggleTextureArray(3,true);
}

void PxQuakeMapRenderer::Render(const PxVector & cameraPosition, const PxFrustrum & frustum)
{
	DEFINE_VARB(g_debug_cull);
	
	mMap->CalculateVisibleFaces(cameraPosition,frustum,facesToDraw);
	glFrontFace(GL_CW);
	numTris = 0;
	PxMultiTextureManager::SetActive(1);
	PxMultiTextureManager::SetClientActive(1);

	for(int i = 0; i < mMap->numFaces; ++i)
	{
		if( !g_debug_cull || facesToDraw.IsSet(i))
			DrawFace(i);
	}
	DrawEntities();
}


void PxQuakeMapRenderer::DrawFace(int faceNumber)
{
	if(mMap->faceDirectory[faceNumber].faceType == 0)
		return;
	
	if(mMap->faceDirectory[faceNumber].faceType == bspPolygonFace)
		DrawPolygonFace(mMap->faceDirectory[faceNumber].typeFaceNumber);

	if(mMap->faceDirectory[faceNumber].faceType == bspMeshFace)
		DrawMeshFace(mMap->faceDirectory[faceNumber].typeFaceNumber);

	if(mMap->faceDirectory[faceNumber].faceType == bspPatch)
		DrawPatch(mMap->faceDirectory[faceNumber].typeFaceNumber);
}


void PxQuakeMapRenderer::DrawPolygonFace(int polygonFaceNumber)
{
	if(mMap->isTextureLoaded[mMap->polygonFaces[polygonFaceNumber].textureIndex]==false)
		return;
	PxMultiTextureManager::SetVertexPointer(3, GL_FLOAT, sizeof(PxBSPVertex), &mMap->vertices[0].position);
	PxMultiTextureManager::SetTexCoordPointer( 1 , 2, GL_FLOAT, sizeof(PxBSPVertex), &mMap->vertices[0].decalS);
	PxMultiTextureManager::SetTexCoordPointer( 2 , 2, GL_FLOAT, sizeof(PxBSPVertex), &mMap->vertices[0].lightmapS);
	PxMultiTextureManager::Bind(1 , mMap->decalTextures[mMap->polygonFaces[polygonFaceNumber].textureIndex]);
	if(mMap->polygonFaces[polygonFaceNumber].lightmapIndex >= 0)
		PxMultiTextureManager::Bind(
			2,
			mMap->lightmapTextures[mMap->polygonFaces[polygonFaceNumber].lightmapIndex],
			eTexModeNoStretch
		);
	else
		PxMultiTextureManager::Bind(
			2,
			whiteTexture,
			eTexModeNoStretch
		);
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glDrawArrays(	GL_TRIANGLE_FAN, mMap->polygonFaces[polygonFaceNumber].firstVertexIndex,
									 mMap->polygonFaces[polygonFaceNumber].numVertices);
	numTris += mMap->polygonFaces[polygonFaceNumber].numVertices - 2;
}

void PxQuakeMapRenderer::DrawMeshFace(int meshFaceNumber)
{
	//skip this face if its texture was not loaded
	if(mMap->isTextureLoaded[mMap->meshFaces[meshFaceNumber].textureIndex]==false)
		return;

	//set array pointers
	glVertexPointer(	3, GL_FLOAT, sizeof(PxBSPVertex),
						&mMap->vertices[mMap->meshFaces[meshFaceNumber].firstVertexIndex].position);
	glTexCoordPointer(	2, GL_FLOAT, sizeof(PxBSPVertex),
						&mMap->vertices[mMap->meshFaces[meshFaceNumber].firstVertexIndex].decalS);

	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glTexCoordPointer(	2, GL_FLOAT, sizeof(PxBSPVertex),
						&mMap->vertices[mMap->meshFaces[meshFaceNumber].firstVertexIndex].lightmapS);
	glClientActiveTextureARB(GL_TEXTURE0_ARB);


	//bind textures
	//unit 0 - decal texture
	PxTextureManager::Bind( mMap->decalTextures[mMap->meshFaces[meshFaceNumber].textureIndex] , eTexModeNoStretch);

	//unit 1 - lightmap
	glActiveTextureARB(GL_TEXTURE1_ARB);
	if(mMap->meshFaces[meshFaceNumber].lightmapIndex>=0)	//only bind a lightmap if one exists
		glBindTexture(GL_TEXTURE_2D, mMap->lightmapTextures[mMap->meshFaces[meshFaceNumber].lightmapIndex]);
	else
		glBindTexture(GL_TEXTURE_2D, whiteTexture);
	glActiveTextureARB(GL_TEXTURE0_ARB);


	if( ! PxExtensionManager::IsEnabled(EXT_DRAWRANGEELEMENTS))
		glDrawElements(
			GL_TRIANGLES,mMap->meshFaces[meshFaceNumber].numMeshIndices, 
			GL_UNSIGNED_INT,
			&mMap->meshIndices[mMap->meshFaces[meshFaceNumber].firstMeshIndex]
		);
	else
		glDrawRangeElementsEXT(
			GL_TRIANGLES,
			0,
			mMap->meshFaces[meshFaceNumber].numVertices,
			mMap->meshFaces[meshFaceNumber].numMeshIndices,
			GL_UNSIGNED_INT,
			&mMap->meshIndices[mMap->meshFaces[meshFaceNumber].firstMeshIndex]
		);
	numTris += mMap->meshFaces[meshFaceNumber].numVertices / 3;
}

void PxQuakeMapRenderer::DrawPatch(int patchNumber)
{
	//skip this patch if its texture was not loaded
	if(mMap->isTextureLoaded[mMap->patches[patchNumber].textureIndex]==false)
		return;

	//bind textures
	//unit 0 - decal texture
	PxTextureManager::Bind( mMap->decalTextures[mMap->patches[patchNumber].textureIndex] , eTexModeNoStretch);

	//unit 1 - lightmap
	glActiveTextureARB(GL_TEXTURE1_ARB);
	if(mMap->patches[patchNumber].lightmapIndex>=0)	//only bind a lightmap if one exists
		glBindTexture(GL_TEXTURE_2D, mMap->lightmapTextures[mMap->patches[patchNumber].lightmapIndex]);
	else
		glBindTexture(GL_TEXTURE_2D, whiteTexture);
	glActiveTextureARB(GL_TEXTURE0_ARB);

	for(int i=0; i< mMap->patches[patchNumber].numQuadraticPatches; ++i)
		DrawBiquadraticPatch( & mMap->patches[patchNumber].quadraticPatches[i] );
}


void PxQuakeMapRenderer::DrawBiquadraticPatch(PxBSPBiquadraticPatch * pQuad)
{
	//set array pointers
	glVertexPointer(3, GL_FLOAT, sizeof(PxBSPVertex), &pQuad->vertices[0].position);
		
	glTexCoordPointer(2, GL_FLOAT, sizeof(PxBSPVertex), &pQuad->vertices[0].decalS);
	
	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glTexCoordPointer(2, GL_FLOAT, sizeof(PxBSPVertex), &pQuad->vertices[0].lightmapS);
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	
	//Draw a triangle strip for each row
	if(! PxExtensionManager::IsEnabled( EXT_MULTIDRAWARRAY ) )
	{
		for(int row=0; row<pQuad->tesselation; ++row)
		{
			glDrawElements(	GL_TRIANGLE_STRIP, 2*(pQuad->tesselation+1), GL_UNSIGNED_INT,
							&pQuad->indices[row*2*(pQuad->tesselation+1)]);
		}
	}
	else
	{
		glMultiDrawElementsEXT(	GL_TRIANGLE_STRIP, pQuad->trianglesPerRow,
								GL_UNSIGNED_INT, (const void **)pQuad->rowIndexPointers,
								pQuad->tesselation);
	}
}

void PxQuakeMapRenderer::RenderBoundingBox()
{
	mMap->boundingBox.Render();
}

void PxQuakeMapRenderer::DrawEntities()
{
	return;
	PxQuake3Entity & entity = mMap->entities[1];
	glPushMatrix();
	PxTextureManager::Bind( "BLUE" );
	glTranslatef( entity.Origin.x , entity.Origin.y, entity.Origin.z );
	//auxSolidSphere(1.0f);
	glPopMatrix();
}

