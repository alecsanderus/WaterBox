#pragma once
#include "BaseWidget.h"

class RenderManager;


class ButtonWidget : public BaseWidget
{
public:

	virtual void Render(RenderManager& renderer, const PrimitivePoint & Position) override;
	ScreenPoint MySize = { 300,150, true, false , 0, 0, KeepRatioAxis::KeepY };
	virtual PrimitivePoint GetSize() override;


};