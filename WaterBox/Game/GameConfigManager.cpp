#include "GameConfigManager.h"
#include "GameSimulation.h"
#include "SDL3/SDL.h"
#include "nlohmann/json.hpp"



const std::vector<GameMaterial>& GameConfigManager::GetMaterials()
{
    if (!AreMaterialsLoaded)
        LoadConfig();
	return Materials;
}

const std::vector<MaterialCategory>& GameConfigManager::GetCategories()
{
    if (!AreMaterialsLoaded)
        LoadConfig();
    return Categories;
}

int GameConfigManager::GetMaterialIndex(std::string Name)
{
    auto ptr = MaterialsLookupMap.find(Name);
    if (ptr != MaterialsLookupMap.end())
        return ptr->second;
    else
        return 0;
}

const GameMaterial& GameConfigManager::GetMaterial(int ID)
{
    if (!AreMaterialsLoaded)
        LoadConfig();

    if (!AreMaterialsLoaded)
    {
        LOG_FATAL("Materials are not loaded yet");
       
        return DefaultMaterial;
    }

    if (ID < Materials.size())
        return Materials[ID];
    else
        return DefaultMaterial;
}

int GameConfigManager::GetCategoryIndex(std::string Name)
{
    auto ptr = CategoriesLookupMap.find(Name);
    if (ptr != CategoriesLookupMap.end())
        return ptr->second;
    else
        return 0;
}

const MaterialCategory& GameConfigManager::GetCategory(int ID)
{
    if (!AreMaterialsLoaded)
        LoadConfig();

    if (!AreMaterialsLoaded)
    {
        LOG_FATAL("Categories are not loaded yet");

        return DefaultCategory;
    }

    if (ID < Categories.size())
        return Categories[ID];
    else
        return DefaultCategory;
}

void GameConfigManager::LoadConfig()
{
    bool OK = LoadMaterials(MaterialsFileName);
    LoadLocalization("ru");

    AreMaterialsLoaded = OK;

}

bool GameConfigManager::LoadMaterials(std::string FileName)
{  
    size_t fileSize = 0;
    char* fileData = (char*)SDL_LoadFile((GlobalPathPrefix + FileName).c_str(), &fileSize);

    if (!fileData) {
        std::string error = "Cant read file name:  " + FileName + "  , SDL3 error : " + std::string(SDL_GetError());
        LOG_ERROR(error);
        return false;
    }

    try {
        auto json = nlohmann::json::parse(fileData);

        SDL_free(fileData);
       
        if (json.contains("Materials") && json["Materials"].is_array()) {

            Materials.reserve(Materials.size() + json["Materials"].size());

            for (const auto& item : json["Materials"]) {

                auto Name =  item["name"].get<std::string>();
                int ID = GetArrayIndex(Name, Materials, MaterialsLookupMap);
                GameMaterial& TecMat = Materials [ID];

                TecMat.Name = Name;  
                TecMat.ID = ID;

                TecMat.CategoryID = GetArrayIndex(item["category_key"].get <std::string>(), Categories, CategoriesLookupMap);

                TecMat.ShowPriority = item.value <int>("show_priority", 0);
                TecMat.CanBeShown = item.value <bool>("can_be_shown", true);
                TecMat.KeepColorProportions = item.value <bool>("keep_color_proportions", true);

                TecMat.MaxColor.r = item.value <int>("color_Max_R", 0);
                TecMat.MaxColor.g = item.value <int>("color_Max_G", 0);
                TecMat.MaxColor.b = item.value <int>("color_Max_B", 0);

                TecMat.MinColor.r = item.value <int>("color_Min_R", 0);
                TecMat.MinColor.g = item.value <int>("color_Min_G", 0);
                TecMat.MinColor.b = item.value <int>("color_Min_B", 0);
            }
        }
        if (json.contains("Categories") && json["Categories"].is_array()) {

            Categories.reserve(Categories.size() + json["Categories"].size());

            for (const auto& item : json["Categories"]) {

                auto Name = item["name"].get<std::string>();
                int ID = GetArrayIndex(Name, Categories, CategoriesLookupMap);
                MaterialCategory& TecCat = Categories[GetArrayIndex(Name, Categories, CategoriesLookupMap)];

                TecCat.Name = Name;
                TecCat.ID = ID;


                TecCat.CanBeShown = item.value <bool>("can_be_shown", true);

                TecCat.Color.r = item.value <int>("color_R", 0);
                TecCat.Color.g = item.value <int>("color_G", 0);
                TecCat.Color.b = item.value <int>("color_B", 0);
            }
        }

        LOG_INFO("Materials loaded from" + FileName);
    }
    catch (const nlohmann::json::parse_error& e) {
        std::string err = "Cant parse  " + FileName + "  JSON: " + std::string(e.what());
        LOG_ERROR(err);
        SDL_free(fileData);
        return false;
    }

    return true;
}

std::string GameConfigManager::GetString(std::string key)
{
    auto it = Localization.find (key);
    if (it != Localization.end())
        return it->second;
    else
        return key;
}



void GameConfigManager::LoadLocalization(std::string FileName)
{
    size_t fileSize = 0;
    std::string FullFileName = GlobalPathPrefix + FileName + ".json";

    char* fileData = (char*)SDL_LoadFile(FullFileName.c_str(), &fileSize);

    if (!fileData) {
        std::string error = "Cant read file name:  " + FullFileName + "  , SDL3 error : " + std::string(SDL_GetError());
        LOG_ERROR(error);
        return;
    }

    try {
        auto json = nlohmann::json::parse(fileData);

        SDL_free(fileData);

        if (json.is_object()) {

            for (const auto& [key, value] : json.items()) {

                if (value.is_string()) 
                    Localization[key] = value.get<std::string>();
               
                else                  
                    Localization[key] = value.dump();
                
            }
        }
      
        LOG_INFO("Localization loaded from" + FullFileName);
    }
    catch (const nlohmann::json::parse_error& e) {
        std::string err = "Cant parse  " + FullFileName + "  JSON: " + std::string(e.what());
        LOG_ERROR(err);
        SDL_free(fileData);
        return;
    }
}

template <typename T>
int GameConfigManager::GetArrayIndex(const std::string& ID, std::vector <T>& elements, std::unordered_map <std::string, int>& NamesMap) {

    auto it = NamesMap.find(ID);
    if (it != NamesMap.end()) {
        return it->second;
    }

    T placeholder;
    placeholder.ID = elements.size();
    placeholder.Name = ID; 
    placeholder.IsLoaded = false;

    elements.push_back(placeholder);

    int newIndex = elements.size() - 1;
    NamesMap[ID] = newIndex;

    return newIndex;
}