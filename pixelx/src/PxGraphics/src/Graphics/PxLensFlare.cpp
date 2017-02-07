#include "PxLensFlare.h"
#include "PxTextureManager.h"
#include "Interfaces.h"
#include "PxWindow.h"

#define HEIGHTFROMWIDTH(w)  ((w)*screenHeight/screenWidth)
#define isqrt(x)        (int)((double)(x))

void PxLensFlareRenderer::RenderFlare(long lx, long ly)
{
    int     dx, dy;          // Screen coordinates of "destination"
    int     px, py;          // Screen coordinates of flare element
    int     maxflaredist, flaredist, flaremaxsize, flarescale;
    int     width, height, alpha;    // Piece parameters;
    int     i;
    PxFlareElement    *element;

    // Compute how far off-center the flare source is.
    maxflaredist = isqrt(cx*cx + cy*cy);
    flaredist = isqrt((lx - cx)*(lx - cx)+
                      (ly - cy)*(ly - cy));
    flaredist = (maxflaredist - flaredist);
    flaremaxsize = (int)(screenWidth * m_flare.maxSize );
    flarescale = (int)(screenWidth * m_flare.scale );

    // Destination is opposite side of centre from source
    dx = cx + (cx - lx);
    dy = cy + (cy - ly);

    // Render each element.
    for (i = 0; i < m_flare.numElements; ++i)
    {
        element = &m_flare.elements[i];

        // Position is interpolated along line between start and destination.
        px = (int)((1.0f - element->distance)*lx + element->distance*dx);
        py = (int)((1.0f - element->distance)*ly + element->distance*dy);

        // Piece size are 0 to 1; flare size is proportion of
        // screen width; scale by flaredist/maxflaredist.
        width = (int)((flaredist*flarescale*element->size)/maxflaredist);

        // Width gets clamped, to allows the off-axis flares
        // to keep a good size without letting the elements get
        // too big when centered.
        if (width > flaremaxsize)
        {
            width = flaremaxsize;
        }

        // Flare elements are square (round) so height is just
        // width scaled by aspect ratio.
        height = HEIGHTFROMWIDTH(width);
        alpha = (flaredist*(element->ARGB >> 24))/maxflaredist;

        if ( width > 1 )
        {
            unsigned int    argb = (alpha << 24 ) | (element->ARGB & 0x00ffffff);

            DrawQuad( px - width/2, py - height/2, width, height, element->textureID, argb );
        }
    }
}

void PxLensFlareRenderer::DrawQuad( int x, int y, int width, int height, GLuint texID, unsigned int colour )
{
	PxTextureManager::Bind( texID , TextureMode::NoStretch );

    glBegin(GL_QUADS);

    glColor4ub( (GLbyte)(colour >> 16 & 0xff),
                (GLbyte)(colour >>  8 & 0xff),
                (GLbyte)(colour >>  0 & 0xff),
                (GLbyte)(colour >> 24 & 0xff) );

	GLfloat fx = (GLfloat)x, fy = (GLfloat)y;

    glTexCoord2f( 0.0f, 0.0f );
    glVertex3f( fx, fy, 1.0);
    glTexCoord2f( 1.0f, 0.0f );
    glVertex3f( fx + width, fy, 1.0);
    glTexCoord2f( 1.0f, 1.0f );
    glVertex3f( fx + width, fy + height, 1.0);
    glTexCoord2f( 0.0f, 1.0f );
    glVertex3f( fx, fy + height, 1.0);

    glEnd();
}

PxLensFlareRenderer::PxLensFlareRenderer( PxVertex & sun )
	:m_sunPosition(sun)
{
	screenHeight = PxWindow::Window()->ScreenHeight;
	screenWidth = PxWindow::Window()->ScreenWidth;

	cx = screenWidth / 2;
	cy = screenHeight / 2;

	m_flare = PxFlare(2);
	/*m_flare.elements[0].textureID = PxTextureManager::GetTextureId("RING");
	m_flare.elements[0].distance = 0;
	m_flare.elements[0].size = 0.7f;
	m_flare.elements[0].ARGB = ( 255 << 24 ) | ( 225 << 16 ) | ( 170 << 8 ) | ( 170 << 0 );*/

	m_flare.elements[1].textureID = PxTextureManager::GetTextureId("RING");
	m_flare.elements[1].distance = 0;
	m_flare.elements[1].size = 0.1f;
	m_flare.elements[1].ARGB = ( 255 << 24 ) | ( 173 << 16 ) | ( 131 << 8 ) | ( 138 << 0 );

	m_flare.elements[0].textureID = PxTextureManager::GetTextureId("RING");
	m_flare.elements[0].distance = 0.1f;
	m_flare.elements[0].size = 0.1f;
	m_flare.elements[0].ARGB = ( 255 << 24 ) | ( 100 << 16 ) | ( 120 << 8 ) | ( 150 << 0 );

	/*m_flare.elements[3].textureID = PxTextureManager::GetTextureId("RING");
	m_flare.elements[3].distance = 0.35f;
	m_flare.elements[3].size = 0.25f;
	m_flare.elements[3].ARGB = ( 255 << 24 ) | ( 145 << 16 ) | ( 110 << 8 ) | ( 100 << 0 );*/

	glFeedbackBuffer(3, GL_2D, m_sunProjection );
}

void PxLensFlareRenderer::Render( PxVector & cameraPoistion )
{
	/*m_sunPosition = PxVertex(
		25.0 + cameraPoistion.x,
		20.0 + cameraPoistion.y,
		-35.0 + cameraPoistion.z
	);*/
	m_sunProjection[1] = m_sunProjection[2] = -1;
	
	glRenderMode(GL_FEEDBACK);
    glBegin(GL_POINTS);
		glVertex3fv(&m_sunPosition.x);
    glEnd();
    glRenderMode(GL_RENDER);
	if( m_sunProjection[1] == -1 ||  m_sunProjection[2] == -1 )
		return;
	m_sunProjection[1] = (float)abs((int)m_sunProjection[1] - 400);
	m_sunProjection[2] = (float)abs((int)m_sunProjection[2] - 300);

	PxGraphicsRoot::Switch();
	glPushAttrib( GL_ALL_ATTRIB_BITS );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	RenderFlare((long)m_sunProjection[1], (long)m_sunProjection[2]);
	glPopAttrib();
	PxGraphicsRoot::Restore();
}
/*
ring  0.0  0.7  ( 255 225 170 170 )
flar  0.0  0.7  ( 255 173 131 138 )
crcl  0.3  0.25 ( 255 100 120 150 )
crcl  0.35 0.25 ( 255 145 110 100 )
*/

