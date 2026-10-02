#pragma once
#include "WaterBox.h"

class GameSimulation;

class GameManager
{
public:
	void Init();
	void Tick(uint64_t time);

	static GameManager& GetGameManager();
	const GameSimulation& GetSimulation();
	class SimulationTool& GetSimulationTool();

	uint64_t SPT = 1000 / 60;

private:

	std::unique_ptr <GameSimulation> Simulation;
	std::unique_ptr <class SimulationTool> SimTool;
	

};