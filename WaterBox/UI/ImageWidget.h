#pragma once
#include "BaseWidget.h"
#include "ScreenPositionContainers.h"

class ImageWidget : public BaseWidget
{
public:
	virtual PrimitivePoint GetSize() override;
	virtual void Render(RenderManager& renderer, const PrimitivePoint& Position) override;

	void SetImage(std::string FileName);
	void SetImage(int ID);


	bool SizeAsImage = true;
	ScreenPoint Size;

protected:
	PrimitivePoint CachedSize = { 0,0 };
	int ImageID = -1;
	int lastX = 0, lastY = 0;

};