#pragma once
#include "BaseWidget.h"

class RenderManager;

class ButtonWidget : public BaseWidget
{
public:
	using ClickCallback = std::function<void()>;

	virtual void Render(RenderManager& renderer, const PrimitivePoint & Position) override;	
	virtual PrimitivePoint GetSize() override;
	virtual bool ProcessEvent(const ScreenEvent& event) override;

	virtual void SetOnClick(ClickCallback callback);

	

protected:

	virtual bool Callback();
	ScreenPoint MySize = { 300,150, true, false , 0, 0, KeepRatioAxis::KeepY };
	PrimitiveRect MyTriggerZone;
	ClickCallback OnClick;
};