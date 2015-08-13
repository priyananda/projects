#ifndef _PIXELX_CONF_H
#define _PIXELX_CONF_H
#include "Common.h"

#include <unordered_map>
using std::unordered_map;

class PxConfiguration
{
	static unordered_map<string,string> options;
	static unordered_map<int,int> keyBindigs;
	static bool keyStates[16];

public:
	static void		Init();
	static string	GetString( cstrref name );
	static long		GetLong( cstrref name );
	static float	GetFloat( cstrref name );
	static bool		Exists( cstrref name );
	static void		SetString( cstrref name, cstrref value );

	static int		GetKey( PxKeyBindingEnum eKb , bool consume = true);
	static void		SetKey( int keyCode );
	static void		RegisterKey( int keyCode, PxKeyBindingEnum keb );
	static int		MapKey( PxKeyBindingEnum ekb );

	static void		ReadCommands(cstrref name);
};

#define VARB(v) (PxConfiguration::GetLong(v) != 0)
#define VARF(v) PxConfiguration::GetFloat(v)
#define VARS(v) PxConfiguration::GetString(v)
#define VARL(v) PxConfiguration::GetLong(v)

#define ASSIGN_VARB(v) v = VARB(#v)
#define ASSIGN_VARF(v) v = VARF(#v)
#define ASSIGN_VARS(v) v = VARS(#v)
#define ASSIGN_VARL(v) v = VARL(#v)

#define DEFINE_VARB(v) bool v = VARB(#v)
#define DEFINE_VARF(v) float v = VARF(#v)
#define DEFINE_VARS(v) string v = VARS(#v)
#define DEFINE_VARL(v) long v = VARL(#v)

#define DECLARE_VARB(v) static bool v
#define DECLARE_VARF(v) static float v
#define DECLARE_VARS(v) static string v
#define DECLARE_VARL(v) static long v
#endif

