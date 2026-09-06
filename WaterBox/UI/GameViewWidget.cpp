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

        Pixels[tec] =
            (static_cast<uint32_t>(color.R) << 24) |
            (static_cast<uint32_t>(color.G) << 16) |
            (static_cast<uint32_t>(color.B) << 8) |
            static_cast<uint32_t>(255);
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

    if (lock.first != this && ( event.x >= SizeX || event.y >= SizeY || event.isMouseButton()))
        return false;
 
    auto& SimTool = GameManager::GetGameManager().GetSimulationTool();       
    auto MySize = GetSize();
    auto GameSize = GameManager::GetGameManager().GetSimulation().GetGameFieldSize();

    in::InputEvent NewEvent = event;

    int PosX = NewEvent.x = event.x * GameSize.first / MySize.x;
    int PosY = NewEvent.y = event.y * GameSize.second / MySize.y;   

    PosX = std::max(PosX, 0);
    PosY = std::max(PosY, 0);
    PosX = std::min(PosX, (int)GameSize.first -1);
    PosY = std::min(PosY, (int)GameSize.second -1);
  
    lock  = { this, EventFocusType::Lock_AutoUnlock };

    if (OldX != -1 && OldY != -1)
    {
        int dx = std::abs(PosX - OldX);
        int dy = std::abs(PosY - OldY);

        int sx = (OldX < PosX) ? 1 : -1;
        int sy = (OldY < PosY) ? 1 : -1;

        int err = dx - dy;

        while (true) {
            NewEvent.x = OldX;
            NewEvent.y = OldY;
            SimTool.ProcessEvent(NewEvent);

            if (OldX == PosX && OldY == PosY) {
                break;
            }

            int e2 = 2 * err;

            if (e2 > -dy) {
                err -= dy;
                OldX += sx;
            }

            if (e2 < dx) {
                err += dx;
                OldY += sy;
            }
        }
    }
    else
    {
        SimTool.ProcessEvent(NewEvent);
    }


   


    if (event.isMouseButton() && std::get <in::MouseButtonEvent> (event.data).action == in::InputAction::Release) { OldX = -1; OldY = -1; }
    else {OldX = PosX; OldY = PosY;}

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
