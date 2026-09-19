#include "ShapePainterWidget.h"
#include "RenderManager.h"

void ShapePainterWidget::Render(RenderManager& renderer, const PrimitivePoint& Position)
{
	if (AutoSizeAsBackground)
		CachedSize = BaseWidget::GetSize();
	else
		CachedSize = Size.GetNormalizedPoint();


	if (DrawContour)
	{
		

		renderer.SetColor(ContourColor);
		//renderer.DrawRect(PrimitiveRect ( , CachedSize + ContourSize ));
		renderer.DrawRect({ Position, CachedSize });
	}

	renderer.SetColor(Color);
	if (!DrawContour)
		renderer.DrawRect({ Position, CachedSize });
	else
	{
		auto siz = ContourSize.GetNormalizedPoint();
		renderer.DrawRect({ PrimitivePoint(Position.x + siz.x * 0.5, Position.y + siz.y * 0.5), CachedSize - ContourSize });
		
	}


	BaseWidget::Render(renderer, Position);
}

PrimitivePoint ShapePainterWidget::GetSize()
{
	return CachedSize;
}
