#include "VerticalBoxWidget.h"

void VerticalBoxWidget::Render(RenderManager& renderer, const PrimitivePoint& Position)
{
	PrimitivePoint Padding = { 0,0 };
	for (auto& tec : Children)
	{
		tec->Render(renderer, PrimitivePoint(Position.x, Position.y + Padding.y));
		Padding.y += tec->GetSize().y;
		Padding.x = std::max(Padding.x, tec->GetSize().x);
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
			CachedSize.y += tec->GetSize().y;
			CachedSize.x = std::max(CachedSize.x, tec->GetSize().x);
		}
		return CachedSize;
	}
}
