#include "PxTesselatedMapManager.h"

#include <fstream>
using std::ofstream;
using std::ifstream;
using std::endl;

static char buff[512];
void PxTesselatedMapManager::Persist(PxTesselatedMap& tmap, cstrref filename)
{
	PxTriangleSet* pTS = tmap.GetTriangleSet();
	ofstream out(filename.c_str());
	out << pTS->NumMeshes() << endl;
	for (const auto& item: *pTS)
	{
		PxMesh* pmesh = item.second;
		sprintf_s(buff , _countof(buff), "mesh %d %s %d",pmesh->NumTriangles(),pmesh->TextureName.c_str(),pmesh->TexMode );
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
	out << tmap.Objects.size() << endl;
	for (const auto& item: tmap.Objects)
	{
		sprintf_s(buff, _countof(buff), "%s %d %s" , item.Name.c_str() , item.Type , item.Params.c_str());
		out << buff << endl;
		sprintf_s(buff, _countof(buff), "%f %f %f" , item.x , item.y , item.z);
		out << buff << endl;
		sprintf_s(buff, _countof(buff), "%f %f %f" , item.dx , item.dy , item.dz);
		out << buff << endl;
	}
}

UP<PxTesselatedMap> PxTesselatedMapManager::Restore( cstrref filename )
{
	int  numMeshes = 0, numTriangles = 0 , numObjects = 0;
	char texname[200];
	int  texmode = 0;
	char name[100];
	char params[100];
	
	UP<PxTesselatedMap> pmap{ new PxTesselatedMap() };
	UP<PxTriangleSet> pts{ new PxTriangleSet() };
	
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
	pmap->SetTriangleSet(std::move(pts));

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

