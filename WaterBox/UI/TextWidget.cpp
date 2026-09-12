#include "TextWidget.h"

void TextWidget::Render(RenderManager& renderer, const PrimitivePoint& Position)
{
	Draw(renderer, Position);
}

PrimitivePoint TextWidget::GetSize()
{
	return getSize();
}
