#include "PxModel.h"

void PxModel::Register(PxPolygonCollection * pcoll)
{
	m_modelCore->Register(pcoll);
}

void PxModel::Render()
{
	glPushMatrix();
	glTranslatef( bBox.x + bBox.length / 2 , bBox.y + bBox.width / 2, bBox.z + bBox.height / 2);
	if( m_angle )
		glRotatef( m_angle , 0 , 1 , 0 );
	glScalef(m_scale,m_scale,m_scale);
	m_modelCore->Render();
	glPopMatrix();
}

void PxModel::Animate(int sf, int ef , float interp)
{
	glPushMatrix();
	glTranslatef( bBox.x + bBox.length / 2 , bBox.y + bBox.width / 2 , bBox.z + bBox.height / 2);
	if( m_angle )
		glRotatef( m_angle , 0 , 1 , 0 );
	glScalef(m_scale,m_scale,m_scale);
	m_modelCore->Animate(sf,ef,interp);
	glPopMatrix();
}

