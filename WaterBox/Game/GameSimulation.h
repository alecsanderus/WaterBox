#pragma once
#include "WaterBox.h"
#include "GameConfigManager.h"

struct PixelColor
{
	uint8_t R = 0, G = 0, B = 255;
};

struct GameMaterial
{
	PixelColor MinColor, MaxColor;
};

PixelColor GetRandomColor(const GameMaterial& material);

struct GameCell
{	
	void Create(int ID);

	PixelColor Color;
	uint16_t OriginalMaterialID = 0;
	int16_t temp = 20;
	bool Active = 0;
};

class GameSimulation
{
public:

	const std::vector <std::vector <GameCell>>& GetGameField();
	static GameConfigManager Config;


protected:	

	uint16_t GameSizeX = 100, GameSizeY = 100;
	std::vector <std::vector <GameCell>> GameField;
};