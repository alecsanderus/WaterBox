#include "WaterBox.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "RenderManager.h" 
#include "ExeptionHandlers.h"



int GameMain();

int main(int argc, char* argv[]) {

#ifdef _WIN32
    SetUnhandledExceptionFilter(UnhandledExceptionFilter);
    _set_se_translator(TranslateException);
#endif

    Logger::Instance().Init();
    SDL_SetLogOutputFunction(LogCallback, nullptr);

    try {  
        return GameMain();
    }
    catch (const std::exception& e) {
        OpenProgramDeathScreen(std::string("Fatal error (std::exception): ") + e.what());
        return 1;
    }
    catch (const std::string& e) {
        OpenProgramDeathScreen(std::string("Fatal error (std::string): ") + e);
        return 1;
    }
    catch (...) {
        OpenProgramDeathScreen("Fatal error: Unknown exception");
        return 1;
    }
}

int GameMain()
{

    bool Running = true;

    LOG_INFO("Console launched");

    RenderManager MainRenderManager;

    if (!MainRenderManager.Init())
        Running = false;

    SDL_Event event;

    while (Running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                Running = false;
            }
            else
                if (event.type == SDL_EVENT_KEY_DOWN) {
                    if (event.key.key == SDLK_ESCAPE) {
                        Running = false;
                    }
                }
                else
                    MainRenderManager.ProcessEvent(event);
        }

        if (!MainRenderManager.Render())
            Running = false;

       // auto err = SDL_GetError();
       // if (err != "")
       //     LOG_ERROR(err);
        //if (const char* err = SDL_GetError(); err && *err)
        //{
        //    LOG_ERROR(err);
        //}
    }

    if (const char* err = SDL_GetError(); err && *err)
    {
        LOG_ERROR(err);
    }

    MainRenderManager.Destroy();
    LOG_INFO("Exit");

#ifdef ENABLE_CONSOLE
    system("pause");
#endif 


    return 0;
}