#pragma once
#include "WaterBox.h"
struct ColorStr
{
	uint8_t r = 50, g = 50, b = 255, a = 255;
	bool operator==(const ColorStr&) const = default;
	inline uint32_t PackColor() {
		return (r << 24) | (g << 16) | (b << 8) | a;
	}
	static ColorStr GetRandomColor(const ColorStr& a, const ColorStr& b, const bool KeepProportions);
	static ColorStr GetAverageColor(const ColorStr& c1, const ColorStr& c2);
	static ColorStr GetContrastColor(const ColorStr& background);
	
	
};