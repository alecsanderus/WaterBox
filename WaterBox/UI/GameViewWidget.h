#pragma once
#include "BaseWidget.h"

class GameViewWidget : public BaseWidget
{
public:
	GameViewWidget();
	virtual PrimitivePoint GetSize() override;


	virtual void Render(RenderManager& renderer, const PrimitivePoint& Position) override;

};