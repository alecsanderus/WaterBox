#include "GameManager.h"
#include "GameSimulation.h"
#include "GameConfigManager.h"

void GameManager::Init()
{
	ConfigManager = std::make_unique <GameConfigManager>();
	Simulation = std::make_unique <GameSimulation> ();
	Simulation->SetGameFieldSize(100, 100);
}

void GameManager::Tick()
{

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
