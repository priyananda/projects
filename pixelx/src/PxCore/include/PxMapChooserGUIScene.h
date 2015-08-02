#ifndef _PIXELX_MAPCHOOSERGUI
#define _PIXELX_MAPCHOOSERGUI

#include "PxGUIScene.h"

namespace Gooey{ class FrameWindow; }

class PxMapChooserGUIScene : public PxGUIScene
{
	Gooey::FrameWindow * m_pWindow;
public:
	PxMapChooserGUIScene( cstrref name );
	void Initialize();
	void Dispose();
	void mButton_Click();
};
#endif

