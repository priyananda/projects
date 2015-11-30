#include "PxQuake2Model.h"
#include "PxTextureManager.h"

bool PxQuake2ModelLoader::Load(char* filename)
{
	FILE * file;
	PxQuake2Header header;

	fopen_s(&file, filename, "rb");
	if(file == NULL)
		return false;
	fread(&header, sizeof(PxQuake2Header), 1, file);
	if(header.magic != QUAKE2_MAGIC)
		return false;
	if(header.version != QUAKE2_VERSION)
		return false;

	frames = new char[header.frameSize*header.numFrames];

	fseek(file, header.offsetFrames, SEEK_SET);
	fread(frames, header.frameSize*header.numFrames, 1, file);

	glCommands = new long [header.numGlCommands*sizeof(long)];
	fseek(file, header.offsetGlCommands, SEEK_SET);
	fread(glCommands, header.numGlCommands*sizeof(long), 1, file);

	numFrames	 = header.numFrames;
	numGlCommands= header.numGlCommands;
	frameSize	 = header.frameSize;
	numTriangles = header.numTriangles;

	fclose(file);	

	return true;
}

void PxQuake2ModelLoader::Render(int numFrame)
{
	static PxQuake2Vertex vertList[100];
	PxQuake2Frame	*currentFrame;
	PxQuake2Vertex	v1;
	long*			command;
    float			texcoord[2];
	int				loop;
	int				vertIndex;
	int				type;
	int				numVertex;
	int				index;

	currentFrame = (PxQuake2Frame*) ((char*)frames+frameSize*numFrame);
	command	= glCommands;

	while( (*command)!= 0 )
	{
		if( *command > 0)	//This is a triangle strip
		{
			numVertex = *command; 
			command++; 
			type = 0;
		}
		else			//This is a triangle fan
		{
			numVertex= -*command; 
			command++; 
			type= 1;
		}
		if( numVertex < 0 )
			numVertex= -numVertex;

		index = 0;
		for(loop=0; loop<numVertex; loop++)
		{
			vertList[index].u= *((float*)command); 
			command++;
			vertList[index].v= *((float*)command); 
			command++;
			vertIndex= *command; 
			command++;

			vertList[index].x= ( (currentFrame->vertices[vertIndex].vertex[0]* 
								  currentFrame->scale[0])+ 
								  currentFrame->translate[0]);
			vertList[index].z= -((currentFrame->vertices[vertIndex].vertex[1]* 
								  currentFrame->scale[1])+ 
								  currentFrame->translate[1]);
			vertList[index].y= ( (currentFrame->vertices[vertIndex].vertex[2]*
								  currentFrame->scale[2])+
								  currentFrame->translate[2]);
			index++;
		}

		if(type==0)
		{
			glBegin(GL_TRIANGLE_STRIP);
			for(loop=0; loop<index; loop++)
			{
				v1.x=(vertList[loop].x);
				v1.y=(vertList[loop].y);
				v1.z=(vertList[loop].z);

                texcoord[0]= vertList[loop].u;
				texcoord[1]= vertList[loop].v;

				glTexCoord2fv(texcoord);
				glVertex3f( v1.x,v1.y,v1.z);
			}
			glEnd();
		}

		else
		{
			glBegin(GL_TRIANGLE_FAN);
			for(loop=0; loop<index; loop++)
			{
				v1.x=(vertList[loop].x);
				v1.y=(vertList[loop].y);
				v1.z=(vertList[loop].z);

                texcoord[0]= vertList[loop].u;
				texcoord[1]= vertList[loop].v;

				glTexCoord2fv(texcoord);
                glVertex3f( v1.x,v1.y,v1.z);
            }
			glEnd();
		}

		}
}

void PxQuake2ModelLoader::Animate(int startFrame, int EndFrame, float percent)
{
	if(currentFrame==-1 || currentFrame>endFrame)
	{
		currentFrame= startFrame;
		nextFrame	= currentFrame+1;
		endFrame	= EndFrame;
	}

	if(interpolation>1.0f)
	{
		interpolation= 0.0f;
		currentFrame = nextFrame;
		nextFrame	 = currentFrame+1;
	}

	interpolation += percent;
	Render(currentFrame);
}

void PxQuake2ModelLoader::SetState(int state)
{	
	switch(state)
	{
		case IDLE1:
			stateStart	 = IDLE1_START;
			stateEnd	 = IDLE1_END;
			currentFrame =-1;
			break;
		case RUN:
			stateStart	 = RUN_START;
			stateEnd	 = RUN_END;
			currentFrame =-1;
			break;
		case SHOT_STAND:
			stateStart	 = SHOT_STAND_START;
			stateEnd	 = SHOT_STAND_END;
			currentFrame =-1;
			break;
		case SHOT_SHOULDER:
			stateStart	 = SHOT_SHOULDER_START;
			stateEnd	 = SHOT_SHOULDER_END;
			currentFrame =-1;
			break;
		case JUMP:
			stateStart	 = JUMP_START;
			stateEnd	 = JUMP_END;
			currentFrame =-1;
			break;
		case IDLE2:
			stateStart	 = IDLE2_START;
			stateEnd	 = IDLE2_END;
			currentFrame =-1;
			break;
		case SHOT_FALLDOWN:
			stateStart	 = SHOT_FALLDOWN_START;
			stateEnd	 = SHOT_FALLDOWN_END;
			currentFrame =-1;
			break;
		case IDLE3:
			stateStart	 = IDLE3_START;
			stateEnd	 = IDLE3_END;
			currentFrame =-1;
			break;
		case IDLE4:
			stateStart	 = IDLE4_START;
			stateEnd	 = IDLE4_END;
			currentFrame =-1;
			break;
		case CROUCH:
			stateStart	 = CROUCH_START;
			stateEnd	 = CROUCH_END;
			currentFrame =-1;
			break;
		case CROUCH_CRAWL:
			stateStart	 = CROUCH_CRAWL_START;
			stateEnd	 = CROUCH_CRAWL_END;
			currentFrame =-1;
			break;
		case CROUCH_IDLE:
			stateStart	 = CROUCH_IDLE_START;
			stateEnd	 = CROUCH_IDLE_END;
			currentFrame =-1;
			break;
		case CROUCH_DEATH:
			stateStart	 = CROUCH_DEATH_START;
			stateEnd	 = CROUCH_DEATH_END;
			currentFrame =-1;
			break;
		case DEATH_FALLBACK:
			stateStart	 = DEATH_FALLBACK_START;
			stateEnd	 = DEATH_FALLBACK_END;
			currentFrame =-1;
			break;
		case DEATH_FALLFORWARD:
			stateStart	 = DEATH_FALLFORWARD_START;
			stateEnd	 = DEATH_FALLFORWARD_END;
			currentFrame =-1;
			break;
		case DEATH_FALLBACKSLOW:
			stateStart	 = DEATH_FALLBACKSLOW_START;
			stateEnd	 = DEATH_FALLBACKSLOW_END;
			currentFrame =-1;
			break;
	}	
}

PxQuake2ModelCore::PxQuake2ModelCore(cstrref filename )
{
	m_loader.Load( (char *)filename.c_str() );
}

void PxQuake2ModelCore::Render()
{
	PxTextureManager::Bind( m_texid, eTexModeNoStretch );
	m_loader.Render(IDLE1);
}

void PxQuake2ModelCore::Animate(int sf,int ef,float interp)
{
	PxTextureManager::Bind( m_texid, eTexModeNoStretch );
	m_loader.Animate(sf,ef,interp );
}

void PxQuake2ModelCore::SetTexture(cstrref name)
{
	m_texid = PxTextureManager::GetTextureId( name );
}

