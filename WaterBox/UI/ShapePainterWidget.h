#pragma once
#include "BaseWidget.h"
#include "ColorContainer.h"

class ShapePainterWidget : public BaseWidget
{
public:
	virtual void Render(RenderManager& renderer, const PrimitivePoint& Position) override;
	virtual PrimitivePoint GetSize() override;

	bool AutoSizeAsBackground = false;
	ScreenPoint Size;
	ColorStr Color;

	ScreenPoint ContourSize;
	ColorStr ContourColor;
	bool DrawContour = false;
	

protected:
	PrimitivePoint CachedSize = { 0,0 };
	
};