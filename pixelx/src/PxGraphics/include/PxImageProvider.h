#ifndef _PIXELX_IMAGEPROV_H
#define _PIXELX_IMAGEPROV_H

#include "Common.h"
class PxImageProvider
{
public:
	static GLuint CreateTexture(cstrref path, bool MipMap = false);
	static void Init();
	static void Reset();
};

#endif

