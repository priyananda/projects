#ifndef _PIXELX_TEAMCHOOSERUI
#define _PIXELX_TEAMCHOOSERUI

#include "PxGUIScene.h"

namespace Gooey{ class FrameWindow; }

class PxTeamChooserScene : public PxGUIScene
{
	Gooey::FrameWindow * m_pWindow;
public:
	PxTeamChooserScene( cstrref name );
	void Initialize();
	void Dispose();
	void mButton_Click();
	void CustomRender();
};
#endif