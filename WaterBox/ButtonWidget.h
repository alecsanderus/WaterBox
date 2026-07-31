#pragma once
#include "BaseWidget.h"

class RenderManager;


class ButtonWidget : public BaseWidget
{
public:

	virtual void Render(RenderManager& renderer) override;
	ScreenRect MyRect = { {-150,-150,true,true,1,1, KeepRatioAxis::KeepY}, {300,300, true, false , 0, 0, KeepRatioAxis::KeepY }};
};