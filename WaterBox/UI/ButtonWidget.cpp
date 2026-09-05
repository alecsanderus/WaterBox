#include "ButtonWidget.h"
#include "RenderManager.h"

void ButtonWidget::Render(RenderManager& renderer, const PrimitivePoint & Position)
{
	BaseWidget::Render(renderer, Position);

	auto Size = MySize.GetNormalizedPoint();
	PrimitiveRect rect{Position, Size};

	renderer.SetColor(r, 100, 100);
	renderer.DrawRect(rect);

	MyTriggerZone = rect;
}

PrimitivePoint ButtonWidget::GetSize()
{
	return 	MySize.GetNormalizedPoint();

}

bool ButtonWidget::ProcessEvent(const ScreenEvent& event)
{
	if (!MyTriggerZone.Contains(event.Point))
		return false;

	if (event.Type != ScreenEventType::UP || event.ButtonType != ScreenEventButtonType::LMB)
		return true;




	return Callback ();
}

void ButtonWidget::SetOnClick(ClickCallback callback)
{
	OnClick = callback;
}

bool ButtonWidget::Callback()
{
	if (!OnClick)
		return false;
	
	OnClick();
	return true;
}



