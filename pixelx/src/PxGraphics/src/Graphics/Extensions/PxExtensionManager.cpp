#include "PxExtensionManager.h"

static string g_extensions[] =
{
	"GL_EXT_draw_range_elements",
	"GL_ARB_multitexture",
	"GL_EXT_multi_draw_arrays",
	"GL_EXT_texture_env_combine",
	"WGL_EXT_swap_control"
};
static bool g_flags[] = 
{
	true,
	true,
	true,
	true,
	true
};
static const int g_extensionsSize = 5;

void SetupARBMultitexture();
void SetupEXTDrawRangeElements();
void SetupEXTMultiDrawArrays();
void SetupEXTSwapControl();

void PxExtensionManager::Init()
{
	string extensionString((char *)glGetString(GL_EXTENSIONS));
	PxLog::LogMessage( extensionString.c_str() );
	for( int i = 0 ; i < g_extensionsSize ; ++i )
		if( extensionString.find( g_extensions[i] ) == extensionString.npos )
		{
			PxLog::LogMessage("Extension %s not found!!!" , g_extensions[i].c_str() );
			g_flags[i] = false;
		}

	if( ! g_flags[ ARB_MULTITEXTURE ] || ! g_flags[ EXT_TEXENVCOMBINE ])
		exit(0);
	SetupARBMultitexture();
	SetupEXTDrawRangeElements();
	SetupEXTMultiDrawArrays();
	SetupEXTSwapControl();
}

bool PxExtensionManager::IsEnabled( PxExtensions e )
{
	return g_flags[e];
}
void SetupEXTDrawRangeElements()
{
	glDrawRangeElementsEXT			=	(PFNGLDRAWRANGEELEMENTSEXTPROC)
										wglGetProcAddress("glDrawRangeElementsEXT");
}
void SetupARBMultitexture()
{
	//get function pointers
	glActiveTextureARB			=	(PFNGLACTIVETEXTUREARBPROC)
									wglGetProcAddress("glActiveTextureARB");
	glClientActiveTextureARB	=	(PFNGLCLIENTACTIVETEXTUREARBPROC)
									wglGetProcAddress("glClientActiveTextureARB");
	glMultiTexCoord1dARB		=	(PFNGLMULTITEXCOORD1DARBPROC)
									wglGetProcAddress("glMultiTexCoord1dARB");
	glMultiTexCoord1dvARB		=	(PFNGLMULTITEXCOORD1DVARBPROC)
									wglGetProcAddress("glMultiTexCoord1dvARB");
	glMultiTexCoord1fARB		=	(PFNGLMULTITEXCOORD1FARBPROC)
									wglGetProcAddress("glMultiTexCoord1fARB");
	glMultiTexCoord1fvARB		=	(PFNGLMULTITEXCOORD1FVARBPROC)
									wglGetProcAddress("glMultiTexCoord1fvARB");
	glMultiTexCoord1iARB		=	(PFNGLMULTITEXCOORD1IARBPROC)
									wglGetProcAddress("glMultiTexCoord1iARB");
	glMultiTexCoord1ivARB		=	(PFNGLMULTITEXCOORD1IVARBPROC)
									wglGetProcAddress("glMultiTexCoord1ivARB");
	glMultiTexCoord1sARB		=	(PFNGLMULTITEXCOORD1SARBPROC)
									wglGetProcAddress("glMultiTexCoord1sARB");
	glMultiTexCoord1svARB		=	(PFNGLMULTITEXCOORD1SVARBPROC)
									wglGetProcAddress("glMultiTexCoord1svARB");
	glMultiTexCoord2dARB		=	(PFNGLMULTITEXCOORD2DARBPROC)
									wglGetProcAddress("glMultiTexCoord2dARB");
	glMultiTexCoord2dvARB		=	(PFNGLMULTITEXCOORD2DVARBPROC)
									wglGetProcAddress("glMultiTexCoord2dvARB");
	glMultiTexCoord2fARB		=	(PFNGLMULTITEXCOORD2FARBPROC)
									wglGetProcAddress("glMultiTexCoord2fARB");
	glMultiTexCoord2fvARB		=	(PFNGLMULTITEXCOORD2FVARBPROC)
									wglGetProcAddress("glMultiTexCoord2fvARB");
	glMultiTexCoord2iARB		=	(PFNGLMULTITEXCOORD2IARBPROC)
									wglGetProcAddress("glMultiTexCoord2iARB");
	glMultiTexCoord2ivARB		=	(PFNGLMULTITEXCOORD2IVARBPROC)
									wglGetProcAddress("glMultiTexCoord2ivARB");
	glMultiTexCoord2sARB		=	(PFNGLMULTITEXCOORD2SARBPROC)
									wglGetProcAddress("glMultiTexCoord2sARB");
	glMultiTexCoord2svARB		=	(PFNGLMULTITEXCOORD2SVARBPROC)
									wglGetProcAddress("glMultiTexCoord2svARB");
	glMultiTexCoord3dARB		=	(PFNGLMULTITEXCOORD3DARBPROC)
									wglGetProcAddress("glMultiTexCoord3dARB");
	glMultiTexCoord3dvARB		=	(PFNGLMULTITEXCOORD3DVARBPROC)
									wglGetProcAddress("glMultiTexCoord3dvARB");
	glMultiTexCoord3fARB		=	(PFNGLMULTITEXCOORD3FARBPROC)
									wglGetProcAddress("glMultiTexCoord3fARB");
	glMultiTexCoord3fvARB		=	(PFNGLMULTITEXCOORD3FVARBPROC)
									wglGetProcAddress("glMultiTexCoord3fvARB");
	glMultiTexCoord3iARB		=	(PFNGLMULTITEXCOORD3IARBPROC)
									wglGetProcAddress("glMultiTexCoord3iARB");
	glMultiTexCoord3ivARB		=	(PFNGLMULTITEXCOORD3IVARBPROC)
									wglGetProcAddress("glMultiTexCoord3ivARB");
	glMultiTexCoord3sARB		=	(PFNGLMULTITEXCOORD3SARBPROC)
									wglGetProcAddress("glMultiTexCoord3sARB");
	glMultiTexCoord3svARB		=	(PFNGLMULTITEXCOORD3SVARBPROC)
									wglGetProcAddress("glMultiTexCoord3svARB");
	glMultiTexCoord4dARB		=	(PFNGLMULTITEXCOORD4DARBPROC)
									wglGetProcAddress("glMultiTexCoord4dARB");
	glMultiTexCoord4dvARB		=	(PFNGLMULTITEXCOORD4DVARBPROC)
									wglGetProcAddress("glMultiTexCoord4dvARB");
	glMultiTexCoord4fARB		=	(PFNGLMULTITEXCOORD4FARBPROC)
									wglGetProcAddress("glMultiTexCoord4fARB");
	glMultiTexCoord4fvARB		=	(PFNGLMULTITEXCOORD4FVARBPROC)
									wglGetProcAddress("glMultiTexCoord4fvARB");
	glMultiTexCoord4iARB		=	(PFNGLMULTITEXCOORD4IARBPROC)
									wglGetProcAddress("glMultiTexCoord4iARB");
	glMultiTexCoord4ivARB		=	(PFNGLMULTITEXCOORD4IVARBPROC)
									wglGetProcAddress("glMultiTexCoord4ivARB");
	glMultiTexCoord4sARB		=	(PFNGLMULTITEXCOORD4SARBPROC)
									wglGetProcAddress("glMultiTexCoord4sARB");
	glMultiTexCoord4svARB		=	(PFNGLMULTITEXCOORD4SVARBPROC)
									wglGetProcAddress("glMultiTexCoord4svARB");
}

void SetupEXTMultiDrawArrays()
{
	glMultiDrawArraysEXT			=	(PFNGLMULTIDRAWARRAYSEXTPROC)
										wglGetProcAddress("glMultiDrawArraysEXT");
	glMultiDrawElementsEXT			=	(PFNGLMULTIDRAWELEMENTSEXTPROC)
										wglGetProcAddress("glMultiDrawElementsEXT");
}

void SetupEXTSwapControl()
{
	wglSwapIntervalEXT				=	(PFNWGLSWAPINTERVALEXTPROC)
										wglGetProcAddress("wglSwapIntervalEXT");
}

PFNGLACTIVETEXTUREARBPROC				glActiveTextureARB				=nullptr;
PFNGLCLIENTACTIVETEXTUREARBPROC			glClientActiveTextureARB		=nullptr;
PFNGLMULTITEXCOORD1DARBPROC				glMultiTexCoord1dARB			=nullptr;
PFNGLMULTITEXCOORD1DVARBPROC			glMultiTexCoord1dvARB			=nullptr;
PFNGLMULTITEXCOORD1FARBPROC				glMultiTexCoord1fARB			=nullptr;
PFNGLMULTITEXCOORD1FVARBPROC			glMultiTexCoord1fvARB			=nullptr;
PFNGLMULTITEXCOORD1IARBPROC				glMultiTexCoord1iARB			=nullptr;
PFNGLMULTITEXCOORD1IVARBPROC			glMultiTexCoord1ivARB			=nullptr;
PFNGLMULTITEXCOORD1SARBPROC				glMultiTexCoord1sARB			=nullptr;
PFNGLMULTITEXCOORD1SVARBPROC			glMultiTexCoord1svARB			=nullptr;
PFNGLMULTITEXCOORD2DARBPROC				glMultiTexCoord2dARB			=nullptr;
PFNGLMULTITEXCOORD2DVARBPROC			glMultiTexCoord2dvARB			=nullptr;
PFNGLMULTITEXCOORD2FARBPROC				glMultiTexCoord2fARB			=nullptr;
PFNGLMULTITEXCOORD2FVARBPROC			glMultiTexCoord2fvARB			=nullptr;
PFNGLMULTITEXCOORD2IARBPROC				glMultiTexCoord2iARB			=nullptr;
PFNGLMULTITEXCOORD2IVARBPROC			glMultiTexCoord2ivARB			=nullptr;
PFNGLMULTITEXCOORD2SARBPROC				glMultiTexCoord2sARB			=nullptr;
PFNGLMULTITEXCOORD2SVARBPROC			glMultiTexCoord2svARB			=nullptr;
PFNGLMULTITEXCOORD3DARBPROC				glMultiTexCoord3dARB			=nullptr;
PFNGLMULTITEXCOORD3DVARBPROC			glMultiTexCoord3dvARB			=nullptr;
PFNGLMULTITEXCOORD3FARBPROC				glMultiTexCoord3fARB			=nullptr;
PFNGLMULTITEXCOORD3FVARBPROC			glMultiTexCoord3fvARB			=nullptr;
PFNGLMULTITEXCOORD3IARBPROC				glMultiTexCoord3iARB			=nullptr;
PFNGLMULTITEXCOORD3IVARBPROC			glMultiTexCoord3ivARB			=nullptr;
PFNGLMULTITEXCOORD3SARBPROC				glMultiTexCoord3sARB			=nullptr;
PFNGLMULTITEXCOORD3SVARBPROC			glMultiTexCoord3svARB			=nullptr;
PFNGLMULTITEXCOORD4DARBPROC				glMultiTexCoord4dARB			=nullptr;
PFNGLMULTITEXCOORD4DVARBPROC			glMultiTexCoord4dvARB			=nullptr;
PFNGLMULTITEXCOORD4FARBPROC				glMultiTexCoord4fARB			=nullptr;
PFNGLMULTITEXCOORD4FVARBPROC			glMultiTexCoord4fvARB			=nullptr;
PFNGLMULTITEXCOORD4IARBPROC				glMultiTexCoord4iARB			=nullptr;
PFNGLMULTITEXCOORD4IVARBPROC			glMultiTexCoord4ivARB			=nullptr;
PFNGLMULTITEXCOORD4SARBPROC				glMultiTexCoord4sARB			=nullptr;
PFNGLMULTITEXCOORD4SVARBPROC			glMultiTexCoord4svARB			=nullptr;

//DrawRangeElements
PFNGLDRAWRANGEELEMENTSEXTPROC			glDrawRangeElementsEXT			=nullptr;

//Draw Multi Arrays
PFNGLMULTIDRAWARRAYSEXTPROC				glMultiDrawArraysEXT			=nullptr;
PFNGLMULTIDRAWELEMENTSEXTPROC			glMultiDrawElementsEXT			=nullptr;

//Texture Env Combine
//--

//SwapControl
PFNWGLSWAPINTERVALEXTPROC				wglSwapIntervalEXT				=nullptr;

