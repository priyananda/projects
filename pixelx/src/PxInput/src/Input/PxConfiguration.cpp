#include "PxConfiguration.h"
#include "PxDataFilesManager.h"
#include <cstring>

unordered_map<string,string> PxConfiguration::options;
unordered_map<int,int> PxConfiguration::keyBindigs;
bool PxConfiguration::keyStates[16];

void PxConfiguration::Init()
{
	static char buff[100];
	ReadCommands("CONFIG");
	LPSTR pCmd = GetCommandLine();
	if( pCmd == nullptr || pCmd[0] == 0 )
		return;
	char * pArg = strstr( pCmd, "--config-file" );
	if( pArg != nullptr && *pArg != 0)
	{
		sscanf_s(pArg, "--config-file=%s", BUFFER_AND_SIZE(buff));
		ReadCommands(buff);
	}
}

int PxConfiguration::GetKey( PxKeyBindingEnum eKb, bool consume)
{
	int ret = keyStates[eKb];
	if( consume )
		keyStates[eKb] = false;
	return ret;
}

void PxConfiguration::SetKey( int KeyCode)
{
	if( keyBindigs.find( KeyCode ) == keyBindigs.end() )
		return;
	keyStates[ keyBindigs[KeyCode] ] = true;
}

void PxConfiguration::RegisterKey( int keyCode , PxKeyBindingEnum keb )
{
	keyBindigs[ keyCode ] = keb;
}

string PxConfiguration::GetString( cstrref name )
{
	if( options.find( name ) == options.end() )
		return "";
	return options[name];
}

long PxConfiguration::GetLong( cstrref name )
{
	return atol(GetString(name).c_str());
}

float PxConfiguration::GetFloat( cstrref name )
{
	return static_cast<float>(atof(GetString(name).c_str()));
}

bool PxConfiguration::Exists( cstrref name )
{
	return options.find(name) != options.end();
}

int PxConfiguration::MapKey( PxKeyBindingEnum ekb )
{
	for( unordered_map<int,int>::iterator iter = keyBindigs.begin(); iter != keyBindigs.end(); ++iter )
		if( iter->second == ekb )
			return iter->first;
	return 0;
}

void PxConfiguration::ReadCommands(cstrref name)
{
	PxCommandList * clist = PxDataFilesManager::Get( name );
	if(! clist )
		return;
	for( auto& spCmd : clist->Commands )
	{
		PxCommand * p = spCmd.get();
		if( p->Command == "set" )
			options[ p->Arguments[0] ] = p->Arguments[1];
		if( p->Command == "bind" )
			RegisterKey( atoi( p->Arguments[1].c_str() ) , (PxKeyBindingEnum)atoi( p->Arguments[0].c_str() ) );
	}
}

void PxConfiguration::SetString( cstrref name , cstrref value )
{
	options[ name ] = value;
}

