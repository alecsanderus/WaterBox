#pragma once
#include "WaterBox.h"

enum class KeepRatioAxis {
	None, // Пропорции не сохраняются (растягивается независимо)
	KeepX, // Изменяет Y, чтобы сохранить пропорции относительно нормализованного X
	KeepY  // Изменяет X, чтобы сохранить пропорции относительно нормализованного Y
};
struct ScreenPoint;

struct PrimitivePoint
{
	int x = 0, y = 0;

	PrimitivePoint(const ScreenPoint& Source);
	PrimitivePoint(int Nx, int Ny) : x(Nx), y(Ny) {};
	PrimitivePoint() {};
    PrimitivePoint(std::pair <int, int> pair);


    friend PrimitivePoint operator+(const PrimitivePoint& a, const PrimitivePoint& b);
    friend PrimitivePoint operator+(const PrimitivePoint& a, const ScreenPoint& b);
	friend PrimitivePoint operator-(const PrimitivePoint& a, const PrimitivePoint& b);
	friend PrimitivePoint operator-(const PrimitivePoint& a, const ScreenPoint& b);
};

struct PrimitiveRect
{
	PrimitivePoint pos;
	PrimitivePoint size;

	friend PrimitiveRect operator+(const PrimitiveRect& a, const PrimitivePoint& b);
	friend PrimitiveRect operator-(const PrimitiveRect& a, const PrimitivePoint& b);
	friend PrimitiveRect operator+(const PrimitiveRect& a, const PrimitiveRect& b);
	friend PrimitiveRect operator-(const PrimitiveRect& a, const PrimitiveRect& b);
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


    friend ScreenPoint operator+(const ScreenPoint& a, const ScreenPoint& b);
	friend ScreenPoint operator-(const ScreenPoint& a, const ScreenPoint& b);
};

struct ScreenRect
{
	ScreenPoint pos; 
	ScreenPoint size;

	// Возвращает {X, Y, Width, Height}
	PrimitiveRect GetNormalizedRect() const;

	
    friend ScreenRect operator+(const ScreenRect& a, const ScreenPoint& b);
	friend ScreenRect operator-(const ScreenRect& a, const ScreenPoint& b);
	friend ScreenRect operator+(const ScreenRect& a, const ScreenRect& b);
	friend ScreenRect operator-(const ScreenRect& a, const ScreenRect& b);
};

