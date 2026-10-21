#pragma once
#include "WaterBox.h"
#include "GameMaterial.h"
#include <unordered_map>
#include "MapContainer.h"

struct GameMaterial;
struct SDL_Texture;

class GameConfigManager
{
public:
	static GameConfigManager& GetGameConfigManager(){
		static GameConfigManager manager;
		return manager;
	}

	struct TextureStruct
	{
		float x = 0, y = 0;
		SDL_Texture* texture = nullptr;
	};

	MapContainer <GameMaterial> Materials;
	MapContainer <MaterialCategory> Categories;
	MapContainer <TextureStruct> Images;


	void LoadConfig();
	bool LoadMaterials(std::string FilePath);
	void LoadLocalization(std::string FilePath);
	void LoadMod(std::string FilePath);
	void LoadScript(std::string FilePath);
	void LoadImage(std::string FilePath, std::string ImageName);
	std::string GetString(std::string key);

	std::string CurrentLanguage = "ru";
	std::string DefaultDefaultLanguage = "en";

	void SetRenderManager(class RenderManager* manager);


private:
	bool AreMaterialsLoaded = false;
	class RenderManager* renderer;
	

	std::unordered_map <std::string, std::string> Localization;

	

	template <typename T>
	std::pair <T&, int> GetArrayIndex(const std::string& ID, MapContainer <T>& elements);

	inline StateCategoryEnum ParseStateCategory(const std::string& stateStr);

	GameMaterial DefaultMaterial = { .MinColor = {0,0,0}, .MaxColor = {255,255,255}, .KeepColorProportions = false };
	MaterialCategory DefaultCategory = { .Name = "NO_CATEGORY", .CanBeShown = true, .Color = {255,255,0,255} };

	std::string MaterialsFileName = "Materials.json";



};