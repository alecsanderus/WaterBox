#pragma once
#include "UI/ColorContainer.h"

struct GameMaterial
{
	std::string Name = "no";
	int ID = 0;
	bool IsLoaded = false;

	std::string CategoryID;
	bool CanBeShown = true;
	ColorStr MinColor, MaxColor;
	bool KeepColorProportions = true;
};

struct MaterialCategory
{
	std::string Name = "no";
	int ID = 0;
	bool IsLoaded = false;

	bool CanBeShown = true;
	ColorStr Color;
};