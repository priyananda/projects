#include "PxAudioManager.h"
#include "..\..\PxInput\include\PxDataFilesManager.h"
#include "..\..\PxInput\include\PxConfiguration.h"

map<string, _AudioData > PxAudioManager::m_files;
static bool g_debug_audio;

#define LOOP_STREAM_CHANNEL 17

void PxAudioManager::Init()
{
	g_debug_audio = PxConfiguration::GetLong("g_debug_audio");
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
	FOR_EACH_CLIST(clist,iter)
	{
		_AudioData md;
		md.path = "data\\" + (*iter)->Arguments[1];
		md.loop = ( stricmp( (*iter)->Arguments[2].c_str() , "true" ) == 0);
		m_files[ (*iter)->Arguments[0] ] = md;
	}
}

void PxAudioManager::Play( cstrref name )
{
	if( m_files.find(name) == m_files.end() )
		return;
	_AudioData ad = m_files[ name ];
	if( ad.id.sampleid == NULL )
		Load(ad);
	Play( ad );
	m_files[ name ] = ad;
}

void PxAudioManager::Load( _AudioData & data )
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

void PxAudioManager::Play( _AudioData & ad )
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
	FSOUND_StopSound( LOOP_STREAM_CHANNEL );
	if( m_files.find(name) == m_files.end() )
		return;
	_AudioData ad = m_files[ name ];
	if( ad.id.sampleid == NULL )
	{
		Load(ad);
		m_files[ name ] = ad;
	}
	Loop( ad );
}

void PxAudioManager::Loop( _AudioData & ad  )
{
	if( ad.loop )
		FSOUND_SetLoopMode(
			LOOP_STREAM_CHANNEL,
			FSOUND_LOOP_NORMAL
		);
	Play( ad );
}

