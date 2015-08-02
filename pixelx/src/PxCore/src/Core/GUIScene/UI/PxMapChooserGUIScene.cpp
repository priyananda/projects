#include "PxMapChooserGUIScene.h"
#include "..\..\PxInput\include\PxConfiguration.h"
#include "PxWorld.h"
#include "PxGameScene.h"

#include "glgooey/FrameWindow.h"
#include "glgooey/WindowManager.h"
#include "glgooey/core/Rectangle.h"
#include "glgooey/ListBox.h"
#include "glgooey/Panel.h"
#include "glgooey/Button.h"


class _MapChooserWindow : public Gooey::FrameWindow
{
	PxMapChooserGUIScene * pParent;
	Gooey::Button mButton;
	Gooey::ListBox mListBox;
	Gooey::Panel mPanel;
public:
	_MapChooserWindow( PxMapChooserGUIScene * parent );
	void mButton_Click();
	void AddFiles();
};

_MapChooserWindow::_MapChooserWindow( PxMapChooserGUIScene * parent )
	:Gooey::FrameWindow(
		Gooey::Core::Rectangle(90, 120, 340, 420),
		0,
		"Choose a Map"
	),
	pParent(parent),
	mListBox(0, Gooey::Core::Rectangle(0, 0, 200, 240)),
	mPanel(Gooey::Core::Rectangle(10, 10, 20, 20), 0),
	mButton(0, "Play")
{
	try
	{
		//mButton.loadAppearance("data/ui/example2.xml", "leftButton");
		AddFiles();
		mButton.pressed.connect(this, &_MapChooserWindow::mButton_Click);
		mPanel.addChildWindow(&mListBox);
		mPanel.addChildWindow(&mButton);
		setClientWindow(&mPanel);
	}
	catch( Gooey::Core::StandardException & se )
	{
		PxLog::LogMessage( se.what() );
	}
}

static vector<PxWorld> worlds;
void _MapChooserWindow::AddFiles()
{
	WIN32_FIND_DATA lpFindFileData;
	HANDLE h = FindFirstFile("data\\worlds\\*.pxw", &lpFindFileData);
	PxWorld theWorld;
	while(true)
	{
		string s = lpFindFileData.cFileName;
		theWorld.Deserialize( "data\\worlds\\" + s );
		mListBox.addString(theWorld.GetName());
		worlds.push_back( theWorld );

		if( FindNextFile(h,&lpFindFileData) == FALSE )
			break;
	}
}
static int g_selectedWorld = 0;
void _MapChooserWindow::mButton_Click()
{
	g_selectedWorld = mListBox.selectedIndex();
	pParent->mButton_Click();
}
PxMapChooserGUIScene::PxMapChooserGUIScene( cstrref name )
	:PxGUIScene(name)
{
}

void PxMapChooserGUIScene::Initialize()
{
	m_pWindow = new _MapChooserWindow(this);
	Gooey::WindowManager::instance().addWindow(m_pWindow);
}

void PxMapChooserGUIScene::mButton_Click()
{
	PxGameScene * pGameScene = new PxGameScene("game");
	pGameScene->World = & worlds[g_selectedWorld];
	m_pSceneRegulator->AddScene( pGameScene );
	m_pSceneRegulator->Signal( eScNamedScene , "game" );
}

void PxMapChooserGUIScene::Dispose()
{
	if( m_pWindow )
	{
		//delete m_pWindow;
		//m_pWindow = NULL;
	}
}

