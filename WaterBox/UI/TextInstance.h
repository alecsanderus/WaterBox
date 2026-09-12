#pragma once
#include "ScreenPositionContainers.h"
#include "ColorContainer.h"

class RenderManager;

struct TextInstance
{
	void Init(RenderManager& manager, const std::string text, const ColorStr color);
	void Draw(RenderManager& manager, const PrimitivePoint point);
	void ChangeColor(const ColorStr color);
	void ChangeText(const std::string text);
	void SetWrapping(int width = 0);
	PrimitivePoint getSize();
	TextInstance(const TextInstance&) = delete;
	TextInstance& operator=(const TextInstance&) = delete;
	TextInstance() = default;
	~TextInstance();
private:
	struct TTF_Text* TextTtf = nullptr;
};