#include "PxShaderParser.h"

enum PxParserStateEnum
{
	eParserOutside,
	eParserInsideShader,
	eParserInsideStage
};

#define OBRACE	"{"
#define CBRACE	"}"
#define NL		"<NL>"

static PxParserStateEnum _state = eParserOutside;
static string m_currentShaderName = "";

inline bool _isnl( int ch )
{
	return ch == '\n' || ch == '\r';
}
inline bool _isspc( int ch )
{
	return ch == -1 || isspace( ch );
}
bool PxShaderParser::ignoreWhiteSpace(bool ignorenl)
{
	char ch = 0;
	while( ! feof( m_file ) )
    {
		ch = fgetc( m_file );
		if( _isnl( ch ) && ! ignorenl )
			return true;
		if(!_isspc(ch))
		{
			ungetc( ch , m_file );
			break;
		}
    }
	return false;
}
void PxShaderParser::Parse(cstrref filename)
{
	m_file = nullptr;
	fopen_s( &m_file, filename.c_str() , "r" );
	if( ! m_file )
		return;
	_ReadShaders();
	fclose( m_file );
}

void PxShaderParser::_ReadShaders()
{
	while( ! feof( m_file ) )
	{
		string token = getNextToken( true );
		if( token == OBRACE )
		{
			switch(_state)
			{
				case eParserInsideShader:
				{
					_state = eParserInsideStage;
					PxShaderData & shader = m_shaders[ m_currentShaderName ];
					PxCommandList clist;
					shader.Stages.push_back( clist );
					break;
				}
				case eParserOutside:
					_state = eParserInsideShader;
					break;
			}
			continue;
		}
		if( token == CBRACE )
		{
			switch(_state)
			{
				case eParserInsideShader:
					_state = eParserOutside;
					break;
				case eParserInsideStage:
					_state = eParserInsideShader;
					break;
			}
			continue;
		}
		switch(_state)
		{
			case eParserOutside:
			{
				m_currentShaderName = token;
				this->m_shaders[ token ] = PxShaderData( token );
				break;
			}
			case eParserInsideShader:
			{
				PxCommandList & clist = this->m_shaders[ m_currentShaderName ].Commands;
				PxCommand * command = new PxCommand;
				command->Command = token;
				list<string> args;
				while( ! feof( m_file ) )
				{
					token = getNextToken( false );
					if( token == "" || token == NL )
						break;
					args.push_back( token );
				}
				command->SetArguments( args );
				clist.Commands.push_back( command );
				break;
			}
			case eParserInsideStage:
			{
				PxCommandList & clist = this->m_shaders[ m_currentShaderName ].Stages.back();
				PxCommand * command = new PxCommand;
				command->Command = token;
				list<string> args;
				while( ! feof( m_file ) )
				{
					token = getNextToken( false );
					if( token == "" || token == NL )
						break;
					args.push_back( token );
				}
				command->SetArguments( args );
				clist.Commands.push_back( command );
				break;
			}
		}
	}
}

string PxShaderParser::getNextToken( bool ignorenl )
{
	static char buff[300];
	char ch = 0;
	int count = 0;
	bool last_char_slash = false;
	
	if( ignoreWhiteSpace(ignorenl) )
		return NL;
	
	while( ! feof( m_file ) )
	{
		if( _isspc( ch = fgetc( m_file ) ) )
		{
			ungetc( ch , m_file );
			break;
		}
		if( ch == '/' )
		{
			if( last_char_slash )
			{
				while( ! feof( m_file ) && ! _isnl( ch = fgetc( m_file ) ) );
				if( ! feof( m_file ) )
					ungetc( ch , m_file );
				if( --count )
					break;
				last_char_slash = false;
				if( ignoreWhiteSpace(ignorenl) )
					return NL;
			}
			else
			{
				last_char_slash = true;
				buff[count++] = ch;
			}
		}
		else
		{
			last_char_slash = false;
			buff[count++] = ch;
		}
	}
	buff[count] = 0;
	return string(buff);
}

