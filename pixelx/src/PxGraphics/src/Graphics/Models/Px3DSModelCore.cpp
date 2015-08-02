#include "Px3DSModelCore.h"

Px3DSModelCore::Px3DSModelCore(cstrref name)
{
	m_scene.LoadFile( name.c_str() );
	m_scene.SetOptimizationLevel(oFull );
	dispList = glGenLists(1);
	glNewList( dispList , GL_COMPILE );
	for (uint i= 0; i<m_scene.GetMeshCount(); i++)
    {
		LMesh &mesh = m_scene.GetMesh(i);
        glVertexPointer(4, GL_FLOAT, 0, &mesh.GetVertex(0));
        glNormalPointer(GL_FLOAT, 0, &mesh.GetNormal(0));
        glColorPointer(3, GL_FLOAT, 0, &mesh.GetBinormal(0));
        glDrawElements(GL_TRIANGLES, mesh.GetTriangleCount()*3, 
                        GL_UNSIGNED_SHORT, &mesh.GetTriangle(0));

    }
	glEndList();
}
void Px3DSModelCore::Render()
{
	glPushMatrix();
	glRotatef(-90.0f,1,0,0);
	glTranslatef(0,-2,0);
	PxTextureManager::Bind(texid);
	glCallList(dispList);
	glPopMatrix();
}

