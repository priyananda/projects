#pragma once

#include "Common.h"

class PxAudioManager
{
public:
	static void Init();
	static void Play( cstrref name );
	static void Loop( cstrref name );
};
