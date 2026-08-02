#include "MainUIWidget.h"
#include "HorizontalBoxWidget.h"
#include "GameViewWidget.h"
#include "ButtonWidget.h"

void MainUIWidget::Init()
{
	Children.clear();

	Children.push_back(std::make_unique <HorizontalBoxWidget> ());
	auto& HorizontalBox = *Children[0];

	HorizontalBox.Children.push_back(std::make_unique <GameViewWidget>());
	HorizontalBox.Children.push_back(std::make_unique <ButtonWidget>());
}
