#include "GameSimulation.h"
#include "GameConfigManager.h"


void GameCell::Create(const int ID)
{
    const auto& mat = GameConfigManager::GetGameConfigManager().Materials.GetElement(ID);
    Color = ColorStr::GetRandomColor(mat.MinColor, mat.MaxColor, mat.KeepColorProportions);
    Active = true;
    OriginalMaterialID = ID;
    temp = mat.InitialTemperature;

    VelX = 0.f;
    VelY = 0.f;
    Pressure = 0.f;
}

void GameCell::Destroy()
{
    Color = { 0,0,0,255 };
    Active = false;
    Pressure = 0;
}


const Vector2D <GameCell>& GameSimulation::GetGameField() const
{
    return GameField;
}

std::pair<size_t, size_t> GameSimulation::GetGameFieldSize() const
{
    return { GameSizeX, GameSizeY };
}

void GameSimulation::SetGameFieldSize(const int x, const int y)
{
    GameSizeX = x;
    GameSizeY = y;
    GameField.resize(GameSizeX, GameSizeY);
    /* тут была ёлка



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
    }*/
}

void GameSimulation::SimulationTick()
{
    TecTick++;

    ProcessGravity();

    ProcessDefaultPhysic();

    ProcessLiquidPhysic();
   
    NormalizeVelocity();
}

void GameSimulation::ProcessGravity()
{
    auto& config = GameConfigManager::GetGameConfigManager();

    for (auto& i : GameField.GetVector())
    {
        if (i.Active && i.Updating != 1)
        {
            i.Updating = 1;

            auto cat = config.Materials.GetElement(i.OriginalMaterialID).StateCategory;
            if (cat == StateCategoryEnum::liquid || cat == StateCategoryEnum::gas || cat == StateCategoryEnum::solid)
                i.VelY += 0.1f;
        }
    }    
}

void GameSimulation::ProcessDefaultPhysic()
{
    auto& config = GameConfigManager::GetGameConfigManager();

   
    bool reverseX = (TecTick & 1);
    int startX = reverseX ? GameSizeX - 1 : 0;
    int endX = reverseX ? -1 : GameSizeX;
    int stepX = reverseX ? -1 : 1;


    for (int y = GameSizeY -1; y >= 0 ; y--)
    {
        for (int x = startX; x != endX; x += stepX)
        {
            auto& tec = GameField(x, y);
            if (!tec.Active || tec.Updating == 2) continue;

            tec.Updating = 2;

            auto& mat = config.Materials.GetElement(tec.OriginalMaterialID);

            if (mat.StateCategory == StateCategoryEnum::unmovable) continue;

            int StepsX = static_cast<int>(tec.VelX);
            int StepsY = static_cast<int>(tec.VelY);

            StepsX += (RandomFloat(x, y, TecTick) < abs(tec.VelX - static_cast<float> (StepsX))) * ((tec.VelX > 0) ? 1 : -1);
            StepsY += (RandomFloat(x, y, TecTick) < abs(tec.VelY - static_cast<float> (StepsY))) * ((tec.VelY > 0) ? 1 : -1);

            if (StepsX == 0 && StepsY == 0) continue;

            int tecX = x, tecY = y;

            int AbsStepsX = std::abs(StepsX);
            int AbsStepsY = std::abs(StepsY);
            int SignX = (StepsX > 0) ? 1 : -1;
            int SignY = (StepsY > 0) ? 1 : -1;


            int MaxSteps = std::max(AbsStepsX, AbsStepsY);
            float AccumX = 0.0f;
            float AccumY = 0.0f;
            float RatioX = (MaxSteps > 0) ? static_cast<float>(AbsStepsX) / static_cast<float> (MaxSteps) : 0.0f;
            float RatioY = (MaxSteps > 0) ? static_cast<float>(AbsStepsY) / static_cast<float> (MaxSteps) : 0.0f;


            for (int step = 0; step < MaxSteps; step++)
            {
                int NextX = tecX;
                int NextY = tecY;

                AccumX += RatioX;
                AccumY += RatioY;

                if (AccumX >= 1.0f) {
                    NextX += SignX;
                    AccumX -= 1.0f;
                }
                if (AccumY >= 1.0f) {
                    NextY += SignY;
                    AccumY -= 1.0f;
                }


                if (NextX < 0 || NextX >= GameSizeX || NextY < 0 || NextY >= GameSizeY)
                {
                    auto& NewTec = GameField(tecX, tecY);
                    if (NextX < 0 || NextX >= GameSizeX) NewTec.VelX = 0.0f;
                    if (NextY < 0 || NextY >= GameSizeY) NewTec.VelY = 0.0f;
                    break;
                }


                auto& target = GameField(NextX, NextY);
                if (!target.Active)
                {
                    std::swap(GameField(tecX, tecY), target);
                    tecX = NextX;
                    tecY = NextY;
                    continue;
                }

                uint8_t Direction = 0;
                if (NextX != tecX && NextY == tecY) {
                    Direction = (SignX > 0) ? 1 : 3;
                }
                else if (NextY != tecY && NextX == tecX) {
                    Direction = (SignY > 0) ? 0 : 2;
                }
                else {
                    Direction = (AbsStepsY > AbsStepsX) ? ((SignY > 0) ? 0 : 2) : ((SignX > 0) ? 1 : 3);
                }

                float stopping = DoLiteCollision(GameField(tecX, tecY), target, Direction, tecX, tecY, NextX, NextY);
                MaxSteps *= static_cast<int> (stopping);
                                            
                if (stopping > 0)
                {
                    std::swap(GameField(tecX, tecY), GameField(NextX, NextY));
                    tecX = NextX;
                    tecY = NextY;
                    continue;
                }
                break;
            }


        }
    }
}

void GameSimulation::ProcessLiquidPhysic() {
    auto& config = GameConfigManager::GetGameConfigManager();


    bool reverse = (TecTick & 1);
    int step = reverse ? -1 : 1;

    int startX = reverse ? GameSizeX - 1 : 0;
    int endX = reverse ? 0 : GameSizeX - 1;
    int startY = reverse ? GameSizeY - 2 : 0;
    int endY = reverse ? -1 : GameSizeY - 1;



    for (int y = 0; y < GameSizeY; y++)
    {
        for (int x = startX; x != endX; x += step) {
            auto& tec = GameField(x, y);
            if (!tec.Active || tec.Updating == 4) continue;

            tec.Updating = 4;

            auto& mat = config.Materials.GetElement(tec.OriginalMaterialID);

            if (mat.StateCategory != StateCategoryEnum::liquid) continue;

            GameCell& tecB = GameField(x + step, y);
            auto& matB = config.Materials.GetElement(tecB.OriginalMaterialID);

            if (matB.StateCategory != StateCategoryEnum::liquid) continue;

            float diff = tec.Pressure - tecB.Pressure;
            diff *= static_cast<float> (step);

            tec.Pressure = std::max (tecB.Pressure, tec.Pressure);
            tecB.Pressure = std::max (tecB.Pressure, tec.Pressure);

           // tec.VelX += diff * 0.001f;
          //  tecB.VelX += diff * 0.001f;
        }
    }


    for (int y = startY; y != endY; y += step) {
        for (int x = 0; x < GameSizeX; x ++) {
            auto& tec = GameField(x, y);
            if (!tec.Active || tec.Updating == 5) continue;

            tec.Updating = 5;

            auto& mat = config.Materials.GetElement(tec.OriginalMaterialID);

            if (mat.StateCategory != StateCategoryEnum::liquid) continue;

            GameCell& tecB = GameField(x, y + 1);
            auto& matB = config.Materials.GetElement(tecB.OriginalMaterialID);

            if (matB.StateCategory != StateCategoryEnum::liquid || !tecB.Active) continue;

            float TargetPressure = tec.Pressure + mat.Density;

            float diff = TargetPressure - tecB.Pressure;

            if (diff > 0)
            {
                tecB.Pressure = TargetPressure;
            }
            else
                tec.Pressure = tecB.Pressure - mat.Density;



         //   tec.VelY += diff;
         //   tecB.VelY += diff;
        }
    }
}


void GameSimulation::DoCollision(GameCell& a, GameCell& b, const uint8_t direction, int x, int y, const float size)
{

    auto& config = GameConfigManager::GetGameConfigManager();
    auto& AMat = config.Materials.GetElement(a.OriginalMaterialID);
    auto& BMat = config.Materials.GetElement(b.OriginalMaterialID);

    float DensSumm = AMat.Density + BMat.Density;
    if (AMat.Density <= 0.f || BMat.Density <= 0.f) return;

    float nx = 0.f, ny = 0.f;
    switch (direction) {
    case 0: ny = 1.f; break; // a сверху, давит вниз
    case 1: nx = 1.f; break; // a слева, давит вправо
    case 2: ny = -1.f; break; // a снизу, давит вверх
    case 3: nx = -1.f; break; // a справа, давит влево
    default: return;
    }

    float vRelX = a.VelX - b.VelX;
    float vRelY = a.VelY - b.VelY;

    vRelX *= size;
    vRelY *= size;

    if (vRelX * nx <= 0 && vRelY * ny <= 0) return;

    float Bon = (AMat.Bounciness);
    float Sc = (AMat.ScatterFactor + BMat.ScatterFactor) * 0.5f;
    float Fr = (AMat.SurfaceFriction + BMat.SurfaceFriction) * 0.5f;




    if (AMat.Density != BMat.Density)
    {
        if (nx != 0)
        {
            a.VelX -= vRelX;
            b.VelX += vRelX * AMat.Density / BMat.Density;
        }
        else
        {
            a.VelY -= vRelY;
            b.VelY += vRelY * AMat.Density / BMat.Density;
        }
    }
    else
    {
        if (nx != 0)
        {
            a.VelX -= vRelX;
            b.VelX += vRelX;
        }           
        else
        {
            a.VelY -= vRelY;
            b.VelY += vRelY;
        }
           
    }


    if (nx != 0)
    {
        float FrictionY = Fr * vRelX;
        bool vyN = a.VelY >= 0;
        a.VelY = std::max(abs(a.VelY) - abs(FrictionY), 0.f) * ((vyN) ? 1.f : -1.f);
    }
    else
    {
        float FrictionX = Fr * vRelY;
        bool vxN = a.VelX >= 0;
        a.VelX = std::max(abs(a.VelX) - abs(FrictionX), 0.f) * ((vxN) ? 1.f : -1.f);
    }

  
}

float GameSimulation::DoLiteCollision(GameCell& a, GameCell& b, uint8_t direction, int& xA, int& yA, int& xB, int& yB)
{
    /*  switch (direction) {
    case 0: ny = 1.f; break; // a сверху, давит вниз
    case 1: nx = 1.f; break; // a слева, давит вправо
    case 2: ny = -1.f; break; // a снизу, давит вверх
    case 3: nx = -1.f; break; // a справа, давит влево
    default: return;
    }
*/

    auto& config = GameConfigManager::GetGameConfigManager();

    const auto& mat = config.Materials.GetElement(a.OriginalMaterialID);
    const auto& target_mat = config.Materials.GetElement(b.OriginalMaterialID);

if (mat.StateCategory == StateCategoryEnum::liquid || target_mat.StateCategory == StateCategoryEnum::liquid) return 0;

    if ((target_mat.StateCategory == StateCategoryEnum::liquid || target_mat.StateCategory == StateCategoryEnum::gas)
        && mat.Density > target_mat.Density)
    {
        return 1.f;
    }

    if (target_mat.StateCategory != StateCategoryEnum::solid || !target_mat.CanSlide)
    {
        DoCollision(a, GameField(xB, yB), direction, xA, yA);
        return 0.f;
    }

       /* if (!direction && yA == yB-1 && xA == xB)
        {
            bool tried = 1;
            if (RandomFloat(xA, yB, TecTick) > 0.5f)
            {
                Ch1:
                if (xA > 0 && !GameField(xA - 1, yA).Active && !GameField(xA - 1, yA + 1).Active)
                {
                    DoCollision(a, b, direction, xA, yA, 0.3f);
                    xB--;
                    xA--;
                    auto& NewB = GameField(xB, yA);
                    std::swap(a, NewB);
                    DoCollision(a, NewB, direction, xA, yA);
                    return 0.7f;
                }
                else if (tried)
                {
                    tried = 0;
                    goto Ch2;
                }
            }
            else
            {
                Ch2:
                if (xA < GameSizeX-1 && !GameField(xA + 1, yA).Active && !GameField(xA + 1, yA + 1).Active)
                {
                    DoCollision(a, b, direction, xA, yA, 0.3f);
                    xB++;
                    xA++;
                    auto& NewB = GameField(xB, yA);
                    std::swap(a, NewB);
                    DoCollision(a, NewB, direction, xA, yA);
                    return 0.7f;
                }
                else if (tried)
                {
                    tried = 0;
                    goto Ch1;
                }
            }
        }*/



    int normalX = 0, normalY = 0;
    int tangentX = 0, tangentY = 0;

    switch (direction)
    {
    case 0: normalY = 1; tangentX = 1; break; // A сверху, B снизу
    case 1: normalX = 1; tangentY = 1; break; // A слева, B справа
    case 2: normalY = -1; tangentX = 1; break; // A снизу, B сверху
    case 3: normalX = -1; tangentY = 1; break; // A справа, B слева
    default: return 0.0f;
    }

    if (xB != xA + normalX || yB != yA + normalY)
    {
        DoCollision(a, GameField(xB, yB), direction, xA, yA);
        return 0.0f;
    }

    auto IsOutOfBounds = [&](int x, int y) {
        return x < 0 || x >= GameSizeX || y < 0 || y >= GameSizeY;
        };


    auto TrySlide = [&](int sign) -> bool
        {
            const int slideX = xA + tangentX * sign;
            const int slideY = yA + tangentY * sign;
            const int cornerX = slideX + normalX; 
            const int cornerY = slideY + normalY;

            if (IsOutOfBounds(slideX, slideY) || GameField(slideX, slideY).Active) return false;
            if (IsOutOfBounds(cornerX, cornerY) || GameField(cornerX, cornerY).Active) return false;
     
            xB = slideX;
            yB = slideY;

            return true;
        };

    bool firstPositive = RandomFloat(xA, yA + xB + yB, TecTick) > 0.5f;
    int firstSign = firstPositive ? 1 : -1;

    if (TrySlide(firstSign) || TrySlide(-firstSign))
    {
        DoCollision(a, b, direction, xA, yA, 0.3f);
        return 0.7f;

    }

    DoCollision(a, GameField(xB, yB), direction, xA, yA);
    return 0.0f;
}

   


void GameSimulation::NormalizeVelocity()
{
    auto& config = GameConfigManager::GetGameConfigManager();

    for (auto& i : GameField.GetVector())
    {
        if (i.Active && i.Updating != 1)
        {
            i.Updating = 3;

            auto cat = config.Materials.GetElement(i.OriginalMaterialID).StateCategory;
            if (cat == StateCategoryEnum::unmovable)
            {
                i.VelX = 0;
                i.VelY = 0;
            }
            else
            {
                i.VelX *= 0.99;
                i.VelY *= 0.99;
                if (abs(i.VelX) < 0.01f) i.VelX = 0.f;
                if (abs(i.VelY) < 0.01f) i.VelY = 0.f;

                if (cat == StateCategoryEnum::liquid)
                {
                    i.Pressure = std::max (i.Pressure * 0.95f, 0.f);
                }

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

inline float GameSimulation::RandomFloat(const uint32_t x, const uint32_t y, const uint32_t tick)
{
    return static_cast<float>(Deterministic_hash(x, y, tick)) / static_cast<float>(UINT32_MAX);
}
