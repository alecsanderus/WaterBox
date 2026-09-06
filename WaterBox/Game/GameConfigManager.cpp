#include "GameConfigManager.h"
#include "GameSimulation.h"
#include "SDL3/SDL.h"
#include "nlohmann/json.hpp"



const std::vector<GameMaterial>& GameConfigManager::GetMaterials()
{
	if (!AreMaterialsLoaded)
		LoadMaterials();
	return Materials;
}

int GameConfigManager::GetMaterialIndex(std::string name)
{
    auto ptr = MaterialsLookupMap.find(name);
    if (ptr != MaterialsLookupMap.end())
        return ptr->second;
    else
        return 0;
}

const GameMaterial& GameConfigManager::GetMaterial(int ID)
{
	if (!AreMaterialsLoaded)
		LoadMaterials();

    if (!AreMaterialsLoaded)
    {
        LOG_FATAL("Materials are not loaded yet");
        return { .MinColor = {0,0,0}, .MaxColor = {255,255,255}, .KeepColorProportions = false };
    }

    if (ID < Materials.size())
        return Materials[ID];
    else
        return { .MinColor = {0,0,0}, .MaxColor = {255,255,255}, .KeepColorProportions = false };
}

void GameConfigManager::LoadMaterials()
{
    //const char* basePath = SDL_GetBasePath();
    //if (!basePath) {
    //    LOG_ERROR("Cant get path to materials");
    //    return;
    //}

    //std::string fullPath = std::string(basePath) + MaterialsFileName;


    //size_t fileSize = 0;
    //char* fileData = (char*)SDL_LoadFile(fullPath.c_str(), &fileSize);

    size_t fileSize = 0;
    char* fileData = (char*)SDL_LoadFile((GlobalPathPrefix + MaterialsFileName).c_str(), &fileSize);

    if (!fileData) {
        std::string error = "Cant read file, SDL3 error: " + std::string (SDL_GetError());
        LOG_ERROR(error);
        return;
    }

    try {
        auto json = nlohmann::json::parse(fileData);

        SDL_free(fileData);
       
        if (json.contains("Materials") && json["Materials"].is_array()) {

            Materials.clear();
            MaterialsLookupMap.clear();
            Materials.reserve(json["Materials"].size());

            for (const auto& item : json["Materials"]) {
                GameMaterial TecMat;

                TecMat.Name = item["name"].get<std::string>();

                TecMat.KeepColorProportions = item.value <bool>("keep_color_proportions", true);

                TecMat.MaxColor.R = item.value <int>("color_Max_R", 0);
                TecMat.MaxColor.G = item.value <int>("color_Max_G", 0);
                TecMat.MaxColor.B = item.value <int>("color_Max_B", 0);

                TecMat.MinColor.R = item.value <int>("color_Min_R", 0);
                TecMat.MinColor.G = item.value <int>("color_Min_G", 0);
                TecMat.MinColor.B = item.value <int>("color_Min_B", 0);
                
                MaterialsLookupMap[TecMat.Name] = Materials.size();
                Materials.push_back(TecMat);
            }
        }
        AreMaterialsLoaded = true;
        LOG_INFO("Materials loaded");
    }
    catch (const nlohmann::json::parse_error& e) {
        std::string err = "Cant parse JSON: " + std::string(e.what());
        LOG_ERROR(err);
        SDL_free(fileData);
        return;
    }
}
