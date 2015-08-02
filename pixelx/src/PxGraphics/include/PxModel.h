#ifndef _PIXELX_MODEL_H
#define _PIXELX_MODEL_H

#include "PxSolidObject.h"

class PxModelCore
{
public:
	virtual void Register(PxPolygonCollection *) = 0;
	virtual void Render() = 0;
	virtual void Animate( int StartFrame , int EndFrame , float interp = 0.8f) = 0;

	virtual void SetTexture( cstrref name ) = 0;
};

class PxModel : public PxSolidObject
{
protected:
	PxBoundingBox bBox;
	PxModelCore * m_modelCore;
	GLfloat m_scale;
	float m_angle;
public:
	PxModel( PxModelCore * _m ): m_modelCore(_m),m_scale(1.0f),m_angle(0){}
	void SetLocation(GLfloat x,GLfloat y,GLfloat z)
	{
		bBox.x = x;bBox.y = y;bBox.z = z;
		bBox.length = 5; bBox.width = 4; bBox.height = 5;
		bBox.Parent = this;
	}
	void SetScale( GLfloat s ){ m_scale = s;}
	void Turn( float angle ){ m_angle = angle; }
	void Strafe( bool right, float val);
	PxBoundingBox & GetBoundingBox(){ return bBox; }
	void Register(PxPolygonCollection *);
	void Render();
	void Animate( int startframe, int endframe , float interpolation = 0.08f);
};

#endif

