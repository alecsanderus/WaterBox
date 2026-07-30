#include "RenderManager.h"
#include <SDL3/SDL.h>
#include "WaterBox.h"
#include "ButtonWidget.h"



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

    NeedToDestroyWindow = true;
    ButtonWidget *but = new ButtonWidget;
    MainWidget.Children.push_back(but);
    return true;
}

bool RenderManager::Render()
{
    // Очистка экрана синим цветом (R, G, B, A)
    SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255);
    SDL_RenderClear(renderer);    
    MainWidget.Render(*this);

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

void RenderManager::DrawRect()
{
    SDL_FRect rect{ 100, 50, 200, 40 };

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}



