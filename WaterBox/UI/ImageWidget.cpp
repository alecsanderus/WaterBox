#include "ImageWidget.h"
#include "Game/GameConfigManager.h"
#include "RenderManager.h"

PrimitivePoint ImageWidget::GetSize()
{
	if (SizeAsImage)
		return {lastX, lastY};
	else
		return Size.GetNormalizedPoint();
}

void ImageWidget::Render(RenderManager& renderer, const PrimitivePoint& Position)
{
	if (ImageID != -1)
	{
		auto& img = GameConfigManager::GetGameConfigManager().Images.GetElement(ImageID);
		if (SizeAsImage)
		{
			renderer.DrawTexture(img.texture, PrimitiveRect { Position, PrimitivePoint {(int)img.x,(int)img.y} } );
			lastX = img.x;
			lastY = img.y;
		}
		else		
			renderer.DrawTexture(img.texture, {Position, Size.GetNormalizedPoint()});

	}
}

void ImageWidget::SetImage(std::string FileName)
{
	int NewID = GameConfigManager::GetGameConfigManager().Images.GetElementIdIfHasIt(FileName);
	if (NewID != -1)
		SetImage(NewID);
}

void ImageWidget::SetImage(int ID)
{
	ImageID = ID;
}
