#include "PxConsole.h"
#include "PxTextWriter.h"
#include "PxTextureManager.h"

#include <string.h>
#include <stdarg.h>
#include <stdio.h>

PxConsole::PxConsole(int screenwidth, int screenheight,int consoleheight, PxConsoleCommandHandler * pHandler )
{
	memset( &m_console , 0 , sizeof(_console) );
	m_console.max_height = consoleheight;
	m_console.speed = 80;
	m_screenheight = screenheight;
	m_screenwidth = screenwidth;
	m_pHandler = pHandler;
}

void PxConsole::Toggle()
{
	if( !m_console.is_toggling )
	{
        m_console.is_toggling = true;
        m_console.is_open     = !m_console.is_open;
    }
}

void PxConsole::Flush()
{
	PutMessage( m_console.buffer );
	m_console.bufferpos = 0;
	m_console.buffermax = 0;
	m_console.curr_msg = m_console.last_msg;
	memset( m_console.buffer, '\0', CONSOLE_MSGLGTH );
}

void PxConsole::ClearLine()
{
	m_console.bufferpos = 0;
	m_console.buffermax = 0;
	m_console.curr_msg = m_console.last_msg;
	memset( m_console.buffer, '\0', CONSOLE_MSGLGTH );
}

void PxConsole::ClearBuffer()
{
	m_console.bufferpos = 0;
	m_console.buffermax = 0;
	memset( m_console.buffer, '\0', CONSOLE_MSGLGTH );
}


void PxConsole::AddChar( unsigned char c )
{
	if( m_console.bufferpos < CONSOLE_MSGLGTH-1 )
	{
		if( m_console.buffermax == m_console.bufferpos )
		{
			m_console.buffer[m_console.bufferpos] = c;
			m_console.bufferpos++;
			m_console.buffermax++;
		}
        else
		{
			int i;
			for( i=m_console.buffermax; i>m_console.bufferpos; i-- )
				m_console.buffer[i] = m_console.buffer[i-1];
			m_console.buffer[i] = c;
			m_console.buffermax++;
			m_console.bufferpos++;
		}
    }
    else
	{
        this->SaveCommand( m_console.buffer );
        this->Flush();
    }
}

void PxConsole::PutMessage( const char *str, ... )
{
	static char buffer[1024];
    int i;

	va_list argptr;
    va_start( argptr, str );
    vsprintf( buffer, str, argptr );
    va_end( argptr );

	if( m_console.last_msg < CONSOLE_MSG )
	{
        strncpy( m_console.line[m_console.last_msg], buffer, CONSOLE_MSGLGTH );
        m_console.last_msg++;
    }
    else
	{
		for( i=0; i<CONSOLE_MSG-1 && i<m_console.last_msg-1; i++ )
			strncpy( m_console.line[i], m_console.line[i+1], CONSOLE_MSGLGTH );
		strncpy( m_console.line[m_console.last_msg-1], buffer, CONSOLE_MSGLGTH );
    }
}

void PxConsole::SaveCommand( const char *cmd, ... )
{
	int i;
    static char buffer[1024];

	va_list argptr;
    va_start( argptr, cmd );
    vsprintf( buffer, cmd, argptr );
    va_end( argptr );

    if( m_console.last_cmd < CONSOLE_CMDLINE )
	{
        strncpy( m_console.command[m_console.last_cmd], buffer, CONSOLE_CMDLINELGTH );
        m_console.last_cmd++;
        m_console.curr_cmd = m_console.last_cmd;
    }
    else
	{
        for( i=0; i<CONSOLE_CMDLINE-1 && i<m_console.last_cmd-1; i++ )
            strncpy( m_console.command[i], m_console.command[i+1], CONSOLE_CMDLINELGTH );
        strncpy( m_console.command[m_console.last_cmd-1], buffer, CONSOLE_CMDLINELGTH );
    }
}

void PxConsole::HandleKey(PxKeyStateEnum state, long code )
{
	if( state == eKeyStateDown )
		if( code < CONSOLE_TOTAL_KEYS )
			m_console.keys[code] = true;
}

void PxConsole::TranslateKey( unsigned int code, bool state )
{
    if( code<CONSOLE_TOTAL_KEYS )
	{
        if( code == VK_LEFT ) m_console.keys[CONSOLE_MOVELEFT] = state;
        else if( code == VK_RIGHT ) m_console.keys[CONSOLE_MOVERIGHT] = state;
        else if( code == VK_UP ) m_console.keys[CONSOLE_MOVEUP] = state;
        else if( code == VK_DOWN ) m_console.keys[CONSOLE_MOVEDOWN] = state;
        else if( code == VK_DELETE ) m_console.keys[CONSOLE_DELETE] = state;
        else if( code == VK_HOME ) m_console.keys[CONSOLE_MOVEHOME] = state;
        else if( code == VK_END ) m_console.keys[CONSOLE_MOVEEND] = state;
        else if( code == VK_PRIOR ) m_console.keys[CONSOLE_PGUP] = state;
        else if( code == VK_NEXT ) m_console.keys[CONSOLE_PGDOWN] = state;
   }
}
void PxConsole::KeyCheck()
{
    int i, j;

	if( m_console.keys[(unsigned char)'~'] )
	{
        Toggle();
        m_console.keys[(unsigned char)'~'] = false;
        return;
    }
    else if( m_console.keys[(unsigned char)'`'] )
	{
        Toggle();
        m_console.keys[(unsigned char)'`'] = false;
        return;
    }
    else if( !m_console.is_open || m_console.is_toggling ) return;

    for( i=0; i<CONSOLE_TOTAL_KEYS; i++ )
	{
        if( m_console.keys[i] )
		{
            switch( i ){
            case '\r':
            case '\n':
                SaveCommand( m_console.buffer );
                if( !m_console.bufferpos )
				{
                    Flush();
                }
				else if( m_console.buffer[0] != ':' )
				{
					PutMessage( "Invalid Command:%s" , m_console.buffer);
                    ClearBuffer();
                }
                else if( !Execute(m_console.buffer+1) )
				{
					PutMessage( "Invalid Command:%s" , m_console.buffer+1 );
                    ClearBuffer();
                }
                else
                    ClearBuffer();
                break;
            case '\t':
                MessageBeep( 0 );
                break;
            case '\b':
                if( m_console.bufferpos )
				{
                    if( m_console.bufferpos == m_console.buffermax )
					{
                        m_console.bufferpos--;
                        m_console.buffermax--;
                        m_console.buffer[m_console.bufferpos] = '\0';
                    }
                    else
					{
                        for( j=m_console.bufferpos-1; j<m_console.buffermax-1; j++ )
                            m_console.buffer[j] = m_console.buffer[j+1];
                        m_console.buffer[m_console.buffermax-1] = '\0';
                        m_console.buffermax--;
                        m_console.bufferpos--;
                    }
                }
                break;
            case CONSOLE_DELETE:
                if( m_console.bufferpos<m_console.buffermax )
				{
                    for( j=m_console.bufferpos; j<m_console.buffermax-1; j++ )
                        m_console.buffer[j] = m_console.buffer[j+1];
                    m_console.buffer[m_console.buffermax-1] = '\0';
                    m_console.buffermax--;
                }
                break;
            case CONSOLE_MOVELEFT:
                if( m_console.bufferpos ) m_console.bufferpos--;
                break;
            case CONSOLE_MOVERIGHT:
                if( m_console.bufferpos<m_console.buffermax ) m_console.bufferpos++;
                break;
            case CONSOLE_MOVEUP:
                if( m_console.curr_cmd )
				{
                    m_console.curr_cmd--;
                    strncpy( m_console.buffer, m_console.command[m_console.curr_cmd], CONSOLE_CMDLINELGTH );
                    m_console.bufferpos = strlen( m_console.buffer );
                    m_console.buffermax = m_console.bufferpos;
                }
                break;
            case CONSOLE_MOVEDOWN:
                if( m_console.curr_cmd<m_console.last_cmd-1 )
				{
                    m_console.curr_cmd++;
                    strncpy( m_console.buffer, m_console.command[m_console.curr_cmd], CONSOLE_CMDLINELGTH );
                    m_console.bufferpos = strlen( m_console.buffer );
                    m_console.buffermax = m_console.bufferpos;
                }
                break;
            case CONSOLE_MOVEHOME:
                m_console.bufferpos = 0;
                break;
            case CONSOLE_MOVEEND:
                m_console.bufferpos = m_console.buffermax;
                break;
            case CONSOLE_PGUP:
                if( m_console.first_visible_msg<m_console.last_msg-15 ) m_console.first_visible_msg++;
                break;
            case CONSOLE_PGDOWN:
                if( m_console.first_visible_msg>0 ) m_console.first_visible_msg--;
                break;
            default:
                if( isprint(i) )
                    AddChar((unsigned char)i );
            }
            m_console.keys[i] = false;
        }
    }
}


void PxConsole::Update( unsigned long frame_time )
{
    static float xshift = 0;
    static float yshift = 0;
    int i, j;

	KeyCheck();


    if( m_console.is_open )
	{
        if( m_console.is_toggling )
		{
            if( m_console.height < m_console.max_height )
			{
                m_console.height += (float)(frame_time)*m_console.speed*0.01f;
                if( m_console.height > m_console.max_height ) m_console.height = m_console.max_height;
            }
            else
				m_console.is_toggling = false;
            m_console.last_visible_msg = (int)(m_console.height/16);
        }
    }
    else
	{
		if( m_console.is_toggling )
		{
			if( m_console.height > 0 )
			{
                m_console.height -= (float)(frame_time)*m_console.speed*0.01f;
                if( m_console.height < 0 ) m_console.height = 0;
            }
            else
				m_console.is_toggling = false;
            m_console.last_visible_msg = (int)(m_console.height/16);
        }
    }
    if( m_console.height != 0 )
	{
		glPushAttrib( GL_ALL_ATTRIB_BITS );
		glEnable(GL_BLEND);
        glBlendFunc( GL_ONE, GL_ZERO );
		glPolygonMode( GL_FRONT_AND_BACK , GL_FILL );
        PxTextureManager::Bind( "CONSOLE" , eTexModeNoStretch );
        glBegin(GL_QUADS);
        glTexCoord2d( xshift*10.0f , yshift ); glVertex2f( 0, m_screenheight );
		glTexCoord2d( 2.0f+xshift*10.0f, yshift ); glVertex2f( m_screenwidth, m_screenheight );
		glTexCoord2d( 2.0f+xshift*10.0f, 1.0f + yshift ); glVertex2f( m_screenwidth, m_screenheight-m_console.height );
		glTexCoord2d( xshift*10.0f , 1.0f + yshift ); glVertex2f( 0, m_screenheight-m_console.height );
        glEnd();

        glDisable( GL_BLEND );
        glBindTexture(GL_TEXTURE_2D, 0 );

        glColor3f( 1.0f, 1.0f, 0.0f );
        glBegin( GL_LINES );
        glVertex2f( 0, m_screenheight-m_console.height );
        glVertex2f( m_screenwidth, m_screenheight-m_console.height );
        glEnd();

        xshift += (float)(frame_time)*0.00002f;
        yshift += (float)(frame_time)*0.0001f;

        glColor3f( 1.0f, 1.0f, 1.0f );
		PxTextWriter::SetColor(255,255,255);
		PxTextWriter::SetSize(1);
        if( m_console.height > 16 )
		{
            PxTextWriter::Write(
				0, m_screenheight-(int)m_console.height+2,
				 m_console.buffer
			);
            if( m_console.last_msg )
			{
                j = 0;
                for( i=m_console.first_visible_msg; i<m_console.last_visible_msg+m_console.first_visible_msg-1 && m_console.last_msg-i-1>=0; i++ )
				{
                    PxTextWriter::Write( 
						0,
						m_screenheight-(int)m_console.height+2+(j+1)*16,
						m_console.line[m_console.last_msg-1-i]
					);
                    j++;
                }
            }
        }
	}
	glPopAttrib();
}

bool PxConsole::Execute(const char * cmd)
{
	PutMessage("Executing:%s", cmd);
	m_pHandler->HandleCommand( cmd );
	return true;
}

void PxConsole::Clear()
{
    int i;
    ClearLine();
    for( i=0; i<CONSOLE_MSG; i++ )
        memset( m_console.line[i], 0, CONSOLE_MSGLGTH );
    m_console.last_msg = 0;
}

