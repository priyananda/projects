#ifndef _PIXELX_QUAKE2_H
#define _PIXELX_QUAKE2_H

#include "PxVertex.h"
#include "PxModel.h"

/* MD2 constants */
#define MAX_TRIANGLES 4096
#define MAX_VERTICES  2048
#define MAX_TEXCOORDS 2048
#define MAX_FRAMES    512
#define QUAKE2_MAGIC  844121161
#define QUAKE2_VERSION 8

#define CHUNK1 0
#define CHUNK2 1
#define CHUNK3 2
#define CHUNK4 3

/* MD2 state constants */
#define ANIMATE_CURRENT -100

#define IDLE1				0
#define RUN					1
#define SHOT_STAND			2
#define SHOT_SHOULDER		3
#define JUMP				4
#define IDLE2				5
#define SHOT_FALLDOWN		6
#define IDLE3				7
#define IDLE4				8
#define CROUCH				9
#define CROUCH_CRAWL		10
#define CROUCH_IDLE			11
#define CROUCH_DEATH		12
#define DEATH_FALLBACK		13
#define DEATH_FALLFORWARD	14
#define DEATH_FALLBACKSLOW	15

#define IDLE1_START					0
#define IDLE1_END					39
#define RUN_START					40
#define RUN_END						45
#define SHOT_STAND_START			46
#define SHOT_STAND_END				60
#define SHOT_SHOULDER_START			61
#define SHOT_SHOULDER_END			66
#define JUMP_START					67
#define JUMP_END					73
#define IDLE2_START					74
#define IDLE2_END					95
#define SHOT_FALLDOWN_START			96
#define SHOT_FALLDOWN_END			112
#define IDLE3_START					113
#define IDLE3_END					122
#define IDLE4_START					123
#define IDLE4_END					135
#define CROUCH_START				136
#define CROUCH_END					154
#define CROUCH_CRAWL_START			155
#define CROUCH_CRAWL_END			161
#define CROUCH_IDLE_START			162
#define CROUCH_IDLE_END				169
#define CROUCH_DEATH_START			170
#define CROUCH_DEATH_END			177
#define DEATH_FALLBACK_START		178
#define DEATH_FALLBACK_END			185
#define DEATH_FALLFORWARD_START		186
#define DEATH_FALLFORWARD_END		190
#define DEATH_FALLBACKSLOW_START	191
#define DEATH_FALLBACKSLOW_END		198

struct PxQuake2Header
{
	int magic;				//The 'magic' number (always 844121161)
	int version;			//The version number of the file (always 8)
	int skinWidth;			//The width of the model's skin
	int skinHeight;			//The height of the model's skin
	int frameSize;			//The size of each frame (in BYTEs)
	int numSkins;			//The model's number of skins
	int numVertices;		//The model's number of vertices
	int numTexcoords;		//The model's number of texture coordinates (most likely, its not the same number as the vertices)
	int numTriangles;		//The number of triangles that make up the model
	int numGlCommands;		//The number of DWORDs (4 bytes) in the GLcommand list (which decide to render the model with tri strips, or fans)
	int numFrames;			//The number of frames (of animation) that the model has
	int offsetSkins;		//Offset in the file of the model, to where the skin information is
	int offsetTexcoords;	//Offset in the file of the model, to where the texture coordinate information is
	int offsetTriangles;	//Offset in the file of the model, to where the traingle information is
	int offsetFrames;		//Offset in the file of the model, to where the first frame information is given
	int offsetGlCommands;	//Offset in the file of the model, to where the GLcommand information is
	int offsetEnd;			//Offset in the file of the model, to where the end of it is
};

struct PxQuake2LoadVertex
{
	unsigned char vertex[3];		//Scaled version of the model's 'real' vertex coordinate
	unsigned char lightNormalIndex;	//An index into the table of normals, kept by Quake 2
};

struct PxQuake2Frame
{
	float	   scale[3];		//The scale used by the model's 'fake' vertex structure
	float	   translate[3];	//The translation used by the model's 'fake' vertex structure
	char	   name[16];		//The name for the frame
	PxQuake2LoadVertex vertices[1];		//An array of MD2_VERTEX structures
};

struct PxQuake2Vertex
{
	float x,y,z,u,v;
};
class PxQuake2ModelLoader
{
private:	
	int numGlCommands;
	long* glCommands;

	int numTriangles;

public:
	int stateStart;
	int stateEnd;

	int frameSize;
	int numFrames;
	char* frames;

	int currentFrame;
	int nextFrame;
	int endFrame;
	float interpolation;

	float viewer_x;
	float viewer_y;
	float viewer_z;

	bool Load(char* filename);
	void Render(int numFrame);
	void RenderShadow(int numFrame);
	void Animate(int startFrame, int EndFrame, float Interpolation);
	void AnimateShadow(int startFrame, int EndFrame, float Interpolation);
	void SetState(int state);

	PxQuake2ModelLoader() : stateStart(IDLE1_START), stateEnd(IDLE1_END),
		numGlCommands(0), frameSize(0), numFrames(0), 
		currentFrame(IDLE1_START), nextFrame(currentFrame+1),
		endFrame(IDLE1_END), interpolation(0.0f)
	{}

	~PxQuake2ModelLoader()
	{	
		if(glCommands)
			delete [] glCommands;
		if(frames)
			delete [] frames;
	}
};

class PxQuake2ModelCore : public PxModelCore
{
	PxQuake2ModelLoader m_loader;
	GLuint m_texid;
public:
	PxQuake2ModelCore(cstrref filename);
	void Render();
	void Register( PxPolygonCollection * pColl ){}
	void Animate( int startFrame, int ef , float interp);
	void SetTexture( cstrref name );
};

#endif

