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

template <typename T>
class Vector2D
{
public:
	Vector2D(size_t sizX, size_t sizY) :SizeX (sizX), SizeY (sizY), Field (sizX * sizY)
	{}
	Vector2D() = default;

	T& Get(size_t x, size_t y)	{
		if (x >= SizeX || y >= SizeY)
			throw std::out_of_range("Index out of bounds");

		return Field[x + y * SizeX];
	}

	T& operator()(size_t x, size_t y) noexcept	{
		return Field[x + y * SizeX];
	}

	const T& operator()(size_t x, size_t y) const noexcept	{
		return Field[x + y * SizeX];
	}

	void resize(size_t sizX, size_t sizY)	{
		SizeX = sizX;
		SizeY = sizY;
		Field.resize (sizX * sizY);
	}

	const std::vector <T> GetVector()	const{
		return Field;
	}
private:
	size_t SizeX = -1, SizeY = -1;
	std::vector <T> Field;
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

	const Vector2D <GameCell>& GetGameField() const;
	std::pair <size_t, size_t> GetGameFieldSize() const;
	void SetGameFieldSize(size_t x, size_t y);

private:	
	friend class SimulationTool;
	size_t GameSizeX = 100, GameSizeY = 100;
	Vector2D <GameCell> GameField;
};