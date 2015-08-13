#ifndef _PIXELX_MODELMANAGER_H
#define _PIXELX_MODELMANAGER_H

#include "PxModel.h"
#include "..\..\PxInput\include\PxDataFilesManager.h"
#include <unordered_map>

using std::unordered_map;

enum PxModelType
{
	eModelOBJ,
	eModelMD2,
	eModelMS3D,
	eModel3DS
};

struct _ModelData
{
	PxModelCore * core;
	string name;
	string type;
	string path;
	string texname;
};
class PxModelManager
{
	static unordered_map< string, _ModelData > cores;
	static void LoadModel( _ModelData & m );
public:
	static void Init();
	static PxModel * CreateModel(cstrref name);
	static PxModelCore * GetModel( cstrref name );
};

#endif

