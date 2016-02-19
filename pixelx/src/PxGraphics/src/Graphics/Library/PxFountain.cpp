#include "PxFountain.h"
#include "PxTextureManager.h"
#include "PxCube.h"

#include "PxExtensionManager.h"

PxVector PxFountain::upv( -5,5,-5);
extern int g_debug_tricount;

static bool isBlood = false;
PxFountain::PxFountain(float x,float y,float z)
{
	for(int i = 0; i < NUMBER_OF_STREAMS ; ++i )
		stream[i] = nullptr;
	bBox.x = x - 10;bBox.y = y; bBox.z = z -10;
	bBox.length = 20;bBox.width = 12; bBox.height = 20;
	bBox.Parent = this;
}

void PxFountain::AddParticles()
{
	struct PxParticle * tempp;
	int i, j;
	for ( j = 0 ; j < NUMBER_OF_STREAMS ; ++j)
	{
		for ( i = 0 ; i < 2 ; ++i)
		{
			tempp = (struct PxParticle *)malloc(sizeof(struct PxParticle));
			if (stream[j]) stream[j]->prev = tempp;
			tempp->next = stream[j];
			stream[j] = tempp;

			tempp->t = -0.99f;
			tempp->v = (float)(rand() % 200000)/100000+1; /* Speed */
			tempp->d = (float)(rand() % 200)/100-1;     /* Direction angle: -2..2 */
			tempp->x = 0;
			tempp->y = 0;
			tempp->z = 0;
			tempp->xd = cos((tempp->d*PI)/180)*tempp->v/4;
			tempp->zd = sin((tempp->d*PI)/180)*tempp->v;
			tempp->type = 0;
			tempp->a = 1;
		}
	}
}
void PxFountain::MoveParticles()
{
	struct PxParticle *tempp;
	int j;

	for (j = 0 ; j < NUMBER_OF_STREAMS; ++j )
	{
		tempp = stream[j];
		while (tempp)
		{
			if (tempp->type == 0)
			{
				tempp->x += tempp->xd / 2;
				tempp->z += tempp->zd / 2;
				tempp->y = -( GRAVITY_ACCL *( tempp->t * tempp->t /4 ) )/2+FOUNTAIN_HEIGHT;// v = u + 1/2 gt^2
				tempp->t += 0.1f;
				if (tempp->y < 0)
					tempp->type = 1;
			}
			else
			{
				tempp->y = -( GRAVITY_ACCL * (tempp->t*tempp->t/4) ) / 2 +FOUNTAIN_HEIGHT;
				tempp->a -= 0.1f;
			}
			tempp = tempp->next;
		}
	}
}
void PxFountain::DeleteParticles()
{
	struct PxParticle *tempp, *temp1;
	int j;

	for ( j = 0; j < NUMBER_OF_STREAMS ; ++j)
	{
		tempp = stream[j];
		while (tempp)
		{
			if ((tempp->type == 1) && (tempp->a <= 0))
			{
				temp1 = tempp->prev;
				tempp->prev->next = tempp->next;
				if (tempp->next)
					tempp->next->prev = temp1;
				free(tempp);
				tempp = temp1;
			}
			tempp = tempp->next;
		}
	}
}
void PxFountain::DrawFountain()
{
	int j;
	struct PxParticle *tempp;
	PxVector vectd, vectl;
	float alpha, ttx, ttz;
	static float rotangle = 360.0f / NUMBER_OF_STREAMS;

	if( isBlood )
		PxTextureManager::Bind( "BLOOD" , eTexModeNoStretch );
	else
		PxTextureManager::Bind( "PARTICLE" , eTexModeNoStretch );
	
	AddParticles();
	MoveParticles();
	DeleteParticles();

	glPushMatrix();
	for (j = 0; j< NUMBER_OF_STREAMS ; ++j)
	{
		glBegin(GL_QUADS);
		tempp = stream [j];
		while (tempp)
		{
			
			alpha = ((j*rotangle)*PI)/180;
			ttx = tempp->x*cos(alpha)-tempp->z*sin(alpha);
			ttz = tempp->x*sin(alpha)+tempp->z*cos(alpha);

			vectd.x = ttx;
			vectd.y = tempp->y;
			vectd.z = ttz;

			vectl = PxVector::Cross(vectd,upv);

			vectl.Normalize();

			glColor4f(0.5, 0.5, 1, tempp->a);

			glTexCoord2f(0, 0); glVertex3f((ttx-vectl.x), (tempp->y-upv.y), (ttz-vectl.z));
			glTexCoord2f(1, 0); glVertex3f((ttx+vectl.x), (tempp->y-upv.y), (ttz+vectl.z));
			glTexCoord2f(1, 1); glVertex3f((ttx+vectl.x), (tempp->y+upv.y), (ttz+vectl.z));
			glTexCoord2f(0, 1); glVertex3f((ttx-vectl.x), (tempp->y+upv.y), (ttz-vectl.z));
			g_debug_tricount += 2;
			tempp = tempp->next; 
		}
		glEnd();
	}
	glPopMatrix();
	glColor4f(1,1,1,1);
}
void PxFountain::Register(PxPolygonCollection * coll )
{
	PxCube cube( 
		bBox.x,0.0f,bBox.z,
		bBox.length,0.45f, bBox.height
	);
	cube.SetTexture( "WALL8" );
	cube.Register(coll);
}
void PxFountain::DrawWater()
{
	static float mx = 0.1f;
	static float my = 0.05f;
	
    float wx = bBox.x + 0.5f, wy = bBox.z + 0.5f;
	float wl = bBox.length - 1, ww = bBox.height - 1;

	if( (mx += 0.01f) >= 1.0f ) mx = 0;
	if( (my += 0.01f) >= 1.0f ) my = 0;

	glActiveTextureARB(GL_TEXTURE0_ARB );
	glEnable( GL_TEXTURE_2D );
	PxTextureManager::Bind( "WATER" , eTexModeNoStretch );
	
	glActiveTextureARB(GL_TEXTURE1_ARB );
	glEnable( GL_TEXTURE_2D );
	PxTextureManager::Bind( "WATER" , eTexModeNoStretch );
	
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_ADD_SIGNED_EXT); 
	
	glBegin( GL_QUADS );
		glMultiTexCoord2fARB(GL_TEXTURE0_ARB,0, 0);
		glMultiTexCoord2fARB(GL_TEXTURE1_ARB,0, 0);
		glVertex3f(wx,0.5f,wy);
		glMultiTexCoord2fARB(GL_TEXTURE0_ARB,1, 0);
		glMultiTexCoord2fARB(GL_TEXTURE1_ARB,mx, 0);
		glVertex3f(wx,0.5f,wy + ww);
		glMultiTexCoord2fARB(GL_TEXTURE0_ARB,1, 1);
		glMultiTexCoord2fARB(GL_TEXTURE1_ARB,mx, my);
		glVertex3f(wx + wl,0.5f,wy + ww);
		glMultiTexCoord2fARB(GL_TEXTURE0_ARB,0, 1);
		glMultiTexCoord2fARB(GL_TEXTURE1_ARB,0, 1);
		glVertex3f(wx + wl,0.5f,wy);
	glEnd();

	glActiveTextureARB(GL_TEXTURE0_ARB );
	glDisable( GL_TEXTURE_2D );
	PxTextureManager::Unbind();
	
	glActiveTextureARB(GL_TEXTURE1_ARB );
	glDisable( GL_TEXTURE_2D );
	PxTextureManager::Unbind();

	glDisable(GL_BLEND);
}
void PxFountain::Render()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	DrawWater();
	glPopAttrib();
	
	glPushMatrix();
	glTranslatef( bBox.x + bBox.length / 2 ,bBox.y,bBox.z + bBox.height / 2);
	//glScalef(0.1f, 0.1f, 0.1f);
	glEnable( GL_BLEND );
	glBlendFunc ( GL_SRC_ALPHA , GL_ONE );
	DrawFountain();
	glDisable( GL_BLEND );
	glPopMatrix();
}

void PxFountain::OnCollision()
{
	isBlood = !isBlood;
}

