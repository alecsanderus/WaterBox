#include "GameSimulation.h"
#include "GameConfigManager.h"
#include <random>

PixelColor GetRandomColor(const GameMaterial& material)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    auto [minR, maxR] = std::minmax(material.MinColor.R, material.MaxColor.R);
    auto [minG, maxG] = std::minmax(material.MinColor.G, material.MaxColor.G);
    auto [minB, maxB] = std::minmax(material.MinColor.B, material.MaxColor.B);

    std::uniform_int_distribution<int> distR(minR, maxR);
    std::uniform_int_distribution<int> distG(minG, maxG);
    std::uniform_int_distribution<int> distB(minB, maxB);

    return PixelColor{
        static_cast<uint8_t>(distR(gen)),
        static_cast<uint8_t>(distG(gen)),
        static_cast<uint8_t>(distB(gen))
    };
}

const std::vector<std::vector<GameCell>>& GameSimulation::GetGameField()
{
    return GameField;
}


void GameCell::Create(int ID)
{
    Color = GetRandomColor(GameSimulation::Config.GetMaterial (ID));
}
