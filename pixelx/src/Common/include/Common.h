#pragma once

#include "Platform.h"

#include <string>
using std::string;

typedef const string & cstrref;
typedef string & strref;

#include <memory>

template <typename T>
using UP = std::unique_ptr<T>;

#include <GL/gl.h>
#include <GL/glu.h>

enum PxKeyBindingEnum
{
	eKeyMoveUp,
	eKeyMoveDown,
	eKeyStrafeLeft,
	eKeyStrafeRight,
	eKeyLookUp,
	eKeyLookDown,
	eKeyTurnLeft,
	eKeyTurnRight,
	eKeyShoot,
	eKeyJump,
	eKeyCrouch,
	eKeyNextWeapon,
	eKeyPrevWeapon,
	eKeyReload,
	eKeyConsole,
	eKeyRun
};

enum PxDirectionEnum
{
	eDirectionNorth,
	eDirectionSouth,
	eDirectionEast,
	eDirectionWest
};

enum PxOrientation
{
	eXAxis,
	eYAxis,
	eZAxiz
};

class String
{
public:
	static bool equals(cstrref s1, cstrref s2)
	{
		return s1 == s2;
	}
	static bool equalsIgnoreCase(cstrref s1, cstrref s2)
	{
		return equalsIgnoreCase(s1.c_str(), s2.c_str());
	}
	static bool equals(const char* s1, const char* s2)
	{
		return ::strcmp(s1, s2) == 0;
	}
	static bool equalsIgnoreCase(const char* s1, const char* s2)
	{
#ifdef PLATFORM_LINUX
	return ::strcasecmp(s1, s2) == 0;
#else
	return ::_stricmp(s1, s2) == 0;
#endif
	}
};

#include "PxLog.h"
