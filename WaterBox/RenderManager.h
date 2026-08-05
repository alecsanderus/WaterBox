#pragma once
#include "UI/MainUIWidget.h"

union SDL_Event;

struct ScreenInfoStruct
{
	int ScreenSizeX = 1920;
	int ScreenSizeY = 1080;
};




struct ScreenEvent
{
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

	ScreenEventButtonType ButtonType = ScreenEventButtonType::NO;
	ScreenEventType Type;
	PrimitivePoint Point;
};


class RenderManager
{

protected:

	struct SDL_Window* window = nullptr;
	struct SDL_Renderer* renderer = nullptr;
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

	MainUIWidget MainWidget;

	void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha = 255);
	void DrawRect(struct PrimitiveRect Rect);
};