#pragma once
#include "BaseWidget.h"

class GameViewWidget : public BaseWidget
{
public:
	GameViewWidget();
	virtual PrimitivePoint GetSize() override;


	virtual void Render(RenderManager& renderer, const PrimitivePoint& Position) override;


protected:
    struct SDL_Renderer* Renderer = nullptr;
    struct SDL_Texture* Texture = nullptr;

    int Width;
    int Height;

    // Плоский массив пикселей.
    std::vector<uint32_t> Pixels;
};