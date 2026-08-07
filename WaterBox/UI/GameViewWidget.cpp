#include "GameViewWidget.h"
#include "RenderManager.h"
#include "GameSimulation.h"

GameViewWidget::GameViewWidget()
{}

PrimitivePoint GameViewWidget::GetSize()
{
	auto ScreenInfo = RenderManager::GetScreenInfo();	
	return PrimitivePoint{ScreenInfo->ScreenSizeY, ScreenInfo->ScreenSizeY};
}

void GameViewWidget::Render(RenderManager& renderer, const PrimitivePoint& Position)
{
	renderer.SetColor(50, 255, 50);
	renderer.DrawRect( PrimitiveRect (Position,GetSize()) );
}
