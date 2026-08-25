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
    
    if (material.KeepColorProportions)
    {     
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);
        float factor = dist(gen);

        uint8_t finalR = static_cast<uint8_t>(minR + factor * (maxR - minR));
        uint8_t finalG = static_cast<uint8_t>(minG + factor * (maxG - minG));
        uint8_t finalB = static_cast<uint8_t>(minB + factor * (maxB - minB));

        return PixelColor{finalR, finalG, finalB };
    }
    else
    {
        std::uniform_int_distribution<int> distR(minR, maxR);
        std::uniform_int_distribution<int> distG(minG, maxG);
        std::uniform_int_distribution<int> distB(minB, maxB);

        return PixelColor{
            static_cast<uint8_t>(distR(gen)),
            static_cast<uint8_t>(distG(gen)),
            static_cast<uint8_t>(distB(gen))
        };
    }
}


void GameCell::Create(int ID)
{
    Color = GetRandomColor(GameConfigManager::GetGameConfigManager().GetMaterial (ID));
    Active = true;
}

void GameCell::Destroy()
{
    Color = { 0,0,0 };
    Active = false;
}


const Vector2D <GameCell>& GameSimulation::GetGameField() const
{
    return GameField;
}

std::pair<size_t, size_t> GameSimulation::GetGameFieldSize() const
{
    return { GameSizeX, GameSizeY };
}

void GameSimulation::SetGameFieldSize(size_t x, size_t y)
{
    GameSizeX = x;
    GameSizeY = y;
    GameField.resize(GameSizeX, GameSizeY);



    PixelColor green = { 0, 180, 0 };
    PixelColor brown = { 100, 50, 20 };
    PixelColor star = { 255, 215, 0 };

    // 1. Рисуем крону (три треугольных яруса)
    // Перебираем три яруса сверху вниз
    for (int tier = 0; tier < 3; ++tier) {
        int startY = 20 + tier * 15; // Начало яруса по вертикали
        int height = 20;             // Высота каждого яруса

        for (int y = 0; y < height; ++y) {
            int currentY = startY + y;
            // Ширина яруса увеличивается книзу
            int width = 5 + (tier * 8) + y;

            // Рисуем горизонтальную линию для текущего ряда кроны
            for (int x = 50 - width; x <= 50 + width; ++x) {
                GameField(x, currentY).Color = green;
            }
        }
    }

    // 2. Рисуем ствол (коричневый прямоугольник снизу)
    for (int y = 65; y < 85; ++y) {
        for (int x = 46; x <= 54; ++x) {
            GameField(x, y).Color = brown;
        }
    }

    // 3. Рисуем звезду на верхушке (небольшой крестик)
    int cx = 50;
    int cy = 14;

    // Центральное ядро звезды (квадрат 3x3)
    for (int y = cy - 1; y <= cy + 1; ++y) {
        for (int x = cx - 1; x <= cx + 1; ++x) {
            GameField(x, y).Color = star;
        }
    }

    // Длинные главные лучи (крест: вверх, вниз, влево, вправо)
    for (int i = 2; i <= 6; ++i) {
        GameField(cx, cy - i).Color = star; // Вверх
        GameField(cx, cy + i).Color = star; // Вниз
        GameField(cx - i, cy).Color = star; // Влево
        GameField(cx + i, cy).Color = star; // Вправо
    }

    // Дополнительные боковые пиксели для утолщения главных лучей у основания
    GameField(cx - 1, cy - 2).Color = star;
    GameField(cx + 1, cy - 2).Color = star;
    GameField(cx - 1, cy + 2).Color = star;
    GameField(cx + 1, cy + 2).Color = star;
    GameField(cx - 2, cy - 1).Color = star;
    GameField(cx - 2, cy + 1).Color = star;
    GameField(cx + 2, cy - 1).Color = star;
    GameField(cx + 2, cy + 1).Color = star;

    // Диагональные лучи (короче главных для красивой формы)
    for (int i = 2; i <= 4; ++i) {
        GameField(cx - i, cy - i).Color = star; // Северо-запад
        GameField(cx + i, cy - i).Color = star; // Северо-восток
        GameField(cx - i, cy + i).Color = star; // Юго-запад
        GameField(cx + i, cy + i).Color = star; // Юго-восток
    }
}



