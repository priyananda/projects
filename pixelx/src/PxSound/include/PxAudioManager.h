#pragma once

#include "Common.h"

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

class PxAudioManager
{
	static map<string, _AudioData > m_files;
	static void Play( _AudioData & ad );
	static void Loop( _AudioData & ad );
	static void Load( _AudioData & ad );
public:
	static void Init();
	static void Play( cstrref name );
	static void Loop( cstrref name );
};
