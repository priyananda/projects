#pragma once

// Windows specific code
#ifndef PLATFORM_LINUX

#ifdef PROJECT_PXCORE
	#define PXCORE_DLLDECL __declspec( dllexport )
#else
	#define PXCORE_DLLDECL __declspec( dllimport )
#endif

	#define BUFFER_AND_SIZE(x) x, sizeof(x)

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#endif

// Linux specific code
#ifdef PLATFORM_LINUX

#include <cstring>
#include <strings.h>

#define PXCORE_DLLDECL
typedef void* HINSTANCE;
typedef	char* LPSTR;
extern LPSTR GetCommandLine();
#define sscanf_s sscanf
#define BUFFER_AND_SIZE(x) x
#define vsprintf_s vsprintf
#define strncpy_s strncpy

struct POINT
{
	int x = 0;
	int y = 0;
};

void GetCursorPos(POINT*)
{
}

void SetCursorPos(int, int)
{
}

int GetKeyState(int){ return 0; }

#endif
