#ifndef _PIXELX_CONSOLECOMMANDHDLR
#define _PIXELX_CONSOLECOMMANDHDLR

struct PxConsoleCommandHandler
{
	virtual int HandleCommand( const char * ) = 0;
};
#endif