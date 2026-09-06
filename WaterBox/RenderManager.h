#pragma once
#include "UI/MainUIWidget.h"
#include <optional>


union SDL_Event;
namespace in { struct InputEvent; }


struct ScreenInfoStruct
{
	int ScreenSizeX = 1920;
	int ScreenSizeY = 1080;
};


enum class EventFocusType : uint8_t
{
	NO,
	OK,
	Lock,
	Lock_AutoUnlock,
	Unlock
};


class RenderManager
{

private:

	struct SDL_Window* window = nullptr;
	struct SDL_Renderer* renderer = nullptr;
	bool NeedToDestroyWindow = false;
	void UpdateScreenInfo();


public:
	RenderManager();
	~RenderManager();

	static ScreenInfoStruct* GetScreenInfo()	{
		static ScreenInfoStruct ScreenInfo;
		return &ScreenInfo;
	}

	static std::pair <BaseWidget*, EventFocusType>& GetLockEventState();
	struct SDL_Renderer* GetSDLRenderer(){
		return renderer;
	}

	std::optional<in::InputEvent> TranslateSDLEvent(const SDL_Event& sdlEvent);


	bool Init();
	bool Render();
	void Destroy();
	bool ProcessEvent(const SDL_Event& event);

	MainUIWidget MainWidget;
	BaseWidget* FocusedWidget = nullptr;
	EventFocusType FocusedWidgetType = EventFocusType::NO;

	void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha = 255);
	void DrawRect(struct PrimitiveRect Rect);
	void SetClipRect(const PrimitiveRect* rect);
	void GetClipRect(PrimitiveRect& outRect);
};