#pragma once
#include "BaseWidget.h"

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

public:
	RenderManager();
	~RenderManager();

	bool Init();
	bool Render();
	void Destroy();

	BaseWidget MainWidget;

	void DrawRect();
};