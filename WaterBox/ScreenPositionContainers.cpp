#include "ScreenPositionContainers.h"
#include "RenderManager.h"


std::pair<int, int> ScreenPoint::GetNormalizedPoint() const
{
	const ScreenInfoStruct& ScreenInfo = *RenderManager::GetScreenInfo();

	int NewX = x;
	int NewY = y;

	if (IsVirtualCoordinates)
	{
		NewX = NewX * ScreenInfo.ScreenSizeX / DefaultResolutionX;
		NewY = NewY * ScreenInfo.ScreenSizeY / DefaultResolutionY;
		
	}

	float TargetRatio = static_cast<float>(x / y);

	if (ratioMode == KeepRatioAxis::KeepX) {
		NewY = static_cast<int>(NewX / TargetRatio);
	}
	else if (ratioMode == KeepRatioAxis::KeepY) {
		NewX = static_cast<int>(NewY * TargetRatio);
	}

	if (UseAnchor)
	{
		if (AnchorX == 1) NewX += ScreenInfo.ScreenSizeX / 2;
		if (AnchorX == 2) NewX += ScreenInfo.ScreenSizeX;

		if (AnchorY == 1) NewY += ScreenInfo.ScreenSizeY / 2;
		if (AnchorY == 2) NewY += ScreenInfo.ScreenSizeY;
	}

	return {NewX, NewY};

}

std::pair<std::pair<int, int>, std::pair<int, int>> ScreenRect::GetNormalizedRect() const
{
	auto [normX, normY] = pos.GetNormalizedPoint();
	auto [normW, normH] = size.GetNormalizedPoint();
	return { {normX, normY}, {normW, normH} };

}
