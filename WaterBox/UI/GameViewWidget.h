#pragma once
#include "BaseWidget.h"

class GameViewWidget : public BaseWidget
{
public:
	GameViewWidget();
	virtual PrimitivePoint GetSize() override;
	void UpdateTexture();

	virtual void Render(RenderManager& renderer, const PrimitivePoint& Position) override;
	virtual ~GameViewWidget();
	virtual bool ProcessEvent(const ScreenEvent& event) override;


protected:
	void CreateTexture(size_t X, size_t Y);
    struct SDL_Renderer* Renderer = nullptr;
    struct SDL_Texture* Texture = nullptr;
	   
    std::vector<uint32_t> Pixels;

	size_t SizeX = 0, SizeY = 0;
	int OldX = -1, OldY = -1;
};