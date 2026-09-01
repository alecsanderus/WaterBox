#pragma once
#include "WaterBox.h"
#include "GameMaterial.h"
#include <unordered_map>

struct GameMaterial;

class GameConfigManager
{
public:
	static GameConfigManager& GetGameConfigManager(){
		static GameConfigManager manager;
		return manager;
	}

	const std::vector <GameMaterial>& GetMaterials ();
	int GetMaterialIndex(std::string name);
	const GameMaterial& GetMaterial(int ID);
	void LoadMaterials();

protected:
	bool AreMaterialsLoaded = false;
	std::vector<GameMaterial> Materials;
	std::unordered_map <std::string, int> MaterialsLookupMap;

	const std::string MaterialsFileName = "Materials.json";
};