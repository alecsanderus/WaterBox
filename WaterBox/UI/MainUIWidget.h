#pragma once
#include "BaseWidget.h"

class MainUIWidget : public BaseWidget
{
public:
	void Init();
	virtual void Render(RenderManager& renderer, const PrimitivePoint& Position) override;

protected:

	class GridBoxWidget* GridBox;
	class VerticalBoxWidget* VerticalBox;
	class HorizontalBoxWidget* HorizontalBox;
};