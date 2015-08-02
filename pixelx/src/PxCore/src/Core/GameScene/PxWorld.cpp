#include "PxWorld.h"
#include "..\..\PxInput\include\PxDataFileParser.h"
#include "..\..\PxPhysics\include\PxCollisionManager.h"
#include "..\..\PxGraphics\include\PxTesselatedMapManager.h"
#include "..\..\PxGraphics\include\PxObjectFactory.h"
#include "..\..\PxGraphics\include\PxQuakeMapLoader.h"
#include "..\..\PxGraphics\include\PxSkyBox.h"
#include "..\..\PxInput\include\PxConfiguration.h"
#include "..\..\PxGraphics\include\PxExtensionManager.h"
#include "..\..\PxGraphics\include\PxModelManager.h"
#include "PxEntityFactory.h"
#include "..\..\PxSound\include\PxAudioManager.h"

DECLARE_VARB(g_debug_bbox);
DECLARE_VARB(g_debug_fog);
DECLARE_VARB(g_debug_night);
DECLARE_VARB(g_debug_bsplightmap);
DECLARE_VARB(g_debug_wireframe);

extern bool g_debug_drawbsp;

void PxWorld::Deserialize( cstrref filename )
{
	PxCommandList * commands = PxDataFileParser::Parse( filename );
	if( commands == NULL )
		return;
	for(
		PxCommandList::Iterator iter = commands->Commands.begin();
		iter != commands->Commands.end();
		++iter
	)
	{
		if( (*iter)->Command == "worldname" )
			mName = (*iter)->Arguments[0];
		if( (*iter)->Command == "bsppath" )
			mBspFileName = (*iter)->Arguments[0];
		if( (*iter)->Command == "trifile" )
			mTriFileName = (*iter)->Arguments[0];
		if( (*iter)->Command == "bgsound" )
			mBGSound = (*iter)->Arguments[0];
		if( (*iter)->Command == "enablefog" )
			mEnableFog = (*iter)->Arguments[0] != "0";
		if( (*iter)->Command == "enablelight" )
			mEnableLight = (*iter)->Arguments[0] != "0";
		if( (*iter)->Command == "bot" )
			mBotName = (*iter)->Arguments[0];
	}
	int len = mName.length();
	for(int i = 0 ; i < len ; ++i )
		if( mName[i] == '+' )
			mName[i] = ' ';
}

void PxWorld::Initialize()
{
	ASSIGN_VARB(g_debug_bbox);
	ASSIGN_VARB(g_debug_fog);
	ASSIGN_VARB(g_debug_night);
	ASSIGN_VARB(g_debug_wireframe);
	ASSIGN_VARB(g_debug_bsplightmap);
	DEFINE_VARL(g_debug_bsptess);
	
	mWorldMap = PxTesselatedMapManager::Restore( mTriFileName );
	size_t count = mWorldMap->Objects.size();

	for( int i = 0 ; i < count ; ++i )
	{
		PxRuntimeObject obj = mWorldMap->Objects[i];
		PxBoundingBox bbox;
		bbox.x = obj.x ;bbox.y = obj.y ;bbox.z = obj.z ;
		bbox.length = obj.dx; bbox.width = obj.dy; bbox.height = obj.dz;
		PxSolidObject * sol = PxObjectFactory::GetObject(obj);
		PxCollisionManager::Register(sol);
		if( sol )
			mRuntimeObjects.push_back(sol);
	}
	mHuman.Register();
	PxQuakeMapLoader loader;
	mQuakeMap = loader.Load( (char *)mBspFileName.c_str() , int(g_debug_bsptess));
	mQuakeRenderer = new PxQuakeMapRenderer( mQuakeMap );
	PxCollisionManager::Register( mQuakeMap );

	PxSkyBox sbox = PxSkyBox( 
		mQuakeMap->boundingBox.x - 5 ,mQuakeMap->boundingBox.y - 5 ,mQuakeMap->boundingBox.z - 5,
		mQuakeMap->boundingBox.length  + 10 , mQuakeMap->boundingBox.width + 10 , mQuakeMap->boundingBox.height + 10
	);
	sbox.Register( &mPolygonSet );
	mWorldFragCount = PxEntityFactory::AddObjects( mQuakeMap->entities , mRuntimeObjects , mBotName );

	DEFINE_VARF(w_cam_pos_x);
	DEFINE_VARF(w_cam_pos_y);
	DEFINE_VARF(w_cam_pos_z);

	DEFINE_VARF(w_cam_view_x);
	DEFINE_VARF(w_cam_view_y);
	DEFINE_VARF(w_cam_view_z);

	mHuman.Camera.PositionCamera(
		w_cam_pos_x,w_cam_pos_y,w_cam_pos_z,
		w_cam_view_x,w_cam_view_y,w_cam_view_z,
		0, 1, 0
	);

	if( mEnableFog )
	{
		GLfloat fogColor[4]= {1.0f, 1.0f, 1.0f, 0.80f};
		glFogi(GL_FOG_MODE, GL_EXP );
		glFogfv(GL_FOG_COLOR, fogColor);
		glFogf(GL_FOG_DENSITY, 0.005f);
		glHint(GL_FOG_HINT, GL_DONT_CARE);
		glFogf(GL_FOG_START, 1.0f);
		glFogf(GL_FOG_END, 5.0f);
		glEnable(GL_FOG);
	}

	if( mBGSound != "INTRO" )
		PxAudioManager::Loop( mBGSound );
}

void PxWorld::Render(PxWindow * pWindow)
{
	glDisable( GL_BLEND );
	mHuman.Camera.frustrum.Update();
	if( g_debug_drawbsp )
		DrawBSP();
	mWorldMap->Render();
	mPolygonSet.Render();
	for( list<PxSolidObject *>::iterator iter = mRuntimeObjects.begin(); iter != mRuntimeObjects.end(); ++iter )
	{
		if( *iter == NULL )
			continue;
		if( g_debug_bbox )
			(*iter)->GetBoundingBox().Render();
		if( mHuman.Camera.frustrum.IsBoundingBoxInside( (*iter)->GetBoundingBox() ) )
			(*iter)->Render();
	}
}

void PxWorld::DrawBSP()
{
	bool _firsttime = true;

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	if( _firsttime )
	{
		_firsttime = false;
			
		//Unit 0 - replace with decal textures
		glActiveTextureARB(GL_TEXTURE0_ARB);
		glEnable(GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		//Unit 1
		glActiveTextureARB(GL_TEXTURE1_ARB);
		glEnable(GL_TEXTURE_2D);
		if( PxExtensionManager::IsEnabled( EXT_TEXENVCOMBINE ) )
		{
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
			glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB_EXT, GL_PREVIOUS_EXT);
			glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB_EXT, GL_SRC_COLOR);
		}

		if( g_debug_bsplightmap )
		{
			if( PxExtensionManager::IsEnabled( EXT_TEXENVCOMBINE ) )
			{
				glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_MODULATE);
				glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB_EXT, GL_TEXTURE);
				glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB_EXT, GL_SRC_COLOR);
				glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE_EXT, 2.0f);
			}
		}
		else
		{
			glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_REPLACE);
		}
	}
	glActiveTextureARB(GL_TEXTURE0_ARB);
	if( g_debug_bbox )
		mQuakeRenderer->RenderBoundingBox();
	mQuakeRenderer->Render( mHuman.Camera.Position() , mHuman.Camera.frustrum );
	glPopAttrib();
}

PxWorld::~PxWorld(){}
PxWorld::PxWorld(){}

