#pragma once
#include "BaseWidget.h"

class RenderManager;

class ButtonWidget : public BaseWidget
{
public:
	using ClickCallback = std::function<void()>;

	virtual void Render(RenderManager& renderer, const PrimitivePoint & Position) override;	
	virtual PrimitivePoint GetSize() override;
	virtual bool ProcessEvent(const in::InputEvent& event) override;

	virtual void SetOnClick(ClickCallback callback);	
	virtual bool Callback();

protected:

	ScreenPoint MyMinSize = { 0,0, true, false , 0, 0, KeepRatioAxis::KeepY };
	PrimitiveRect MyTriggerZone;
	ClickCallback OnClick;
};