#include "MainUIWidget.h"
#include "HorizontalBoxWidget.h"
#include "VerticalBoxWidget.h"
#include "GridBoxWidget.h"
#include "GameViewWidget.h"
#include "ButtonWidget.h"
#include "RenderManager.h"

void MainUIWidget::Init()
{
	Children.clear();

	Children.emplace_back(std::make_unique <HorizontalBoxWidget> ());
	HorizontalBox = static_cast  <HorizontalBoxWidget*> (Children[0].get());

	HorizontalBox->Children.emplace_back(std::make_unique <GameViewWidget>());

	HorizontalBox->Children.emplace_back(std::make_unique <VerticalBoxWidget>());
	VerticalBox = static_cast  <VerticalBoxWidget*> (HorizontalBox->Children[1].get());

	

	HorizontalBox->Children.emplace_back(std::make_unique <GridBoxWidget>());

	GridBox = static_cast  <GridBoxWidget*> (HorizontalBox->Children[2].get());


	

	for (size_t i = 0; i < 10; i++)
	{
		GridBox->Children.emplace_back(std::make_unique <ButtonWidget>());
	}

}

void MainUIWidget::Render(RenderManager& renderer, const PrimitivePoint& Position)
{
	int siz= 0;
	
	for (int tec = 0; tec < HorizontalBox->Children.size(); tec++)
	{
		if (HorizontalBox->Children[tec].get() != GridBox)
			siz += HorizontalBox->Children[tec]->GetSize().x;
	}

	auto ScreenInfo = RenderManager::GetScreenInfo();

	GridBox->MaxPossibleSize = ScreenPoint{ .x = ScreenInfo->ScreenSizeX - siz, .y = ScreenInfo->ScreenSizeY, .IsVirtualCoordinates = false };

	BaseWidget::Render(renderer, Position);
}
