#pragma once
#include "BaseWidget.h"
#include "Game/GameMaterial.h"

class MaterialCategoryWidget : public BaseWidget
{
public:
	void Init(RenderManager* manager, int ID, class TabsBoxWidget* tabs, int TabsID);
	void SetWidth(int width);


	int OffsetX = 15, OffsetY = 10;
	ColorStr ActiveButtonColor = { 93, 232, 230, 255 };
	int ContourX = 8, ContourY = 6;

	void MakeClick();
protected:
	class TextWidget* text = nullptr;
	class ButtonWidget* but = nullptr;
	class ShapePainterWidget* background = nullptr;
	class SizeBoxWidget* sizeBox = nullptr;

	PrimitivePoint CachedSize = { 0,0 };
};


