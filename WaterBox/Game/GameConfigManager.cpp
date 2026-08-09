#include "GameConfigManager.h"
#include "GameSimulation.h"

const std::vector<GameMaterial>& GameConfigManager::GetMaterials()
{
	if (!AreMaterialsLoaded)
		LoadMaterials();
	return Materials;
}

GameMaterial GameConfigManager::GetMaterial(int ID)
{
	if (!AreMaterialsLoaded)
		LoadMaterials();

	if (ID < Materials.size())
		return Materials[ID];
	else
		return GameMaterial();
}

void GameConfigManager::LoadMaterials()
{

}
