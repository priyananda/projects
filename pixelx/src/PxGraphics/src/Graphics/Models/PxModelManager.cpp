#include "PxModelManager.h"
#include "PxQuake2Model.h"
#include "PxQuake3Model.h"
#include "PxWaveFrontModel.h"
#include "Px3DSModelCore.h"
#include "PxBobbingItem.h"

unordered_map< string, _ModelData> PxModelManager::cores;

void PxModelManager::Init()
{
	PxCommandList * clist = PxDataFilesManager::Get( "MODEL_LIST" );
	if(!clist) return;
	for( PxCommandList::Iterator iter = clist->Commands.begin(); iter != clist->Commands.end(); ++iter )
	{
		_ModelData md;
		PxCommand * pCmd = *iter;
		md.path = "data\\" + pCmd->Arguments[1];
		md.type = pCmd->Command;
		md.core = NULL;
		md.name = pCmd->Arguments[0];
		if( pCmd->ArgCount > 2 )
			md.texname = pCmd->Arguments[2];
		cores[ pCmd->Arguments[0] ] = md;
	}
}

PxModel * PxModelManager::CreateModel( cstrref name )
{
	PxModelCore * pModelCore = GetModel( name );
	return new PxModel( pModelCore );
}

PxModelCore * PxModelManager::GetModel( cstrref name )
{
	if( cores.find(name) == cores.end() )
		return NULL;
	_ModelData md = cores[ name ];
	if( md.core == NULL )
		LoadModel( md );
	cores[ name ] = md;
	return md.core;
}

void PxModelManager::LoadModel( _ModelData & md )
{
	if( md.type == "md2" )
		md.core = new PxQuake2ModelCore( md.path );
	if( md.type == "obj" )
		md.core = new PxWaveFrontModelCore( md.path );
	if( md.type == "3ds" )
		md.core = new Px3DSModelCore( md.path );
	//if( md.type == "m3d" )
		//md.core = new PxMilkshapeModelCore( md.path );
	if( md.type == "md3" )
		md.core = new PxQuake3ModelCore(md.path );
	if( md.core  && md.texname.length() )
		md.core->SetTexture( md.texname );
}

