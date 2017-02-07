#include "PxTextWriter.h"
#include "PxTextureManager.h"
#include "PxWin32Window.h"
#include "../../PxInput/include/PxConfiguration.h"

static GLYPHMETRICSFLOAT gmf[256];

GLuint PxTextWriter::m_a,PxTextWriter::m_b,PxTextWriter::m_r,PxTextWriter::m_g;
GLuint PxTextWriter::m_size = 10;
GLuint PxTextWriter::m_texid = 0;
GLuint PxTextWriter::m_base = 0;

static void Decode( string & name )
{
	int len = name.length();
	for(int i = 0 ; i < len ; ++i )
		if( name[i] == '+' )
			name[i] = ' ';
}
void PxTextWriter::Init()
{
	HFONT	font;
	m_base = glGenLists(256);

	string fontname = PxConfiguration::GetString("g_debug_font");
	Decode(fontname);
	font = CreateFont(
		-12,
		0,
		0,				// Angle Of Escapement
		0,				// Orientation Angle
		FW_BOLD,		// Font Weight
		FALSE,				// Italic
		FALSE,				// Underline
		FALSE,				// Strikeout
		ANSI_CHARSET,			// Character Set Identifier
		OUT_STRING_PRECIS,			// Output Precision
		CLIP_DEFAULT_PRECIS,		// Clipping Precision
		ANTIALIASED_QUALITY,		// Output Quality
		FF_DONTCARE|DEFAULT_PITCH,	// Family And Pitch
		fontname.c_str()
	);
	HDC hdc = wglGetCurrentDC();
	SelectObject(
		hdc,
		font
	);
	wglUseFontOutlines(	
		hdc,
		0,				// Starting Character
		255,				// Number Of Display Lists To Build
		m_base,				// Starting Display Lists
		0.0f,				// Deviation From The True Outlines
		0.2f,				// Font Thickness In The Z Direction
		WGL_FONT_POLYGONS,		// Use Polygons, Not Lines
		gmf
	);
}

void PxTextWriter::SetTexture( GLuint id )
{
	m_texid = id;
}

void PxTextWriter::SetTexture( cstrref name )
{
	SetTexture( PxTextureManager::GetTextureId( name ) );
}
void PxTextWriter::SetColor(GLuint r,GLuint g, GLuint b, GLuint a )
{
	m_a = a;m_b = b; m_g = g;m_r = r;
	m_texid = 0;
}
void PxTextWriter::SetSize( GLuint size )
{
	m_size = size;
}

void PxTextWriter::Write(int x, int y,cstrref name)
{
	glPushMatrix();
    glPushAttrib(GL_LIST_BIT);

	glTranslated(x,y,0);
	glScalef(20.0f * m_size ,20.0f * m_size,20.0f * m_size);
	glDisable( GL_BLEND );

	if( m_texid != 0 )
		PxTextureManager::Bind(m_texid);
	else{
		PxTextureManager::Unbind();
		glColor4ub( m_r,m_g,m_b,m_a);
	}
	glListBase(m_base);
	glCallLists(name.length(), GL_UNSIGNED_BYTE, name.c_str());	// Draws The Display List Text

	glLoadIdentity();
	glColor3ub(255,255,255);
	glPopAttrib();
	glPopMatrix();
}

void PxTextWriter::Write( int x, int y, cstrref text, GLuint size )
{
	SetSize(size);
	Write(x,y,text);
}
void PxTextWriter::Write( int x, int y, cstrref text, GLuint size,GLuint r,GLuint g, GLuint b, GLuint a)
{
	SetColor(r,g,b,a);
	SetSize(size);
	Write(x,y,text);
}
void PxTextWriter::Write( int x, int y, cstrref text, GLuint size,cstrref texname )
{
	SetTexture(texname);
	SetSize(size);
	Write(x,y,text);
}

