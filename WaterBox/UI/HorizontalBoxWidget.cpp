#include "HorizontalBoxWidget.h"

void HorizontalBoxWidget::Render(RenderManager& renderer, const PrimitivePoint& Position)
{
	PrimitivePoint Padding = { 0,0 };
	for (auto& tec : Children)
	{
		tec->Render(renderer, PrimitivePoint(Position.x + Padding.x, Position.y));
		Padding.x += tec->GetSize().x;
		Padding.y = std::max(Padding.y, tec->GetSize().y);
	}
	CachedSize = Padding;

	return;
}

PrimitivePoint HorizontalBoxWidget::GetSize()
{
	if (CachedSize != PrimitivePoint{ -1,-1 })
		return CachedSize;
	else
	{
		CachedSize = { 0,0 };
		for (auto& tec : Children)
		{
			CachedSize.x += tec->GetSize().x;
			CachedSize.y = std::max(CachedSize.y, tec->GetSize().y);
		}
		return CachedSize;
	}
}


