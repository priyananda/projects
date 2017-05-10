#ifndef _PIXELX_CONSOLE_H
#define _PIXELX_CONSOLE_H

#include "Common.h"
#include "PxInputEventHandler.h"
#include "PxConsoleCommandHandler.h"

#define CONSOLE_MSG             50
#define CONSOLE_MSGLGTH         50

#define CONSOLE_CMDLINE         50
#define CONSOLE_CMDLINELGTH     50

#define CONSOLE_MOVELEFT        (256+0)
#define CONSOLE_MOVERIGHT       (256+1)
#define CONSOLE_MOVEUP          (256+2)
#define CONSOLE_MOVEDOWN        (256+3)
#define CONSOLE_DELETE          (256+4)
#define CONSOLE_MOVEHOME        (256+5)
#define CONSOLE_MOVEEND         (256+6)
#define CONSOLE_PGUP            (256+7)
#define CONSOLE_PGDOWN          (256+8)
#define CONSOLE_TOTAL_KEYS      (256+9)

#ifdef PLATFORM_LINUX

const int VK_LEFT = 0;
const int VK_RIGHT = 0;
const int VK_UP = 0;
const int VK_DOWN = 0;
const int VK_DELETE = 0;
const int VK_HOME = 0;
const int VK_END = 0;
const int VK_PRIOR = 0;
const int VK_NEXT = 0;

void MessageBeep(int)
{
}

#endif

// m_console definition

struct _console
{
    char line[CONSOLE_MSG][CONSOLE_MSGLGTH];
    char command[CONSOLE_CMDLINE][CONSOLE_CMDLINELGTH];

    char buffer[CONSOLE_MSGLGTH];
    bool keys[CONSOLE_TOTAL_KEYS];

    unsigned int texture1;
    unsigned int texture2;
    int     bufferpos;
    int     buffermax;
    int     first_visible_msg;
    int     last_visible_msg;
    int     curr_msg;
    int     last_msg;
    int     first_cmd;
    int     curr_cmd;
    int     last_cmd;
    bool    is_open;
    bool    is_toggling;
    bool    is_ready;
    float   max_height;
    float   height;
    float   speed;

};

class PxConsole
{
	_console m_console;
	int m_screenwidth, m_screenheight;
	PxConsoleCommandHandler * m_pHandler;
public:
	PxConsole( int screenwidth, int screenheight,int consoleheight, PxConsoleCommandHandler * pHandler );
	void Update(unsigned long);
	void Toggle();
	void HandleKey( PxKeyStateEnum keyState, long ScanCode );
	void Clear();
	void PutMessage(const char * , ... );
	void Flush();
	void ClearLine();
	void ClearBuffer();
	void AddChar(unsigned char c);
	void SaveCommand(const char *, ...);
	void TranslateKey( unsigned int code, bool state );
	void KeyCheck();
	bool Execute(const char *);
};
#endif

