#include "RenderManager.h"
#include <SDL3/SDL.h>
#include "WaterBox.h"
#include "UI/MainUIWidget.h"
#include "UI/ScreenPositionContainers.h"
#include "Game/SimulationTool.h"
#include "Game/GameManager.h"


RenderManager::RenderManager()
{}

RenderManager::~RenderManager()
{
    Destroy();
}

std::pair<BaseWidget*, EventFocusType>& RenderManager::GetLockEventState()
{
    static std::pair<BaseWidget*, EventFocusType> state (nullptr, EventFocusType::NO);

    return state;
} 

bool RenderManager::Init()
{
    if (NeedToDestroyWindow)
    {
        LOG_WARN ("Window is already opened");
        return true;
    }

    SDL_SetHint(SDL_HINT_ORIENTATIONS, "LandscapeLeft LandscapeRight");


    if (!SDL_Init(SDL_INIT_VIDEO)) {
        LOG_FATAL("SDL_Init failed");
        LOG_FATAL(SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(
        "WaterBox",
        1000, 600,
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

bool RenderManager::ProcessEvent(const SDL_Event& EventSDL)
{
    switch (EventSDL.type)
    {

    case SDL_EVENT_WINDOW_RESIZED:
    {
        UpdateScreenInfo();
        break;
    }

    case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
    {
        UpdateScreenInfo();
        break;
    }

    case SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED:
    {
        UpdateScreenInfo();
    
        break;
    }

    case SDL_EVENT_MOUSE_BUTTON_DOWN:
    {
        ScreenEvent Event;
        Event.Point.x = static_cast <int> (EventSDL.button.x);
        Event.Point.y = static_cast <int> (EventSDL.button.y);
        Event.Type = ScreenEventType::DOWN;
        switch (EventSDL.button.button)
        {
        case SDL_BUTTON_LEFT:
            Event.ButtonType = ScreenEventButtonType::LMB;
            break;

        case SDL_BUTTON_RIGHT:
            Event.ButtonType = ScreenEventButtonType::RMB;
            break;

        case SDL_BUTTON_MIDDLE:
            Event.ButtonType = ScreenEventButtonType::MMB;
            break;
        }

        MainWidget.ProcessEvent(Event);
        break;
    }
     

    case SDL_EVENT_MOUSE_BUTTON_UP:
    {
        ScreenEvent Event;
        Event.Point.x = static_cast <int> (EventSDL.button.x);
        Event.Point.y = static_cast <int> (EventSDL.button.y);
        Event.Type = ScreenEventType::UP;
        switch (EventSDL.button.button)
        {
        case SDL_BUTTON_LEFT:
            Event.ButtonType = ScreenEventButtonType::LMB;
            break;

        case SDL_BUTTON_RIGHT:
            Event.ButtonType = ScreenEventButtonType::RMB;
            break;

        case SDL_BUTTON_MIDDLE:
            Event.ButtonType = ScreenEventButtonType::MMB;
            break;
        }

        MainWidget.ProcessEvent(Event);
        break;
    }

    case SDL_EVENT_MOUSE_MOTION:
    {
        ScreenEvent Event;
        Event.Point.x = static_cast <int> (EventSDL.motion.x);
        Event.Point.y = static_cast <int> (EventSDL.motion.y);
        Event.Type = ScreenEventType::MOVE;

        MainWidget.ProcessEvent(Event);
        break;
    }

    case SDL_EVENT_KEY_DOWN:
    {
        if (EventSDL.key.key == SDLK_F11)
        {
            bool FullScreen = SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN;

            SDL_SetWindowFullscreen(window, !FullScreen);
        }
        else
        {
            auto Event = CreateSimulationKeyEvent(EventSDL);
            Event.State = true;
            GameManager::GetGameManager().GetSimulationTool().ProcessKeyEvent(Event);

        }
        break;
    }
    case SDL_EVENT_KEY_UP:
    {
        auto Event = CreateSimulationKeyEvent(EventSDL);
        Event.State = false;
        GameManager::GetGameManager().GetSimulationTool().ProcessKeyEvent(Event);
    }
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


SimulationKeyEvent RenderManager::CreateSimulationKeyEvent (const SDL_Event& sdlEvent)
{
    SimulationKeyEvent simEvent;

  
    simEvent.State = sdlEvent.key.down;

    SDL_Keycode keycode = sdlEvent.key.key;

    switch (keycode)
    {
    case SDLK_SPACE:
        simEvent.Type = SimulationKeyEvent::SimulationKeyEventSymbol::SPACE;
        break;

    case SDLK_LSHIFT:
    case SDLK_RSHIFT:
        simEvent.Type = SimulationKeyEvent::SimulationKeyEventSymbol::SHIFT;
        break;

    case SDLK_LCTRL:
    case SDLK_RCTRL:
        simEvent.Type = SimulationKeyEvent::SimulationKeyEventSymbol::CONTROL;
        break;

    case SDLK_LALT:
    case SDLK_RALT:
        simEvent.Type = SimulationKeyEvent::SimulationKeyEventSymbol::ALT;
        break;

    default:
        simEvent.Type = SimulationKeyEvent::SimulationKeyEventSymbol::SYMBOL;

        if (keycode >= 32 && keycode <= 126)
        {
            simEvent.Symbol = static_cast<char>(keycode);
        }
        else
        {
            simEvent.Symbol = '\0';
        }
        break;
    }

    return simEvent;
}
