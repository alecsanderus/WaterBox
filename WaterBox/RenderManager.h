#pragma once
#include "UI/MainUIWidget.h"
#include <optional>
#include "UI/ScreenPositionContainers.h"
#include "UI/ColorContainer.h"


union SDL_Event;
namespace in { struct InputEvent; }
class RenderManager;





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

	void FastDrawText(const std::string& text, ColorStr color, PrimitivePoint point);



private:
	struct SDL_Window* window = nullptr;
	struct SDL_Renderer* renderer = nullptr;
	bool NeedToDestroyWindow = false;
	void UpdateScreenInfo();
	

	struct TTF_TextEngine* TextEngine = nullptr;
	struct TTF_Font* TextFont = nullptr;
	void CheckTextMap();







	struct StringIntPairHash {
		std::size_t operator()(const std::pair<std::string, uint32_t>& p) const {
			std::size_t h1 = std::hash<std::string>{}(p.first);
			std::size_t h2 = std::hash<uint32_t>{}(p.second);
			return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
		}
	};

	std::unordered_map <std::pair <std::string, uint32_t>, std::pair <struct TextInstance, int64_t>, StringIntPairHash> TextMap;

	friend struct TextInstance;
};