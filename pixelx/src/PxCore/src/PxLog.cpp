#include "PxLog.h"

#include <fstream>
#include <stdio.h>
#include <stdarg.h>
using namespace std;

static bool g_inited = false;
static ofstream logfile;

static void Init()
{
	logfile.open( "PixelX.log" , ios::app );
}

void PxLog::LogMessage( const char * format, ... )
{
	static char buffer[12000];
	if( ! g_inited )
	{
		Init();
		g_inited = true;
	}
	va_list argptr;
    va_start( argptr, format );
    vsprintf_s( buffer, format, argptr );
    va_end( argptr );

	logfile << buffer << endl;
	logfile.flush();
}

