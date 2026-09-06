#pragma once


struct PixelColor
{
	uint8_t R = 0, G = 0, B = 255;
};


struct GameMaterial
{
	std::string Name = "no";
	int ID = 0;
	bool IsLoaded = false;

	std::string CategoryID;
	bool CanBeShown = true;
	PixelColor MinColor, MaxColor;
	bool KeepColorProportions = true;
};

struct MaterialCategory
{
	std::string Name = "no";
	int ID = 0;
	bool IsLoaded = false;

	bool CanBeShown = true;
	PixelColor Color;
};