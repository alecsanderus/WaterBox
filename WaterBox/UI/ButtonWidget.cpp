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
	if (event.Type != ScreenEvent::ScreenEventType::UP || event.ButtonType != ScreenEvent::ScreenEventButtonType::LMB)
		return false;

	if (!MyTriggerZone.Contains(event.Point))
		return false;
	r = ~r;

	return true;
}
