#include "MainUIWidget.h"
#include "HorizontalBoxWidget.h"
#include "MaterialsUIWidget.h"
#include "ToolsUIWidget.h"
#include "GameViewWidget.h"
#include "RenderManager.h"
#include "InputEvent.h"

void MainUIWidget::Init()
{
	Children.clear();

	Children.emplace_back(std::make_unique <HorizontalBoxWidget> ());
	MainHorizontalBox = static_cast  <HorizontalBoxWidget*> (Children[0].get());

	MainHorizontalBox->Children.emplace_back(std::make_unique <GameViewWidget>());


	MainHorizontalBox->Children.emplace_back(std::make_unique <ToolsUIWidget>());
	MainToolsBox = static_cast  <ToolsUIWidget*> (MainHorizontalBox->Children[1].get());
	

	MainHorizontalBox->Children.emplace_back(std::make_unique <MaterialsUIWidget>());
	MainMaterialsWidget = static_cast  <MaterialsUIWidget*> (MainHorizontalBox->Children[2].get());
	MainMaterialsWidget->Init();
}




void MainUIWidget::Render(RenderManager& renderer, const PrimitivePoint& Position)
{
	
	auto ScreenInfo = RenderManager::GetScreenInfo();

	auto MaterialsSize = ScreenPoint{ .x = ScreenInfo->ScreenSizeX - MainHorizontalBox->GetSize().x + MainMaterialsWidget->GetSize().x,
		.y = ScreenInfo->ScreenSizeY, .IsVirtualCoordinates = false};

	MainMaterialsWidget->CheckSize(MaterialsSize);
	BaseWidget::Render(renderer, Position);
}




bool MainUIWidget::ProcessEvent(const in::InputEvent& event)
{
	auto& [pointer, type] = RenderManager::GetLockEventState();
	if (type != EventFocusType::NO && pointer != nullptr)
	{
		bool state = pointer->ProcessEvent(event);



		if (event.isMouseButton() && type == EventFocusType::Lock_AutoUnlock &&
			std::get <in::MouseButtonEvent>(event.data).action == in::InputAction::Release)

			type = EventFocusType::NO;

		if (type == EventFocusType::NO)
			pointer = nullptr;



		return state;
	}
	else
	{
		for (auto& tec : Children)
		{
			if (tec->ProcessEvent(event))
				return true;
		}
	}

	return false;
}
