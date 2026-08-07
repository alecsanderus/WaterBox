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


}

void MainUIWidget::Render(RenderManager& renderer, const PrimitivePoint& Position)
{
	
	auto ScreenInfo = RenderManager::GetScreenInfo();

	GridBox->MaxPossibleSize = ScreenPoint{ .x = ScreenInfo->ScreenSizeX - HorizontalBox->GetSize().x + GridBox->GetSize().x,
		.y = ScreenInfo->ScreenSizeY, .IsVirtualCoordinates = false};

	BaseWidget::Render(renderer, Position);
}
