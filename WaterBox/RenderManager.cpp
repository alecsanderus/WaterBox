#include "RenderManager.h"
#include <SDL3/SDL.h>
#include "WaterBox.h"
#include "UI/MainUIWidget.h"
#include "UI/ScreenPositionContainers.h"


RenderManager::RenderManager()
{}

RenderManager::~RenderManager()
{
    Destroy();
}

bool RenderManager::Init()
{
    if (NeedToDestroyWindow)
    {
        LOG_WARN ("Window is already opened");
        return true;
    }

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        LOG_FATAL("SDL_Init failed");
        LOG_FATAL(SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(
        "app",
        800, 600,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY
    );

    if (!window) {
        LOG_FATAL("Window creation failed : ");
        LOG_FATAL(SDL_GetError());      
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        LOG_FATAL("Renderer creation failed: ");
        LOG_FATAL(SDL_GetError());       
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    SDL_SetRenderVSync(renderer, 1);

    LOG_INFO ("Window created");

    UpdateScreenInfo();

    NeedToDestroyWindow = true;

  
    MainWidget.Init();

    return true;
}

bool RenderManager::Render()
{
    // Очистка экрана синим цветом (R, G, B, A)
    SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255);
    SDL_RenderClear(renderer);    

    MainWidget.Render(*this, {0,0});

    SDL_RenderPresent(renderer);

    return true;
}

void RenderManager::Destroy()
{
    if (NeedToDestroyWindow)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}

bool RenderManager::ProcessEvent(const SDL_Event& event)
{
    switch (event.type)
    {

    case SDL_EVENT_WINDOW_RESIZED:
        UpdateScreenInfo();
        break;

    case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
        UpdateScreenInfo();
        break;

    case SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED:
        UpdateScreenInfo();
        break;

    default:
        return false;
        break;
    }

    return true;
}


void RenderManager::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
}

void RenderManager::DrawRect(PrimitiveRect Rect)
{
    SDL_FRect rect{
        static_cast<float>(Rect.pos.x),
        static_cast<float>(Rect.pos.y),
        static_cast<float>(Rect.size.x),
        static_cast<float>(Rect.size.y)
    };
   
    SDL_RenderFillRect(renderer, &rect);
}


void RenderManager::UpdateScreenInfo()
{
    int w, h;

    SDL_GetRenderOutputSize(renderer, &w, &h);

    auto ScreenInfo = GetScreenInfo();

    ScreenInfo->ScreenSizeX = w;
    ScreenInfo->ScreenSizeY = h;
}


