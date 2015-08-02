#ifndef _PIXELX_RUNTIMEOBJECT_H
#define _PIXELX_RUNTIMEOBJECT_H

enum PxRuntimeObjectType
{
	rtoPlane,
	rtoCube,
	rtoFountain,
	rtoSteps,
	rtoFlag,
	rtoModel,
	rtoHoarding
};
class PxRuntimeObject
{
public:
	string Name;
	PxRuntimeObjectType Type;
	string Params;
	float x,y,z;
	float dx,dy,dz;
};
#endif