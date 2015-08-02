#include "PxWaveFrontModel.h"
#include "PxTextureManager.h"

PxWaveFrontModelCore::PxWaveFrontModelCore( cstrref filename )
	:displayList(0)
{
	m_model = glmReadOBJ((char *)filename.c_str());
	glmUnitize(m_model);
	glmFacetNormals(m_model);
	glmVertexNormals(m_model, 90.0);
	glmScale(m_model,2);
}

void PxWaveFrontModelCore::Render()
{
	static	GLfloat pos[] = { 0.0, 5.0, 0.0, 0.0 },
			col[] = { 1.0f, 0.5f, 2.0f ,1.0f};

	if( displayList == 0 )
	{
		displayList = glGenLists(1);
		glNewList( displayList , GL_COMPILE );
			PxTextureManager::Unbind();
			glEnable(GL_LIGHTING);
			glEnable( GL_LIGHT0 );
			glDisable( GL_TEXTURE_2D );
			glDisable( GL_BLEND );
			glPushMatrix();
			glColor3ub(0,0,0);
			glLightfv(GL_LIGHT0, GL_POSITION, pos);
			glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE , col );
			glPopMatrix();
			glEnable( GL_TEXTURE_2D );
			glmDraw(m_model, GLM_SMOOTH | GLM_MATERIAL );
			glDisable( GL_LIGHT0 );
			glDisable(GL_LIGHTING);
			glColor3ub(255,255,255);
		glEndList();
	}
	glCallList(displayList);
}

void PxWaveFrontModelCore::SetTexture(cstrref name)
{

}

