#pragma once
#include "BaseWidget.h"
#include "ScreenPositionContainers.h"

class SizeBoxWidget : public BaseWidget
{
public:
	virtual PrimitivePoint GetSize() override;
	virtual void Render(RenderManager& renderer, const PrimitivePoint& Position) override;

	ScreenPoint Size;
	bool SetX = false, SetY = false, ModifyX = false, ModifyY = false;


protected:
	PrimitivePoint CachedSize = { 0,0 };

};