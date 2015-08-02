#include "PxBobbingItem.h"

void PxBobbingItem::Render()
{
	if( goingup )
	{
		if( ( yfactor += 0.1f ) > 1.0f)
			goingup = false;
	}
	else
	{
		if( ( yfactor -= 0.1f ) < -1.0f)
			goingup = true;
	}
	if( ( rotangle += 5 ) > 360 )
		rotangle = 0;
	glPushMatrix();
	glTranslatef( bBox.x + bBox.length / 2 , bBox.y + yfactor , bBox.z + bBox.height / 2);
	glRotatef( rotangle , 0 , 1, 0 );
	glScalef(m_scale,m_scale,m_scale);
	m_modelCore->Render();
	glPopMatrix();
}

