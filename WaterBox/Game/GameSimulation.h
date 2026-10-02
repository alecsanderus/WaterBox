#pragma once
#include "WaterBox.h"
#include "GameConfigManager.h"


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

	const std::vector <T>& GetVector()	const{
		return Field;
	}
	std::vector <T>& GetVector()	{
		return Field;
	}
private:
	size_t SizeX = -1, SizeY = -1;
	std::vector <T> Field;
};


struct GameCell
{
	void Create(int ID);
	void Destroy();

	ColorStr Color;
	uint16_t OriginalMaterialID = 0;
	bool Active = 0;
	uint8_t Updating = 0;

	int temp = 20;

	float VelX = 0, VelY = 0;
};



class GameSimulation
{
public:

	const Vector2D <GameCell>& GetGameField() const;
	std::pair <size_t, size_t> GetGameFieldSize() const;
	void SetGameFieldSize(size_t x, size_t y);

	void SimulationTick();



	void ProcessGravity();
	void ProcessDefaultPhysic();


private:	

	inline uint32_t Deterministic_hash(uint32_t x, uint32_t y, uint32_t tick);
	inline float RandomFloat(uint32_t x, uint32_t y, uint32_t tick);

	friend class SimulationTool;
	size_t GameSizeX = 100, GameSizeY = 100;
	Vector2D <GameCell> GameField;

	uint32_t TecTick = 0;
};