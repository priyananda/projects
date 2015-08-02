#include "PxMapListGUIScene.h"
#include "..\..\PxInput\include\PxConfiguration.h"
#include "PxWorld.h"
#include "PxGameScene.h"

#include "glgooey/FrameWindow.h"
#include "glgooey/WindowManager.h"
#include "glgooey/core/Rectangle.h"
#include "glgooey/ListBox.h"
#include "glgooey/Panel.h"
#include "glgooey/Button.h"
#include "glgooey/FlowLayouter.h"
#include "glgooey/StaticText.h"

class _MainWindow : public Gooey::FrameWindow
{
	PxMapListGUIScene * pParent;
	Gooey::Button mButtonNext, mButtonPrev , mButtonOK;
	Gooey::Panel mPanel;
	Gooey::FlowLayouter mLayouter;
	Gooey::StaticText mTextBox;
public:
	_MainWindow( PxMapListGUIScene * parent , int sw, int sh );
	void mButtonNext_Click();
	void mButtonPrev_Click();
	void mButtonOK_Click();
	void AddFiles();
	void DrawWorld();
};

_MainWindow::_MainWindow( PxMapListGUIScene * parent, int sw, int sh )
	:Gooey::FrameWindow(
		Gooey::Core::Rectangle(0, 0, sw, sh),
		0,
		"Choose a Map"
	),
	pParent(parent),
	mPanel(Gooey::Core::Rectangle(10, 10, 20, 20), 0),
	mButtonNext(0, ""),
	mButtonPrev(0, ""),
	mButtonOK(0, "Start The Game"),
	mLayouter(Gooey::FlowLayouter::center),
	mTextBox(0, "Box Layouter")
{
	try
	{
		AddFiles();
		mButtonPrev.setSize(Gooey::Core::Vector2(40, 40));
        mButtonPrev.loadAppearance("data/ui/example2.xml", "leftButton");

        mButtonNext.setSize(Gooey::Core::Vector2(40, 40));
        mButtonNext.loadAppearance("data/ui/example2.xml", "rightButton");
		
		mButtonPrev.pressed.connect(this, &_MainWindow::mButtonPrev_Click);
		mButtonNext.pressed.connect(this, &_MainWindow::mButtonNext_Click);
		mButtonOK.pressed.connect(this, &_MainWindow::mButtonOK_Click);
		int wid = sw - 120;
		mTextBox.setSize(Gooey::Core::Vector2( wid , sh - 200 ));
        mPanel.setLayouter(NULL);
		mPanel.addChildWindow(&mButtonPrev);
		mPanel.addChildWindow(&mTextBox);
		mPanel.addChildWindow(&mButtonNext);
		mPanel.addChildWindow(&mButtonOK);
		setClientWindow(&mPanel);
		DrawWorld();
	}
	catch( Gooey::Core::StandardException & se )
	{
		PxLog::LogMessage( se.what() );
	}
}

static vector<PxWorld> worlds;
static vector<GLuint> textures;
static int g_selectedWorld = 0;

#include "../../PxGraphics/Include/PxImageProvider.h"
void _MainWindow::AddFiles()
{
	WIN32_FIND_DATA lpFindFileData;
	HANDLE h = FindFirstFile("data\\worlds\\*.pxw", &lpFindFileData);
	PxWorld theWorld;
	//<hack>
	PxImageProvider::Reset();
	//<endhack>
	while(true)
	{
		string s = lpFindFileData.cFileName;
		theWorld.Deserialize( "data\\worlds\\" + s );
		worlds.push_back( theWorld );
		string fileName = theWorld.GetBSPFileName();
		int l = fileName.find("maps");
		fileName.replace( l , 4 , "qbase\\levelshots" );
		l = fileName.find(".bsp");
		fileName.replace( l ,4 , ".jpg" );
		GLuint tex = PxTextureManager::LoadTexture(
			fileName,
			fileName
		);
		if( tex == 0 )
			textures.push_back( PxTextureManager::GetTextureId( "NOMAP" ));
		else
			textures.push_back( tex );

		if( FindNextFile(h,&lpFindFileData) == FALSE )
			break;
	}
}

void _MainWindow::mButtonPrev_Click()
{
	if( g_selectedWorld != 0 )
		-- g_selectedWorld;
	DrawWorld();
}
void _MainWindow::mButtonNext_Click()
{
	if( g_selectedWorld < worlds.size() - 1 )
		++ g_selectedWorld;
	DrawWorld();
}
void _MainWindow::mButtonOK_Click()
{
	pParent->mButton_Click();
}
void _MainWindow::DrawWorld()
{
	PxWorld & world = worlds[ g_selectedWorld ];
	mTextBox.setText( world.GetName() );
}

PxMapListGUIScene::PxMapListGUIScene( cstrref name )
	:PxGUIScene(name)
{
}

void PxMapListGUIScene::Initialize()
{
	m_pWindow = new _MainWindow(
		this,
		PxConfiguration::GetLong("g_screenwidth"),
		PxConfiguration::GetLong("g_screenheight")
	);
	Gooey::WindowManager::instance().addWindow(m_pWindow);
}

void PxMapListGUIScene::mButton_Click()
{
	PxGameScene * pGameScene = new PxGameScene("game");
	pGameScene->World = & worlds[g_selectedWorld];
	m_pSceneRegulator->AddScene( pGameScene );
	m_pSceneRegulator->Signal( eScNamedScene , "game" );
}

void PxMapListGUIScene::Dispose()
{
	if( m_pWindow )
	{
		Gooey::WindowManager::instance().removeAllWindows();
		//delete m_pWindow;
		//m_pWindow = NULL;
	}
}

void PxMapListGUIScene::CustomRender()
{
	DEFINE_VARL(g_screenwidth);
	DEFINE_VARL(g_screenheight);
	int texid = textures[ g_selectedWorld ];
	PxTextureManager::Bind( texid , eTexModeNoStretch );
	glBegin( GL_QUADS );
		glTexCoord2f( 0, 1 );glVertex2i( g_screenwidth / 2 - 100 , g_screenheight - 300 );
		glTexCoord2f( 0, 0 );glVertex2i( g_screenwidth / 2 - 100 , g_screenheight - 100 );
		glTexCoord2f( 1, 0 );glVertex2i( g_screenwidth / 2 + 100 , g_screenheight - 100 );
		glTexCoord2f( 1, 1 );glVertex2i( g_screenwidth / 2 + 100 , g_screenheight - 300 );
	glEnd();
}

