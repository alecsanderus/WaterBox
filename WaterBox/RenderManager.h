#pragma once
#include "BaseWidget.h"

union SDL_Event;

struct ScreenInfoStruct
{
	int ScreenSizeX = 1920;
	int ScreenSizeY = 1080;
};

enum class ScreenEventType
{
	RMB,
	LMB,
	MMB
};


struct ScreenEvent
{
	ScreenEventType Type;
};


class RenderManager
{

protected:

	class SDL_Window* window = nullptr;
	class SDL_Renderer* renderer = nullptr;
	bool NeedToDestroyWindow = false;
	void UpdateScreenInfo();

public:
	RenderManager();
	~RenderManager();

	static ScreenInfoStruct* GetScreenInfo()
	{
		static ScreenInfoStruct ScreenInfo;
		return &ScreenInfo;
	}

	bool Init();
	bool Render();
	void Destroy();
	bool ProcessEvent(const SDL_Event& event);
	BaseWidget MainWidget;

	void DrawRect(struct ScreenRect Rect);
};