#pragma once
#include "UI/MainUIWidget.h"

union SDL_Event;

struct ScreenInfoStruct
{
	int ScreenSizeX = 1920;
	int ScreenSizeY = 1080;
};


enum class ScreenEventButtonType : uint8_t
{
	NO,
	RMB,
	LMB,
	MMB,
	FINGER
};

enum class ScreenEventType : uint8_t
{
	DOWN,
	UP,
	MOVE
};

struct ScreenEvent
{
	ScreenEventButtonType ButtonType = ScreenEventButtonType::NO;
	ScreenEventType Type;
	PrimitivePoint Point;
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
	struct SimulationKeyEvent CreateSimulationKeyEvent(const SDL_Event& sdlEvent);


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

	bool Init();
	bool Render();
	void Destroy();
	bool ProcessEvent(const SDL_Event& event);

	MainUIWidget MainWidget;
	BaseWidget* FocusedWidget = nullptr;
	EventFocusType FocusedWidgetType = EventFocusType::NO;

	void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha = 255);
	void DrawRect(struct PrimitiveRect Rect);
};