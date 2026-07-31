#include "ButtonWidget.h"
#include "RenderManager.h"

void ButtonWidget::Render(RenderManager& renderer, const PrimitivePoint & Position)
{
	BaseWidget::Render(renderer, Position);
	auto Rect = MyRect.GetNormalizedRect();
	renderer.DrawRect(Rect + Position);	
}
