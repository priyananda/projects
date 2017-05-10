#pragma once

#include "Common.h"

class PxWindow;

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
