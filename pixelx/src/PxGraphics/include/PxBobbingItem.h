#ifndef _PIXELX_BOBBINGITEM_H
#define _PIXELX_BOBBINGITEM_H

#include "PxModel.h"
class PxBobbingItem : public PxModel
{
	float yfactor;
	bool goingup;
	float rotangle;
public:
	PxBobbingItem( PxModelCore * _m ):PxModel(_m),yfactor(0),goingup(true),rotangle(0){}
	virtual void Render();
	virtual bool IsCollidable(){return false;}
};
#endif

