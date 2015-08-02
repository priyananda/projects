#ifndef _PIXELX_MAPLISTGUI
#define _PIXELX_MAPLISTGUI

#include "PxGUIScene.h"

namespace Gooey{ class FrameWindow; }

class PxMapListGUIScene : public PxGUIScene
{
	Gooey::FrameWindow * m_pWindow;
public:
	PxMapListGUIScene( cstrref name );
	void Initialize();
	void Dispose();
	void mButton_Click();

	void CustomRender();
};
#endif

