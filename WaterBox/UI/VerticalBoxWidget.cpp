#include "VerticalBoxWidget.h"

void VerticalBoxWidget::Render(RenderManager& renderer, const PrimitivePoint& Position)
{
	PrimitivePoint Padding = { 0,0 };
	for (auto& tec : Children)
	{
		tec->Render(renderer, PrimitivePoint(Position.x, Position.y + Padding.y));
		Padding = Padding + tec->GetSize();
	}
	CachedSize = Padding;

	return;
}

PrimitivePoint VerticalBoxWidget::GetSize()
{
	if (CachedSize != PrimitivePoint{ -1,-1 })
		return CachedSize;
	else
	{
		CachedSize = { 0,0 };
		for (auto& tec : Children)
		{
			CachedSize = CachedSize + tec->GetSize();
		}
		return CachedSize;
	}
}
