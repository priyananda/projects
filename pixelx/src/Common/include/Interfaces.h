#ifndef _PIXELX_INTERFACES_H
#define _PIXELX_INTERFACES_H

#include "Common.h"

class PxWindow;
#ifdef PROJECT_PXCORE
	#define PXCORE_DLLDECL __declspec( dllexport )
#else
	#define PXCORE_DLLDECL __declspec( dllimport )
#endif

class PxGraphicsRoot
{
public:
	void Init();
	void Close();
	static void Switch();
	static void Restore();
	static void MessageLoop();
	static PxWindow * Window;
};

class PxPhysicsRoot
{
public:
	void Init();
};

class PxInputRoot
{
public:
	void Init();
};

class PxSoundRoot
{
public:
	void Init();
};

class PXCORE_DLLDECL PxEngineRoot
{
	PxGraphicsRoot	graphicsRoot;
	PxPhysicsRoot	physicsRoot;
	PxSoundRoot		soundRoot;
	PxInputRoot		inputRoot;
public:
	void Init(HINSTANCE h);
	void Close();
	void Process();
};

#endif