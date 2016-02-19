#ifndef _PIXELX_WORLD_H
#define _PIXELX_WORLD_H

#include "PxHuman.h"
#include "..\..\PxGraphics\include\PxWindow.h"
#include "..\..\PxGraphics\include\PxQuakeMapRenderer.h"
#include "..\..\PxGraphics\include\PxTesselatedMap.h"
#include "..\..\PxGraphics\include\PxSimplePolygonSet.h"

class PxWorld
{
	string mBspFileName;
	string mTriFileName;
	string mName;
	string mBGSound;
	bool   mEnableFog;
	bool   mEnableLight;
	string mBotName;

	PxQuakeMap * mQuakeMap;
	PxQuakeMapRenderer * mQuakeRenderer;
	PxTesselatedMap * mWorldMap;
	list<PxSolidObject *> mRuntimeObjects;
	bool mEnableCollision;
	PxSimplePolygonSet mPolygonSet;
	long mWorldFragCount;

	PxHuman mHuman;
public:
	PxWorld();
	PxWorld(cstrref filename){ Deserialize(filename); }
	~PxWorld();

	PxWorld(const PxWorld&) = delete;

	void Deserialize(cstrref filename);
	void Initialize();
	void Render(PxWindow *);
	void EnableCollision(bool val){mEnableCollision = val;}

	string		GetName(){return mName;}
	PxCamera &	GetCamera(){return mHuman.Camera;}
	int			GetRenderedTrianglesCount(){ return mQuakeRenderer->numTris; }
	string		GetBSPFileName(){ return mBspFileName; }
	PxHuman &	GetHuman(){ return mHuman; }
	long		GetWorldFragCount(){ return mWorldFragCount; }
private:
	void DrawBSP();
};
#endif

