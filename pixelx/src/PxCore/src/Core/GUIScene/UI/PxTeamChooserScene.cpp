#include "PxTeamChooserScene.h"
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
#include "glgooey/CheckBox.h"
#include "glgooey/CheckBoxGroup.h"

class _PxTeamChooserUIWindow : public Gooey::FrameWindow
{
public:
	_PxTeamChooserUIWindow::_PxTeamChooserUIWindow( PxTeamChooserScene * parent, int sw, int sh )
		:Gooey::FrameWindow(
			Gooey::Core::Rectangle(0, 0, float(sw), float(sh)),
			0,
			"Choose a Map"
		),
		pParent(parent),
		mPanel(Gooey::Core::Rectangle(10, 10, 20, 20), 0),
		mButtonOK(0, "Start The Game"),
		mLayouter(Gooey::FlowLayouter::center)
	{
		Gooey::CheckBoxGroup* radioButtons = new Gooey::CheckBoxGroup;
		Gooey::CheckBox* radioButton1 = new Gooey::CheckBox(0, "Radio Button 1", radioButtons);
		Gooey::CheckBox* radioButton2 = new Gooey::CheckBox(0, "Radio Button 2", radioButtons);
		
        mPanel.setLayouter(nullptr);
		mPanel.addChildWindow(radioButton1);
		mPanel.addChildWindow(radioButton2);
		mPanel.addChildWindow(&mButtonOK);
		setClientWindow(&mPanel);
	}
	void mButtonOK_Click()
	{
		pParent->mButton_Click();
	}
private:
	PxTeamChooserScene * pParent;
	Gooey::Button mButtonOK;
	Gooey::Panel mPanel;
	Gooey::FlowLayouter mLayouter;
};

PxTeamChooserScene::PxTeamChooserScene( cstrref name )
	:PxGUIScene(name)
{
}

void PxTeamChooserScene::Initialize()
{
	m_pWindow = new _PxTeamChooserUIWindow(
		this,
		PxConfiguration::GetLong("g_screenwidth"),
		PxConfiguration::GetLong("g_screenheight")
	);
	Gooey::WindowManager::instance().addWindow(m_pWindow);
}

void PxTeamChooserScene::mButton_Click()
{
	PxGameScene * pGameScene = new PxGameScene("game");
	pGameScene->World = new PxWorld("data\\worlds\\new.pwd");
	m_pSceneRegulator->AddScene( pGameScene );
	m_pSceneRegulator->Signal( eScNamedScene , "game" );
}

void PxTeamChooserScene::Dispose()
{
	if( m_pWindow )
	{
		Gooey::WindowManager::instance().removeAllWindows();
	}
}

void PxTeamChooserScene::CustomRender()
{
	DEFINE_VARL(g_screenwidth);
	DEFINE_VARL(g_screenheight);
}