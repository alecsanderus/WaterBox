#pragma once
#include "WaterBox.h"
#include "GameConfigManager.h"

#include "Vector2D.h"



struct GameCell
{
	void Create(int ID);
	void Destroy();

	ColorStr Color;
	uint16_t OriginalMaterialID = 0;
	bool Active = false;
	uint8_t Updating = 0;

	float temp = 20;

	float VelX = 0.f, VelY = 0.f;
	float Pressure = 0.f;
};



class GameSimulation
{
public:

	[[nodiscard]] const Vector2D <GameCell>& GetGameField() const;
	[[nodiscard]] std::pair <size_t, size_t> GetGameFieldSize() const;
	void SetGameFieldSize(int x, int y);

	void SimulationTick();



	void ProcessGravity();
	void ProcessDefaultPhysic();
	void ProcessLiquidPhysic();
	static void DoCollision (GameCell& a, GameCell&b, uint8_t direction, int x, int y, float size = 1);
	float DoLiteCollision (GameCell& a, GameCell& b, uint8_t direction, int& xA, int& yA, int& xB, int& yB);
	void NormalizeVelocity();


private:
	static inline uint32_t Deterministic_hash(uint32_t x, uint32_t y, uint32_t tick);
	static inline float RandomFloat(uint32_t x, uint32_t y, uint32_t tick);

	friend class SimulationTool;
	int GameSizeX = 100, GameSizeY = 100;
	Vector2D <GameCell> GameField;

	uint32_t TecTick = 0;
};