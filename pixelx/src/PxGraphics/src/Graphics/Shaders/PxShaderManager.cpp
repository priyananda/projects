#include "PxShaderManager.h"

PxShaderParser PxShaderManager::m_parser;
#include <fstream>
using std::ofstream;
using std::endl;

void PxShaderManager::Init()
{
	m_parser.Parse( "data/qbase/scripts/sfx.shader" );
	ofstream out;
	out.open( "shaders.log" );
	FOR_EACH_SHADER(iter,m_parser)
	{
		PxLog::LogMessage( "[SHADER] %s " , (*iter).first.c_str() );
		PxShaderData & shader = (*iter).second;
		out << shader.Name << endl;
		FOR_EACH_CLIST((&shader.Commands),iter)
		{
			out << "\t" << (*iter)->Command << "(";
			for( int i = 0 ; i < (*iter)->ArgCount; ++i )
				out << ( i ? ","  : "" ) << (*iter)->Arguments[i];
			out << ")" << endl;
		}
		for( int j = 0 ; j < shader.Stages.size() ; ++j )
		{
			out << "\tStage" << j << endl;
			PxCommandList & clist = shader.Stages[j];
			FOR_EACH_CLIST((&clist),iter)
			{
				out << "\t\t" << (*iter)->Command << "(";
				for( int i = 0 ; i < (*iter)->ArgCount; ++i )
					out << ( i ? ","  : "" ) << (*iter)->Arguments[i];
				out << ")" << endl;
			}
		}
	}
	out.close();
}

