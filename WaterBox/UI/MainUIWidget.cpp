#include "MainUIWidget.h"
#include "HorizontalBoxWidget.h"
#include "MaterialsUIWidget.h"
#include "ToolsUIWidget.h"
#include "GameViewWidget.h"
#include "RenderManager.h"
#include "InputEvent.h"

void MainUIWidget::Init(RenderManager* renderer)
{
	Children.clear();

	MainHorizontalBox = AddChild<HorizontalBoxWidget> ();

	MainHorizontalBox->AddChild<GameViewWidget>();
	
	MainToolsBox = MainHorizontalBox->AddChild <ToolsUIWidget>();
	
	MainMaterialsWidget = MainHorizontalBox->AddChild<MaterialsUIWidget>();
	MainMaterialsWidget->Init(renderer);
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
