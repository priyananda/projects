#include "PxImageProvider.h"
#include "il/il.h"
#include "il/ilu.h"
#include "il/ilut.h"

using std::basic_string;

inline bool EndsWith( cstrref name, cstrref extn )
{
	return name.rfind( extn ) == name.length() -  extn.length();
}

void PxImageProvider::Init()
{
	ilInit();
	iluInit();
	ilutRenderer(ILUT_OPENGL);
	Reset();
}

void PxImageProvider::Reset()
{
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_UPPER_LEFT);
}

GLuint PxImageProvider::CreateTexture(
	cstrref filename ,
	bool MipMap
)
{
	ILuint ImageName = 0;
	ilGenImages(1, &ImageName);
	ilBindImage(ImageName);
	ilLoadImage((const ILstring)filename.c_str());
	GLuint TexID = ilutGLBindTexImage();
	ilDeleteImages(1, &ImageName);
	return TexID;
}

