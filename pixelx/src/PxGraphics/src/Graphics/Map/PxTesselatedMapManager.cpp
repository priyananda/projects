#include "PxTesselatedMapManager.h"

#include <fstream>
using std::ofstream;
using std::ifstream;
using std::endl;

static char buff[512];
void PxTesselatedMapManager::Persist( PxTesselatedMap * pMap, cstrref filename )
{
	PxTriangleSet * pTS = pMap->GetTriangleSet();
	ofstream out( filename.c_str());
	out << pTS->NumMeshes() << endl;
	for( PxMeshes::Iterator iter = pTS->begin(); iter != pTS->end(); ++iter)
	{
		PxMesh * pmesh = iter->second;
		sprintf_s( buff , _countof(buff), "mesh %d %s %d",pmesh->NumTriangles(),pmesh->TextureName.c_str(),pmesh->TexMode );
		out << buff << endl;
		int numTriangles = pmesh->NumTriangles();
		for( int i = 0 ; i < numTriangles ; ++i )
		{
			PxTriangle & pt = (*pmesh)[i];
			for( int j = 0 ; j < 3 ; ++j )
			{
				PxVertex * v = &pt[j];
				sprintf_s(buff, _countof(buff), "%f %f %f %d %d" , v->x,v->y,v->z, v->u,v->v );
				out << buff << endl;
			}
		}
	}

	// object data
	out << pMap->Objects.size() << endl;
	for( vector<PxRuntimeObject>::iterator iter = pMap->Objects.begin(); iter != pMap->Objects.end(); ++iter )
	{
		sprintf_s(buff, _countof(buff), "%s %d %s" , (*iter).Name.c_str() , iter->Type , iter->Params.c_str() );
		out << buff << endl;
		sprintf_s(buff, _countof(buff), "%f %f %f" , iter->x , iter->y , iter->z );
		out << buff << endl;
		sprintf_s(buff, _countof(buff), "%f %f %f" , iter->dx , iter->dy , iter->dz );
		out << buff << endl;
	}
}

PxTesselatedMap * PxTesselatedMapManager::Restore( cstrref filename )
{
	int  numMeshes = 0, numTriangles = 0 , numObjects = 0;
	char texname[200];
	int  texmode = 0;
	char name[100];
	char params[100];
	
	PxTesselatedMap * pmap = new PxTesselatedMap();
	PxTriangleSet * pts = new PxTriangleSet();
	pmap->SetTriangleSet( pts );
	
	ifstream in(filename.c_str());
	if(!in)
		return nullptr;
	
	in.getline(buff,511);
	sscanf_s(buff,"%d", & numMeshes );

	for( int i = 0 ; i < numMeshes; ++i )
	{
		in.getline(buff,511);
		sscanf_s(buff,"mesh %d %s %d", & numTriangles , texname, _countof(texname), &texmode);
		for( int j = 0 ; j < numTriangles ; ++j )
		{
			PxTriangle tri;
			for( int k = 0 ; k < 3 ; ++k )
			{
				in.getline( buff, 511 );
				sscanf_s( buff , "%f %f %f %d %d" , &tri[k].x,&tri[k].y,&tri[k].z,&tri[k].u,&tri[k].v);
			}
			pts->AddTriangle( texname , (TextureMode)texmode , tri );
		}
	}
	pts->Finalize();
	// objects section
	in.getline(buff,511);
	sscanf_s(buff,"%d", & numObjects );
	
	while( numObjects -- > 0 )
	{
		PxRuntimeObject obj;
		in.getline( buff, 511 );
		sscanf_s( buff ,"%s %d %s" , name, _countof(name) , &obj.Type , params, _countof(params) );
		obj.Name = name;
		obj.Params = params;
		in.getline( buff, 511 );
		sscanf_s( buff ,"%f %f %f" , &obj.x , &obj.y , &obj.z );
		in.getline( buff, 511 );
		sscanf_s( buff , "%f %f %f" , &obj.dx , &obj.dy , &obj.dz );
		pmap->Objects.push_back( obj );
	}

	in.close();
	return pmap;
}

