#include "GameSimulation.h"
#include "GameConfigManager.h"


void GameCell::Create(int ID)
{
    auto& mat = GameConfigManager::GetGameConfigManager().GetMaterial(ID);
    Color = ColorStr::GetRandomColor(mat.MinColor, mat.MaxColor, mat.KeepColorProportions);
    Active = true;
    OriginalMaterialID = ID;
    temp = mat.InitialTemperature;

    VelX = 0;
    VelY = 0;
}

void GameCell::Destroy()
{
    Color = { 0,0,0,255 };
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



    ColorStr green = { 0, 180, 0 };
    ColorStr brown = { 100, 50, 20 };
    ColorStr star = { 255, 215, 0 };

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

void GameSimulation::SimulationTick()
{
    TecTick++;

    ProcessGravity();

    ProcessDefaultPhysic();
   

}

void GameSimulation::ProcessGravity()
{
    auto& config = GameConfigManager::GetGameConfigManager();

    for (auto& i : GameField.GetVector())
    {
        if (i.Active && i.Updating != 1)
        {
            i.Updating = 1;

            auto cat = config.GetMaterial(i.OriginalMaterialID).StateCategory;
            if (cat == StateCategoryEnum::liquid || cat == StateCategoryEnum::gas || cat == StateCategoryEnum::solid)
                i.VelY += (i.VelY < 0.05f) ? 0.4f : 0.1f;
        }
    }    
}

void GameSimulation::ProcessDefaultPhysic()
{
    auto& config = GameConfigManager::GetGameConfigManager();

    for (int y = GameSizeY -1; y >= 0 ; y--)
    {
        for (int x = 0; x < GameSizeX; x++)
        {
            auto& tec = GameField(x, y);
            if (!tec.Active || tec.Updating == 2) continue;

            tec.Updating = 2;

            auto& mat = config.GetMaterial(tec.OriginalMaterialID);

            switch (mat.StateCategory)
            {
            case StateCategoryEnum::solid:
            {               
                float vx = tec.VelX, vy = tec.VelY;
                int tecX = x, tecY = y;
                while (true)
                {
                    if (vy <= 0) break;
                    if (vy < 1) vy = vy > RandomFloat(x, y, TecTick);
                    if (vy <= 0) break;

                    if (tecY < GameSizeY - 1 && !GameField(tecX, tecY + 1).Active)
                    {
                       

                    }
                    else
                        break;
                    vy--;
                    tecY++;
                }
                std::swap(GameField(x, y), GameField(tecX, tecY));
                break;
            }
            default:
                break;
            }

        }
    }
}



inline uint32_t GameSimulation::Deterministic_hash(uint32_t x, uint32_t y, uint32_t tick) {
   
    uint32_t state = x * 73856093U ^ y * 19349663U ^ tick * 83492791U;

    state ^= state >> 16;
    state *= 0x85ebca6b;
    state ^= state >> 13;
    state *= 0xc2b2ae35;
    state ^= state >> 16;

    return state;
}

inline float GameSimulation::RandomFloat(uint32_t x, uint32_t y, uint32_t tick)
{
    return (float)Deterministic_hash(x, y, tick) / (float)UINT32_MAX;
}
