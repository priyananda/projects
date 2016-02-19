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
bool PxShaderParser::_IgnoreWhiteSpace(bool ignorenl)
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
	m_file = nullptr;
}

void PxShaderParser::_ReadShaders()
{
	while( ! feof( m_file ) )
	{
		string token = _GetNextToken( true );
		if( token == OBRACE )
		{
			switch(_state)
			{
				case eParserInsideShader:
				{
					_state = eParserInsideStage;
					PxShaderData & shader = *(m_shaders[ m_currentShaderName ]);
					std::unique_ptr<PxCommandList> commandList(new PxCommandList);
					shader.Stages.push_back( std::move(commandList) );
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
				std::unique_ptr<PxShaderData> pShaderData(new PxShaderData(token));
				this->m_shaders[token] = std::move(pShaderData);
				break;
			}
			case eParserInsideShader:
			{
				std::unique_ptr<PxCommand> command(new PxCommand);
				command->Command = token;
				list<string> args;
				while( ! feof( m_file ) )
				{
					token = _GetNextToken( false );
					if( token == "" || token == NL )
						break;
					args.push_back( token );
				}
				command->SetArguments( args );
				this->m_shaders[m_currentShaderName]->AddCommand(std::move(command));
				break;
			}
			case eParserInsideStage:
			{
				std::unique_ptr<PxCommand> command(new PxCommand);
				command->Command = token;
				list<string> args;
				while( ! feof( m_file ) )
				{
					token = _GetNextToken( false );
					if( token == "" || token == NL )
						break;
					args.push_back( token );
				}
				command->SetArguments( args );
				this->m_shaders[m_currentShaderName]->AddCommandToStage(std::move(command));
				break;
			}
		}
	}
}

string PxShaderParser::_GetNextToken( bool ignorenl )
{
	static char buff[300];
	char ch = 0;
	int count = 0;
	bool last_char_slash = false;
	
	if( _IgnoreWhiteSpace(ignorenl) )
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
				if( _IgnoreWhiteSpace(ignorenl) )
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

