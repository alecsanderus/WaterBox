#include "RenderManager.h"
#include <SDL3/SDL.h>
#include "WaterBox.h"
#include "UI/MainUIWidget.h"
#include "UI/ScreenPositionContainers.h"
#include "Game/SimulationTool.h"
#include "Game/GameManager.h"
#include "InputEvent.h"



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

    auto EventVariant = TranslateSDLEvent(EventSDL);

    if (!EventVariant)
    {
        switch (EventSDL.type)
        {

        case SDL_EVENT_WINDOW_RESIZED:
        {
            UpdateScreenInfo();
            return true;
        }

        case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
        {
            UpdateScreenInfo();
            return true;
        }

        case SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED:
        {
            UpdateScreenInfo();

            return true;
        }
        default:
        {
            return false;
        }
        }
    } 

    auto& event = EventVariant.value();
    if (event.isMouseMove() || event.isMouseButton() || event.isMouseScroll())
        MainWidget.ProcessEvent(event);

    else if (event.isKey())
        GameManager::GetGameManager().GetSimulationTool().ProcessEvent(event);


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

void RenderManager::SetClipRect(const PrimitiveRect* rect)
{
    if (rect == nullptr || !(rect->pos.x || rect->pos.y || rect->size.x || rect->size.y))
    {        
        SDL_SetRenderClipRect (renderer, nullptr);
        return;
    }

    SDL_Rect sdlRect{
        rect->pos.x,
        rect->pos.y,
        rect->size.x,
        rect->size.y
    };

    SDL_SetRenderClipRect(renderer, &sdlRect);
}

void RenderManager::GetClipRect(PrimitiveRect& outRect)
{
    SDL_Rect sdlRect;
    SDL_GetRenderClipRect(renderer, &sdlRect);

    outRect.pos.x = sdlRect.x;
    outRect.pos.y = sdlRect.y;
    outRect.size.x = sdlRect.w;
    outRect.size.y = sdlRect.h;
}

void RenderManager::UpdateScreenInfo()
{
    int w, h;

    SDL_GetRenderOutputSize(renderer, &w, &h);

    auto ScreenInfo = GetScreenInfo();

    ScreenInfo->ScreenSizeX = w;
    ScreenInfo->ScreenSizeY = h;
}

std::optional<in::InputEvent> RenderManager::TranslateSDLEvent(const SDL_Event& sdlEvent) {
    using namespace in;

    InputEvent result;

    {
        auto SDL_Modifiers = SDL_GetModState();

        KeyModifiers mods = KeyModifiers::None;
        if (SDL_Modifiers & SDL_KMOD_SHIFT) mods = mods | KeyModifiers::Shift;
        if (SDL_Modifiers & SDL_KMOD_CTRL)  mods = mods | KeyModifiers::Ctrl;
        if (SDL_Modifiers & SDL_KMOD_ALT)   mods = mods | KeyModifiers::Alt;
        result.modifiers = mods;
    }

    switch (sdlEvent.type) {

    case SDL_EVENT_MOUSE_MOTION: {
        result.data = MouseMoveEvent{};

        result.x = static_cast<int32_t>(sdlEvent.motion.x);
        result.y = static_cast<int32_t>(sdlEvent.motion.y);
        return result;
    }

    case SDL_EVENT_MOUSE_BUTTON_DOWN:
    case SDL_EVENT_MOUSE_BUTTON_UP: {

        MouseButton btn = MouseButton::None;
        switch (sdlEvent.button.button) {
        case SDL_BUTTON_LEFT:   btn = MouseButton::Left; break;
        case SDL_BUTTON_RIGHT:  btn = MouseButton::Right; break;
        case SDL_BUTTON_MIDDLE: btn = MouseButton::Middle; break;
        case SDL_BUTTON_X1:     btn = MouseButton::XButton1; break;
        case SDL_BUTTON_X2:     btn = MouseButton::XButton2; break;
        }

        result.data = MouseButtonEvent{           
            .button = btn,
            .action = (sdlEvent.type == SDL_EVENT_MOUSE_BUTTON_DOWN) ? InputAction::Press : InputAction::Release
        };
        result.x = static_cast<int32_t>(sdlEvent.button.x);
        result.y = static_cast<int32_t>(sdlEvent.button.y);
        return result;
    }


    case SDL_EVENT_MOUSE_WHEEL: {
        float mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        result.data = MouseScrollEvent{
            
            .deltaX = sdlEvent.wheel.x,
            .deltaY = sdlEvent.wheel.y,
            .FullX = sdlEvent.wheel.integer_x,
            .FullY = sdlEvent.wheel.integer_y
        };
        result.x = static_cast<int32_t>(mouseX);
        result.y = static_cast<int32_t>(mouseY);

        return result;
    }

    case SDL_EVENT_KEY_DOWN:
    case SDL_EVENT_KEY_UP: {
        InputAction action = InputAction::Release;

        float mouseX = 0.0f;
        float mouseY = 0.0f;
        SDL_GetMouseState(&mouseX, &mouseY);
        result.x = mouseX;
        result.y = mouseY;



        if (sdlEvent.type == SDL_EVENT_KEY_DOWN) {
            action = sdlEvent.key.repeat ? InputAction::Repeat : InputAction::Press;
        }

        char ch = 0;
        if (sdlEvent.key.key >= 32 && sdlEvent.key.key <= 126) {
            ch = static_cast<char>(sdlEvent.key.key);
        }

        result.data = KeyEvent{
            .keyCode = static_cast<uint32_t>(sdlEvent.key.scancode),
            .character = ch,
            .action = action
        };
        return result;
    }

                      
    case SDL_EVENT_TEXT_INPUT: {

        float mouseX = 0.0f;
        float mouseY = 0.0f;
        SDL_GetMouseState(&mouseX, &mouseY);
        result.x = mouseX;
        result.y = mouseY;

        // SDL3 передает строку UTF-8 в sdlEvent.text.text.
        // Для нашей структуры TextInputEvent (которая ждет char32_t) 
        // возьмем первый символ (подходит для базовой латиницы/кириллицы).
        // При необходимости здесь можно развернуть полный UTF-8 дельсер.
        result.data = TextInputEvent{
            .codepoint = static_cast<char32_t>(sdlEvent.text.text[0])
        };
        return result;
    }

    default:
        break;
    }

    return std::nullopt;
}