#pragma once
#include "UI/MainUIWidget.h"
#include <optional>


union SDL_Event;
namespace in { struct InputEvent; }
class RenderManager;


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

struct ColorStr{uint8_t r, g, b, a;};

struct TextInstance
{	
	void Init(RenderManager& manager, const std::string text, const ColorStr color);
	void Draw(RenderManager& manager, const PrimitivePoint point);
	void ChangeColor(const ColorStr color);
	void ChangeText(const std::string text);
	TextInstance(const TextInstance&) = delete;
	TextInstance& operator=(const TextInstance&) = delete;
	TextInstance() = default;
	~TextInstance();
private:
	struct TTF_Text* TextTtf = nullptr;
};


class RenderManager
{
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

	void SetColor(ColorStr color);
	void DrawRect(struct PrimitiveRect Rect);
	void SetClipRect(const PrimitiveRect* rect);
	void GetClipRect(PrimitiveRect& outRect);

	void FastDrawText(std::string text, ColorStr color, PrimitivePoint point);



private:
	struct SDL_Window* window = nullptr;
	struct SDL_Renderer* renderer = nullptr;
	bool NeedToDestroyWindow = false;
	void UpdateScreenInfo();
	

	struct TTF_TextEngine* TextEngine = nullptr;
	struct TTF_Font* TextFont;
	void CheckTextMap();

	std::unordered_map <std::string, std::pair <TextInstance, int64_t>> TextMap;

	friend TextInstance;
};