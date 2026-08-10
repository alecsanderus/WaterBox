#include "GameViewWidget.h"
#include "RenderManager.h"
#include "Game/GameSimulation.h"
#include "Game/GameManager.h"
#include "SDL3/SDL.h"

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
	return PrimitivePoint{ScreenInfo->ScreenSizeY, ScreenInfo->ScreenSizeY};
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
        SizeX * sizeof(uint32_t)
    );
}

void GameViewWidget::Render(RenderManager& renderer, const PrimitivePoint& Position)
{
    if (!Renderer) Renderer = renderer.GetSDLRenderer();

    UpdateTexture();


    auto ScreenInfo = RenderManager::GetScreenInfo();

    SDL_FRect destination{
    Position.x,
    Position.y,
    ScreenInfo->ScreenSizeY,
    ScreenInfo->ScreenSizeY
    };

    SDL_RenderTexture(
        Renderer,
        Texture,
        nullptr,
        &destination
    );
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
        X,
        Y
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
