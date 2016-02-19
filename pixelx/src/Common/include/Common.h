#ifndef _PIXELX_COMMON_H
#define _PIXELX_COMMON_H

#include <string>
using std::string;

typedef const string & cstrref;
typedef string & strref;

#include <memory>

template <typename T>
using UP = std::unique_ptr<T>;

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

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

#include "PxLog.h"

#endif

