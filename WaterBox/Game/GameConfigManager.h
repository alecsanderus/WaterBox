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
	const std::vector <MaterialCategory>& GetCategories();

	int GetMaterialIndex(std::string Name);
	const GameMaterial& GetMaterial(int ID);

	void LoadConfig();
	bool LoadMaterials(std::string FileName);

private:
	bool AreMaterialsLoaded = false;

	std::vector<GameMaterial> Materials;
	std::unordered_map <std::string, int> MaterialsLookupMap;

	std::vector<MaterialCategory> Categories;
	std::unordered_map <std::string, int> CategoriesLookupMap;

	template <typename T>
	int GetArrayIndex(const std::string& ID, std::vector <T>& elements, std::unordered_map <std::string, int>& NamesMap);

	const std::string MaterialsFileName = "Materials.json";
};