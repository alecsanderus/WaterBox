#include "ShapePainterWidget.h"
#include "RenderManager.h"

void ShapePainterWidget::Render(RenderManager& renderer, const PrimitivePoint& Position)
{
	if (AutoSizeAsBackground)
	{
		CachedSize = BaseWidget::GetSize();
	}

	renderer.SetColor(Color);
	renderer.DrawRect({ Position, CachedSize });


	BaseWidget::Render(renderer, Position);
}

PrimitivePoint ShapePainterWidget::GetSize()
{
	return CachedSize;
}
