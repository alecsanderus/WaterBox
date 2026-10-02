#pragma once
#include "UI/ColorContainer.h"

enum class StateCategoryEnum : uint8_t
{
	unmovable,
	solid,
	liquid,
	gas

};


struct GameMaterial
{
	std::string Name = "no";
	int ID = 0;
	bool IsLoaded = false;

	int ShowPriority = 0;
	int CategoryID;
	bool CanBeShown = true;
	ColorStr MinColor, MaxColor;
	bool KeepColorProportions = true;

	StateCategoryEnum StateCategory = StateCategoryEnum::unmovable;
	float InitialTemperature = 20.0;
	float Density = 1000;
	float ThermalConductivity = 1;
	float SpecificHeatCapacity = 1000;
};

struct MaterialCategory
{
	std::string Name = "no";
	int ID = 0;
	bool IsLoaded = false;

	bool CanBeShown = true;
	ColorStr Color;
};