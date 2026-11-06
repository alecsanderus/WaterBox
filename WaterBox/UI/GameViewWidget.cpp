#include "GameViewWidget.h"
#include "RenderManager.h"
#include "Game/GameSimulation.h"
#include "Game/GameManager.h"
#include "SDL3/SDL.h"
#include "Game/SimulationTool.h"
#include "InputEvent.h"

GameViewWidget::GameViewWidget()
{
	auto& MainGameManager = GameManager::GetGameManager();
	auto& MainGameSimulation = MainGameManager.GetSimulation();
    SizeX = MainGameSimulation.GetGameFieldSize().first;
    SizeY = MainGameSimulation.GetGameFieldSize().second;



    Pixels.resize(SizeX * SizeY);  
}

PrimitivePoint GameViewWidget::GetSize()
{
    auto ScreenInfo = RenderManager::GetScreenInfo();
    SizeX = SizeY = ScreenInfo->ScreenSizeY;

	return PrimitivePoint{ ScreenInfo->ScreenSizeY, ScreenInfo->ScreenSizeY };
}

void GameViewWidget::UpdateTexture()
{
    if (!Texture)  CreateTexture(SizeX, SizeY);
    auto& MainGameManager = GameManager::GetGameManager();
    auto& MainGameSimulation = MainGameManager.GetSimulation();
    const std::vector<GameCell>& Grid = MainGameSimulation.GetGameField().GetVector();
    auto& MainSimulationTool = MainGameManager.GetSimulationTool();
    int type = MainSimulationTool.GetGameViewType();


    if (auto [NewX, NewY] = MainGameSimulation.GetGameFieldSize(); SizeX != NewX || SizeY != NewY)
    {
        SizeX = NewX;
        SizeY = NewY;

        Pixels.resize(SizeX * SizeY);

        CreateTexture(SizeX, SizeY);
    }
    else   if (!Texture)  CreateTexture(SizeX, SizeY);

    for (size_t tec = 0; tec < Grid.size(); tec++)
    {
        const auto& color = Grid[tec].Color;

        switch (type) {
            case 0: {
                Pixels[tec] =
            (static_cast<uint32_t>(color.r) << 24) |
            (static_cast<uint32_t>(color.g) << 16) |
            (static_cast<uint32_t>(color.b) << 8) |
            static_cast<uint32_t>(255);
                break;
            }

            case 1: {
                const auto& gg = Grid[tec];
                Pixels[tec] =
                    (static_cast<uint32_t>(gg.VelX * 5 + 120) << 24) |
                    (static_cast<uint32_t>(gg.OriginalMaterialID * 50) << 16) |
                    (static_cast<uint32_t>(gg.VelY * 5 + 120) << 8) |
                    static_cast<uint32_t>(255);
                break;
            }

            case 2: {
                const auto& gg = Grid[tec];
                ColorStr color = {0,0,0,255};
                if (gg.Active)
                    color = PressureToColor (gg.Pressure);

                Pixels[tec] =
                    (static_cast<uint32_t>(color.r) << 24) |
                    (static_cast<uint32_t>(color.g) << 16) |
                    (static_cast<uint32_t>(color.b) << 8) |
                    static_cast<uint32_t>(255);
                break;
            }

            default:
            {
                Pixels[tec] =
            (static_cast<uint32_t>(color.r) << 24) |
            (static_cast<uint32_t>(color.g) << 16) |
            (static_cast<uint32_t>(color.b) << 8) |
            static_cast<uint32_t>(255);
                break;
            }


        }
        /**/


        /*const auto& gg = Grid[tec];
        Pixels[tec] =
            (static_cast<uint32_t>(gg.VelX * 5 + 120) << 24) |
            (static_cast<uint32_t>(gg.OriginalMaterialID * 50) << 16) |
            (static_cast<uint32_t>(gg.VelY * 5 + 120) << 8) |
            static_cast<uint32_t>(255);*/



        /*
        const auto& gg = Grid[tec];
        Pixels[tec] =
            (static_cast<uint32_t>(gg.Pressure / 2000) << 24) |
            (static_cast<uint32_t>(170) << 16) |
            (static_cast<uint32_t>(170) << 8) |
            static_cast<uint32_t>(255);*/
    }


    SDL_UpdateTexture(
        Texture,
        nullptr,
        Pixels.data(),
        static_cast<int> (SizeX * sizeof(uint32_t))
    );
}

void GameViewWidget::Render(RenderManager& renderer, const PrimitivePoint& Position)
{
    if (!Renderer) Renderer = renderer.GetSDLRenderer();

    UpdateTexture();


    auto ScreenInfo = RenderManager::GetScreenInfo();

    SDL_FRect destination{
    static_cast <float> (Position.x),
    static_cast <float> (Position.y),
    static_cast <float> (ScreenInfo->ScreenSizeY),
    static_cast <float> (ScreenInfo->ScreenSizeY)
    };

    SDL_RenderTexture(
        Renderer,
        Texture,
        nullptr,
        &destination
    );
}

bool GameViewWidget::ProcessEvent(const in::InputEvent& event)
{
    auto& lock = RenderManager::GetLockEventState();

    if (lock.first != this)
    {
        if (event.x >= SizeX || event.y >= SizeY || event.x < 0 || event.y < 0 || !(event.isMouseButton() || event.isMouseScroll()))
            return false;
    }
  
 
    auto& SimTool = GameManager::GetGameManager().GetSimulationTool();       
    auto MySize = GetSize();
    auto GameSize = GameManager::GetGameManager().GetSimulation().GetGameFieldSize();

    in::InputEvent NewEvent = event;

    NewEvent.x = std::clamp(event.x * (int)GameSize.first / (int)MySize.x, 0, (int)GameSize.first-1);
    NewEvent.y = std::clamp(event.y * (int)GameSize.second / (int)MySize.y, 0, (int)GameSize.second-1);


    if (!event.isMouseScroll())    
        lock = { this, EventFocusType::Lock_AutoUnlock };     
    


    SimTool.ProcessEvent(NewEvent);
    
    return true;
}

GameViewWidget::~GameViewWidget()
{
    if (Texture)
        SDL_DestroyTexture(Texture);
}

void GameViewWidget::CreateTexture(size_t X, size_t Y)
{
    if (Texture)
        SDL_DestroyTexture(Texture);

    Texture = SDL_CreateTexture(
        Renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        static_cast <int> (X),
        static_cast <int> (Y)
    );

    SDL_SetTextureScaleMode(
        Texture,
        SDL_SCALEMODE_NEAREST
    );

    if (!Texture)
    {
        throw std::runtime_error(SDL_GetError());
    }
}



inline ColorStr GameViewWidget::PressureToColor(const float pressure, const float maxDisplayPressure)
{
    if (!(pressure > 0.f)) return { 0, 0, 0, 255 };


    if (pressure >= maxDisplayPressure) return { 255, 0, 0, 255 };

    const float scale = maxDisplayPressure * 0.25f;

    float t;

    if (pressure <= scale)
    {
        float x = pressure / scale;
        t = 1.25f * x / (1.f + x);
    }
    else
    {
        float x = scale / pressure;
        t = 1.25f / (1.f + x);
    }

    constexpr uint8_t R[5] = { 0,   0,   0, 255, 255 };
    constexpr uint8_t G[5] = { 0,  64, 255, 220,   0 };
    constexpr uint8_t B[5] = { 32, 255, 160,   0,   0 };

    float scaled = t * 4.f;

    int index = static_cast<int>(scaled);

    float blend;

    if (index >= 4)
    {
        index = 3;
        blend = 1.f;
    }
    else
        blend = scaled - index;


    auto lerp = [blend](uint8_t a, uint8_t b)
    {
        return static_cast<uint8_t>(
            static_cast<float>(a) +
            (static_cast<float>(b) - static_cast<float>(a))
            * blend + 0.5f
        );
    };

    return {
        lerp(R[index], R[index + 1]),
        lerp(G[index], G[index + 1]),
        lerp(B[index], B[index + 1]),
        255
    };
}

