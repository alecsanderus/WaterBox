#pragma once
#include "BaseWidget.h"
#include "Game/GameMaterial.h"

class MaterialCardWidget : public BaseWidget
{
public:
	void Init(class RenderManager* manager, int ID);
	void SetWidth(int width);
	virtual PrimitivePoint GetSize() override;


protected:
	class TextWidget* text = nullptr;
	class ButtonWidget* but = nullptr;
	class ShapePainterWidget* background = nullptr;
	class SizeBoxWidget* sizeBox = nullptr;

	PrimitivePoint CachedSize = { 0,0 };
	ColorStr BackgroundColor = { 50,50,255,255 };

	int OffsetX = 15, OffsetY = 10;
};


