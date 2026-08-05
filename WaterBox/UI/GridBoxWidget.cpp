#include "GridBoxWidget.h"

void GridBoxWidget::Render(RenderManager& renderer, const PrimitivePoint& Position)
{
	int PaddingX = 0, PaddingY = 0, RowPaddingY = 0;

	PrimitivePoint MaxSize = MaxPossibleSize.GetNormalizedPoint();

	for (auto& tec : Children)
	{
		auto Size = tec->GetSize();
		if (Size.x + PaddingX > MaxSize.x)
		{
			PaddingX = 0;
			PaddingY += RowPaddingY;
			RowPaddingY = 0;
		}

		tec->Render(renderer, PrimitivePoint(Position.x + PaddingX, Position.y + PaddingY));
		Size = tec->GetSize();
		RowPaddingY = std::max(RowPaddingY, Size.y);
		PaddingX += Size.x;
	}
	PaddingY += RowPaddingY;

	CachedSize = PrimitivePoint (MaxSize.x, PaddingY);

	return;
}

PrimitivePoint GridBoxWidget::GetSize()
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



	if (CachedSize != PrimitivePoint{ -1, -1 }) {
		return CachedSize;
	}

	int PaddingX = 0, PaddingY = 0, RowPaddingY = 0;
	PrimitivePoint MaxSize = MaxPossibleSize.GetNormalizedPoint();

	for (auto& tec : Children) {
		auto Size = tec->GetSize();

		if (Size.x + PaddingX > MaxSize.x) {
			PaddingX = 0;
			PaddingY += RowPaddingY;
			RowPaddingY = 0;
		}

		RowPaddingY = std::max(RowPaddingY, Size.y);
		PaddingX += Size.x;
	}

	PaddingY += RowPaddingY;
	CachedSize = PrimitivePoint(MaxSize.x, PaddingY);

	return CachedSize;
}
