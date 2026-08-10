#pragma once
#include "WaterBox.h"

class GameSimulation;

class GameManager
{
public:
	void Init();
	void Tick();

	static GameManager& GetGameManager();
	const GameSimulation& GetSimulation();

private:

	std::unique_ptr <GameSimulation> Simulation;
	std::unique_ptr <class GameConfigManager> ConfigManager;


};