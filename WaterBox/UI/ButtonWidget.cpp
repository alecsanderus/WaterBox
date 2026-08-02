#include "ButtonWidget.h"
#include "RenderManager.h"

void ButtonWidget::Render(RenderManager& renderer, const PrimitivePoint & Position)
{
	BaseWidget::Render(renderer, Position);
	auto Size = MySize.GetNormalizedPoint();
	renderer.SetColor(255, 100, 100);
	renderer.DrawRect(PrimitiveRect{Position, Size});
}

PrimitivePoint ButtonWidget::GetSize()
{
	return 	MySize.GetNormalizedPoint();

}
