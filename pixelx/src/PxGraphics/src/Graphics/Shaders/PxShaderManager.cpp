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
	for(auto& item : m_parser)
	{
		PxLog::LogMessage( "[SHADER] %s " , item.first.c_str() );
		PxShaderData & shader = *(item.second);
		out << shader.Name << endl;
		if (shader.Commands)
		{
			for (auto& spCmd : *(shader.Commands))
			{
				out << "\t" << spCmd->Command << "(";
				for (size_t i = 0; i < spCmd->Arguments.size(); ++i)
					out << (i ? "," : "") << spCmd->Arguments[i];
				out << ")" << endl;
			}
		}
		for( unsigned j = 0 ; j < shader.Stages.size() ; ++j )
		{
			out << "\tStage" << j << endl;
			PxCommandList & clist = *(shader.Stages[j]);
			for (auto& spCmd : clist)
			{
				out << "\t\t" << spCmd->Command << "(";
				for( size_t i = 0 ; i < spCmd->Arguments.size(); ++i )
					out << ( i ? ","  : "" ) << spCmd->Arguments[i];
				out << ")" << endl;
			}
		}
	}
	out.close();
}

