#pragma once
#include "BaseWidget.h"

class ToolWidget : public BaseWidget
{
public:
	void Init(int ID, std::string ImageName);


	int OffsetX = 15, OffsetY = 10;
//	ColorStr ActiveButtonColor = { 93, 232, 230, 255 };
	int ContourX = 8, ContourY = 6;

	void MakeClick();

protected:
	class ImageWidget* img = nullptr;
	class ButtonWidget* but = nullptr;
	class ShapePainterWidget* background = nullptr;
	class SizeBoxWidget* sizeBox = nullptr;

	PrimitivePoint CachedSize = { 0,0 };
};


