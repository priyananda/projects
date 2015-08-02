#include "PxQuake3EntityParser.h"
#include "..\..\PxInput\include\PxConfiguration.h"

void PxQuake3Entity::AddParam( cstrref name , cstrref value )
{
	DEFINE_VARF(g_debug_bspscale);
	if( name == "origin" )
	{
		sscanf(
			value.c_str(),
			"%f %f %f",
			&Origin.x,
			&Origin.z,
			&Origin.y
		);
		Origin = Origin / g_debug_bspscale;
		Origin.z = - Origin.z;
		return;
	}
	if( name == "classname" )
	{
		ClassName = value;
		return;
	}
	m_Params [ name ] = value;
}

string PxQuake3Entity::operator []( cstrref name )
{
	return m_Params[ name ];
}

void PxQuake3EntityParser::Parse( cstrref filename , PxQuake3EntityCollection & coll )
{
	FILE * fp = fopen( filename.c_str() , "r" );
	if( fp )
	{
		Parse( fp, coll);
		fclose( fp );
	}
	PxLog::LogMessage( "Number of entities found: %d" , coll.size() );
}

