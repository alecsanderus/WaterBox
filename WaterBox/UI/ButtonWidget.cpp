#include "ButtonWidget.h"
#include "RenderManager.h"
#include "InputEvent.h"

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

bool ButtonWidget::ProcessEvent(const in::InputEvent& event)
{
	if (!MyTriggerZone.Contains(PrimitivePoint (event.x, event.y)))
		return false;

	if (!event.isMouseButton())
		return true;

	if (auto& ButEvent = std::get <in::MouseButtonEvent> (event.data);
		ButEvent.action != in::InputAction::Press || ButEvent.button != in::MouseButton::Left)
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



