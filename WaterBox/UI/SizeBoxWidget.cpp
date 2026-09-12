#include "SizeBoxWidget.h"

PrimitivePoint SizeBoxWidget::GetSize()
{
	return CachedSize;
}


void SizeBoxWidget::Render(RenderManager& renderer, const PrimitivePoint& Position)
{
	auto siz = Size.GetNormalizedPoint();

	auto NewPos = Position;

	if (ModifyX) NewPos.x += siz.x * 0.5;
	if (ModifyY) NewPos.y += siz.y * 0.5;

	BaseWidget::Render(renderer, NewPos);



	if (!(SetX && SetY))
		CachedSize = BaseWidget::GetSize();

	

	if (SetX) CachedSize.x = siz.x;
	if (SetY) CachedSize.y = siz.y;

	if (ModifyX) CachedSize.x += siz.x;
	if (ModifyY) CachedSize.y += siz.y;
}
