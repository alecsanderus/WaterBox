#include "GameManager.h"
#include "GameSimulation.h"
#include "GameConfigManager.h"
#include "SimulationTool.h"

void GameManager::Init()
{
	Simulation = std::make_unique <GameSimulation> ();
	Simulation->SetGameFieldSize(1000, 1000);

	SimTool = std::make_unique <SimulationTool>();
	SimTool->SetSimulation(Simulation.get());
}

void GameManager::Tick(uint64_t time)
{
	static uint64_t LastTime = 0;
	if (time >= LastTime + SPT)
	{
		if (time >= LastTime + SPT * 10)
			LastTime = time;
		else
			LastTime += SPT;

		Simulation->SimulationTick();
	}
}

GameManager& GameManager::GetGameManager()
{
	static GameManager Manager;
	return Manager;
}

const GameSimulation& GameManager::GetSimulation()
{
	return *Simulation;
}

SimulationTool& GameManager::GetSimulationTool()
{
	return *SimTool;
}
