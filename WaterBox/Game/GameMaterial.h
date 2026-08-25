#pragma once


struct PixelColor
{
	uint8_t R = 0, G = 0, B = 255;
};


struct GameMaterial
{
	std::string Name = "no";
	PixelColor MinColor, MaxColor;
	bool KeepColorProportions = true;
};