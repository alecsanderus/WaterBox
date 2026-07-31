#pragma once
#include "WaterBox.h"

enum class KeepRatioAxis {
	None, // Пропорции не сохраняются (растягивается независимо)
	KeepX, // Изменяет Y, чтобы сохранить пропорции относительно нормализованного X
	KeepY  // Изменяет X, чтобы сохранить пропорции относительно нормализованного Y
};

struct ScreenPoint
{
	int x = 0, y = 0;
	bool IsVirtualCoordinates = true;
	bool UseAnchor = false;
	uint8_t AnchorX = 0, AnchorY = 0; // 0 - лево, 1 - центр, 2 - право
	KeepRatioAxis ratioMode = KeepRatioAxis::None;

	const static int DefaultResolutionX = 1000, DefaultResolutionY = 1000;

	std::pair <int, int> GetNormalizedPoint() const;
	
};

struct ScreenRect
{
	ScreenPoint pos; 
	ScreenPoint size;

	// Возвращает {X, Y, Width, Height}
	std::pair<std::pair<int, int>, std::pair<int, int>> GetNormalizedRect() const;
};