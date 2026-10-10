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

	std::vector <GameMaterial>& GetMaterials ();
	std::vector <MaterialCategory>& GetCategories();

	int GetMaterialIndex(std::string Name);
	inline GameMaterial& GetMaterial(int ID);
	int GetCategoryIndex(std::string Name);
	MaterialCategory& GetCategory(int ID);

	void LoadConfig();
	bool LoadMaterials(std::string FileName);

	std::string GetString(std::string key);

private:
	bool AreMaterialsLoaded = false;

	std::vector<GameMaterial> Materials;
	std::unordered_map <std::string, int> MaterialsLookupMap;

	std::vector<MaterialCategory> Categories;
	std::unordered_map <std::string, int> CategoriesLookupMap;

	std::unordered_map <std::string, std::string> Localization;

	void LoadLocalization(std::string FileName);

	template <typename T>
	int GetArrayIndex(const std::string& ID, std::vector <T>& elements, std::unordered_map <std::string, int>& NamesMap);

	inline StateCategoryEnum ParseStateCategory(const std::string& stateStr);

	GameMaterial DefaultMaterial = { .MinColor = {0,0,0}, .MaxColor = {255,255,255}, .KeepColorProportions = false };
	MaterialCategory DefaultCategory = { .Name = "NO_CATEGORY", .CanBeShown = true, .Color = {255,255,0,255} };

	std::string MaterialsFileName = "Materials.json";



};





inline GameMaterial& GameConfigManager::GetMaterial(int ID)
{
#ifndef NDEBUG
	if (!AreMaterialsLoaded)
	{
		LOG_FATAL("Materials are not loaded yet");

		return DefaultMaterial;
	}

	if (ID < Materials.size())
		return Materials[ID];
	else
		return DefaultMaterial;
#else
	return Materials[ID];
#endif
}