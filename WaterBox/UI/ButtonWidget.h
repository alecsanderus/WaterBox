#pragma once
#include "BaseWidget.h"

class RenderManager;


class ButtonWidget : public BaseWidget
{
public:

	virtual void Render(RenderManager& renderer, const PrimitivePoint & Position) override;	
	virtual PrimitivePoint GetSize() override;
	virtual bool ProcessEvent(const ScreenEvent& event) override;

protected:
	int r = 255;
	ScreenPoint MySize = { 300,150, true, false , 0, 0, KeepRatioAxis::KeepY };
	PrimitiveRect MyTriggerZone;
};