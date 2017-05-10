#include "PxAudioManager.h"
#include "../../PxInput/include/PxDataFilesManager.h"
#include "../../PxInput/include/PxConfiguration.h"

#include <map>
using std::map;

#include "fmod/fmod.h"

struct _AudioData
{
	string path;
	union{
		FSOUND_STREAM * streamid;
		FSOUND_SAMPLE * sampleid;
	}id;
	bool loop;
	_AudioData():loop(false){id.streamid = 0;}
};

class PxAudioManagerCore
{
public:
	static map<string, _AudioData > m_files;
	static void Play( const _AudioData & ad );
	static void Loop( const _AudioData & ad );
	static void Load( _AudioData & ad );
	static void Init();
	static void Play( cstrref name );
	static void Loop( cstrref name );
};

map<string, _AudioData > PxAudioManagerCore::m_files;
static bool g_debug_audio;

#define LOOP_STREAM_CHANNEL 17

void PxAudioManager::Init()
{
	PxAudioManagerCore::Init();
}

void PxAudioManagerCore::Init()
{
	g_debug_audio = (PxConfiguration::GetLong("g_debug_audio") != 0);
	if(! g_debug_audio )
		return;
	
	FSOUND_SetOutput(FSOUND_OUTPUT_DSOUND);
	FSOUND_SetBufferSize(50);
	FSOUND_SetDriver(0);
	FSOUND_Init(44100, 32, 0);
	FSOUND_SetVolume( FSOUND_ALL , 255 );

	PxCommandList * clist = PxDataFilesManager::Get("AUDIO_LIST");
	if( ! clist )
		return;
	for(const auto& cmd : *clist)
	{
		_AudioData md;
		md.path = "data\\" + cmd->Arguments[1];
		md.loop = ( String::equalsIgnoreCase( cmd->Arguments[2].c_str() , "true" ) );
		m_files[ cmd->Arguments[0] ] = md;
	}
}

void PxAudioManager::Play( cstrref name )
{
	PxAudioManagerCore::Play(name);
}

void PxAudioManagerCore::Play( cstrref name )
{
	if( m_files.find(name) == m_files.end() )
		return;
	_AudioData& ad = m_files[ name ];
	if( ad.id.sampleid == nullptr )
		Load(ad);
	Play( ad );
	m_files[ name ] = ad;
}


void PxAudioManagerCore::Load( _AudioData & data )
{
	if( data.id.sampleid )
		return;
	if( data.loop )
	{
		data.id.sampleid = FSOUND_Sample_Load(
			FSOUND_FREE,
			data.path.c_str(),
			FSOUND_LOOP_NORMAL,
			0,
			0
		);
	}
	else
	{
		data.id.streamid = FSOUND_Stream_Open(data.path.c_str() , 0 ,0 , 0);
	}
}

void PxAudioManagerCore::Play( const _AudioData & ad )
{
	if( g_debug_audio )
	{
		if( ! ad.loop )
			FSOUND_Stream_Play(FSOUND_FREE, ad.id.streamid );
		else
			FSOUND_PlaySound( LOOP_STREAM_CHANNEL , ad.id.sampleid );
	}
}

void PxAudioManager::Loop( cstrref name )
{
	PxAudioManagerCore::Loop(name);
}

void PxAudioManagerCore::Loop( cstrref name )
{
	FSOUND_StopSound( LOOP_STREAM_CHANNEL );
	if( m_files.find(name) == m_files.end() )
		return;
	_AudioData ad = m_files[ name ];
	if( ad.id.sampleid == nullptr )
	{
		Load(ad);
		m_files[ name ] = ad;
	}
	Loop( ad );
}

void PxAudioManagerCore::Loop( const _AudioData & ad  )
{
	if( ad.loop )
		FSOUND_SetLoopMode(
			LOOP_STREAM_CHANNEL,
			FSOUND_LOOP_NORMAL
		);
	Play( ad );
}

