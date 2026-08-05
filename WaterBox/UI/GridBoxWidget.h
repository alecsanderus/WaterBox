#pragma once
#include "BaseWidget.h"

class GridBoxWidget : public BaseWidget
{
public:

	virtual void Render(RenderManager& renderer, const PrimitivePoint& Position) override;
	virtual PrimitivePoint GetSize() override;

	ScreenPoint MaxPossibleSize = { 9000,9000};
protected:
	PrimitivePoint CachedSize = { -1,-1 };
};