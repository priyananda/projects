#include "PxObjectFactory.h"

#include "PxCube.h"
#include "PxFlag.h"
#include "PxFountain.h"
#include "PxSteps.h"
#include "PxHoarding.h"
#include "PxModelManager.h"

static char g_buff[512];

static PxCube * CreateCube( const PxRuntimeObject & ro)
{
	float x = 0;
	PxCube * p = new PxCube(ro.x,ro.y,ro.z,ro.dx,ro.dy,ro.dz);
	sscanf_s( ro.Params.c_str() , "%f,%f,%f,%f,%f,%f,%s" , &x,&x,&x,&x,&x,&x,g_buff, _countof(g_buff));
	p->SetTexture(g_buff);
	return p;
}

static PxFlag * CreateFlag( const PxRuntimeObject & ro)
{
	float a,b,c,d,e,f;
	sscanf_s( ro.Params.c_str() , "%f,%f,%f,%f,%f,%f,%s" , &a,&b,&c,&d,&e,&f,g_buff, _countof(g_buff));
	return new PxFlag(a,b,c,d,e,f,g_buff);
}

static PxFountain * CreateFountain(const PxRuntimeObject & ro)
{
	float x,y,z;
	sscanf_s( ro.Params.c_str() , "%f,%f,%f" , &x,&y,&z);
	return new PxFountain(x,y,z);
}

static PxSteps * CreateSteps(const PxRuntimeObject & ro)
{
	float a,b,c,d,e,f;
	PxDirectionEnum de;
	sscanf_s( ro.Params.c_str() , "%d,%f,%f,%f,%f,%f,%f" , &de,&a,&b,&c,&d,&e,&f);
	return new PxSteps(de,a,b,c,d,e,f);
}

static PxHoarding * CreateHoarding(const PxRuntimeObject & ro)
{
	float a,b,c,d,e,f;
	sscanf_s( ro.Params.c_str() , "%f,%f,%f,%f,%f,%f,%s" , &a,&b,&c,&d,&e,&f,g_buff, _countof(g_buff));
	return new PxHoarding(a,b,c,d,e,f,g_buff);
}
static PxModel * CreateModel(const PxRuntimeObject & ro )
{
	float x,y,z,s;
	sscanf_s( ro.Params.c_str() , "%f,%f,%f,%f,%s" , &x,&y,&z,&s,g_buff, _countof(g_buff));
	PxModel * pModel = PxModelManager::CreateModel( g_buff );
	pModel->SetLocation(x,y,z);
	pModel->SetScale(s);
	return pModel;
}
PxSolidObject * PxObjectFactory::GetObject(const PxRuntimeObject & ro)
{
	switch(ro.Type)
	{
		case rtoCube:
			return CreateCube(ro);
		case rtoFlag:
			return CreateFlag(ro);
		case rtoFountain:
			return CreateFountain(ro);
		case rtoSteps:
			return CreateSteps(ro);
		case rtoHoarding:
			return CreateHoarding(ro);
		case rtoModel:
			return CreateModel(ro);
	}
	return nullptr;
}

