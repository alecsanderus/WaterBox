#include "GameConfigManager.h"
#include "GameSimulation.h"
#include "SDL3/SDL.h"
#include <SDL3_image/SDL_image.h>
#include "RenderManager.h"

#include "nlohmann/json.hpp"



void GameConfigManager::LoadConfig()
{
    LoadMod(GlobalPathPrefix);

  
    AreMaterialsLoaded = true;

}

bool GameConfigManager::LoadMaterials(std::string FilePath)
{  
    size_t fileSize = 0;
    char* fileData = (char*)SDL_LoadFile(FilePath.c_str(), &fileSize);

    if (!fileData) {
        std::string error = "Cant read file name:  " + FilePath + "  , SDL3 error : " + std::string(SDL_GetError());
        LOG_ERROR(error);
        return false;
    }

    try {
        auto json = nlohmann::json::parse(fileData);

        SDL_free(fileData);
       
        if (json.contains("Materials") && json["Materials"].is_array()) {

            Materials.Elements.reserve(Materials.Elements.size() + json["Materials"].size());

            for (const auto& item : json["Materials"]) {

                auto Name =  item["name"].get<std::string>();
                auto [TecMat, ID] = GetArrayIndex(Name, Materials);
               

                TecMat.CategoryID = GetArrayIndex(item["category_key"].get <std::string>(), Categories).second;

                TecMat.ShowPriority = item.value <int>("show_priority", 0);
                TecMat.CanBeShown = item.value <bool>("can_be_shown", true);


                TecMat.KeepColorProportions = item.value <bool>("keep_color_proportions", true);
                TecMat.MaxColor.r = item.value <int>("color_Max_R", 0);
                TecMat.MaxColor.g = item.value <int>("color_Max_G", 0);
                TecMat.MaxColor.b = item.value <int>("color_Max_B", 0);
                TecMat.MinColor.r = item.value <int>("color_Min_R", 0);
                TecMat.MinColor.g = item.value <int>("color_Min_G", 0);
                TecMat.MinColor.b = item.value <int>("color_Min_B", 0);


                std::string StateStr = item.value <std::string> ("state_category", std::string ("NO_CATEGORY_IN_FILE"));
                TecMat.StateCategory = ParseStateCategory(StateStr);

                TecMat.InitialTemperature = item.value<float>("initial_temperature", 20.0f);
                TecMat.Density = item.value<float>("density", 1000.0f);
                TecMat.ThermalConductivity = item.value<float>("thermal_conductivity", 1.0f);
                TecMat.SpecificHeatCapacity = item.value<float>("specific_heat_capacity", 1000.0f);

                TecMat.Bounciness = item.value<float>("bounciness", 0.1f);
                TecMat.ScatterFactor = item.value<float>("catter_factor", 0.05f);
                TecMat.SurfaceFriction = item.value<float>("surface_friction", 2.0f);
                TecMat.CanSlide = item.value <bool>("can_slide", false);



                TecMat.IsLoaded = true;
            }
        }
        if (json.contains("Categories") && json["Categories"].is_array()) {

            Categories.Elements.reserve(Categories.Elements.size() + json["Categories"].size());

            for (const auto& item : json["Categories"]) {

                auto Name = item["name"].get<std::string>();
                auto [TecCat, ID] = GetArrayIndex(Name, Categories);
              
                TecCat.CanBeShown = item.value <bool>("can_be_shown", true);

                TecCat.Color.r = item.value <int>("color_R", 0);
                TecCat.Color.g = item.value <int>("color_G", 0);
                TecCat.Color.b = item.value <int>("color_B", 0);
            }
        }

        LOG_INFO("Materials loaded from " + FilePath);
    }
    catch (const nlohmann::json::parse_error& e) {
        std::string err = "Cant parse  " + FilePath + "  JSON: " + std::string(e.what());
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

void GameConfigManager::SetRenderManager(RenderManager* manager)
{renderer = manager;}



void GameConfigManager::LoadLocalization(std::string FilePath)
{
    size_t fileSize = 0;

    char* fileData = (char*)SDL_LoadFile(FilePath.c_str(), &fileSize);

    if (!fileData) {
        std::string error = "Cant read file name:  " + FilePath + "  , SDL3 error : " + std::string(SDL_GetError());
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
      
        LOG_INFO("Localization loaded from " + FilePath);
    }
    catch (const nlohmann::json::parse_error& e) {
        std::string err = "Cant parse  " + FilePath + "  JSON: " + std::string(e.what());
        LOG_ERROR(err);
        SDL_free(fileData);
        return;
    }
}

namespace
{
    std::string SelectLanguage(const nlohmann::json& root, std::string CurrentLang, std::string DefaultLang)
    {
        if (!root.contains("languages") || !root["languages"].is_array() || root["languages"].empty()) 
            return "";
        

        std::vector<std::string> languages;
        for (const auto& item : root["languages"])
            if (item.is_string()) 
                languages.push_back(item.get<std::string>());        

        if (languages.empty()) return "";


        auto findValue = [&languages](const std::string& target) -> bool {
            return std::find(languages.begin(), languages.end(), target) != languages.end();
            };


        if (findValue(CurrentLang + ".json")) {
            return CurrentLang + ".json";
        }      
        if (findValue(DefaultLang + ".json")) {          
            return DefaultLang + ".json";
        }
          

        if (root.contains("default_language") && root["default_language"].is_string()) {
            std::string jsonDefault = root["default_language"].get<std::string>();

            if (findValue(jsonDefault)) 
                return jsonDefault;
            
            if (!jsonDefault.ends_with(".json") && findValue(jsonDefault + ".json"))
                return jsonDefault + ".json";
            
        }

        return languages[0];
    }
}

void GameConfigManager::LoadMod(std::string FilePath)
{
    size_t fileSize = 0;
    std::string FullFileName = FilePath + "AssetList.json";

    char* fileData = (char*)SDL_LoadFile(FullFileName.c_str(), &fileSize);

    if (!fileData) {
        std::string error = "Cant read file name:  " + FullFileName + "  , SDL3 error : " + std::string(SDL_GetError());
        LOG_ERROR(error);
        return;
    }

    try {
        auto json = nlohmann::json::parse(fileData);

        SDL_free(fileData);

        LOG_INFO("Start loading mod from " + FullFileName);

        if (json.contains("materials") && json["materials"].is_array())
            for (const auto& value : json["materials"])
                if (value.is_string())
                    LoadMaterials(FilePath + std::string(value));

        auto SelectedFile = SelectLanguage(json, CurrentLanguage, DefaultDefaultLanguage);
        if (SelectedFile != "")
            LoadLocalization(FilePath + SelectedFile);

        if (json.contains("scripts") && json["scripts"].is_array())
            for (const auto& value : json["scripts"])
                if (value.is_string())
                    LoadScript(FilePath + std::string(value));

        if (json.contains("images") && json["images"].is_array())
        {
            for (const auto& value : json["images"])
                if (value.is_string())
                    LoadImage(FilePath + std::string(value), value);

            LOG_INFO(std::to_string (json["images"].size()) + std::string(" texture(s) loaded"));
        }


        LOG_INFO("Mod loaded from " + FullFileName);
    }
    catch (const nlohmann::json::parse_error& e) {
        std::string err = "Cant parse  " + FullFileName + "  JSON: " + std::string(e.what());
        LOG_ERROR(err);
        SDL_free(fileData);
        return;
    }
}

void GameConfigManager::LoadScript(std::string FilePath)
{}

void GameConfigManager::LoadImage(std::string FilePath, std::string ImageName)
{
    auto rend = renderer->GetSDLRenderer();
    auto tex = IMG_LoadTexture(rend, FilePath.c_str());

    if (!tex) {
        LOG_ERROR("LoadImage error, FilePath:" + FilePath + "\n" +  SDL_GetError());       
        return;
    }

    auto [textrPointer, index] = Images.ReserveAndGetElement(ImageName);
    textrPointer.texture = tex;

    SDL_GetTextureSize(tex, &textrPointer.x, &textrPointer.y);

    SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
}

template <typename T>
std::pair <T&, int> GameConfigManager::GetArrayIndex(const std::string& ID, MapContainer <T>& elements) {

    auto par = elements.ReserveAndGetElement (ID);  
   
    par.first.ID = par.second;
    par.first.Name = ID;
    par.first.IsLoaded = false;

    return par;
}

StateCategoryEnum GameConfigManager::ParseStateCategory(const std::string& stateStr)
{
    if (stateStr == "static")   return StateCategoryEnum::unmovable;
    if (stateStr == "solid")    return StateCategoryEnum::solid; 
    if (stateStr == "liquid")   return StateCategoryEnum::liquid;
    if (stateStr == "gas")      return StateCategoryEnum::gas;

    LOG_ERROR("Incorrect StateCategory  " + stateStr);

    return StateCategoryEnum::unmovable; 
};


