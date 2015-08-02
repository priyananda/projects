#ifndef _PIXELX_WAVEFRONT_H
#define _PIXELX_WAVEFRONT_H
#include "PxModel.h"
#include "glm.h"

class PxWaveFrontModelCore : public PxModelCore
{
	GLMmodel * m_model;
	GLuint displayList;
public:
	void Render();
	void Register(PxPolygonCollection * pcoll){}
	void Animate(int sf, int ef,float interp )
	{
		Render();
	}
	PxWaveFrontModelCore(cstrref filename);
	~PxWaveFrontModelCore();
	void SetTexture( cstrref name );
};

#endif

