#include "MaterialCategoryWidget.h"
#include "Game/GameConfigManager.h"
#include "ButtonWidget.h"
#include "TextWidget.h"
#include "Game/GameManager.h"
#include "Game/SimulationTool.h"
#include "RenderManager.h"
#include "ShapePainterWidget.h"
#include "SizeBoxWidget.h"
#include "TabsBoxWidget.h"

void MaterialCategoryWidget::Init(RenderManager* manager, int ID, TabsBoxWidget* tabs, int TabsID)
{
	auto& cat = GameConfigManager::GetGameConfigManager().GetCategory(ID);

	Children.clear();

	but = AddChild <ButtonWidget>();
	background = but->AddChild <ShapePainterWidget>();
	sizeBox = background->AddChild <SizeBoxWidget>();
	text = sizeBox->AddChild <TextWidget>();





	background->Color = cat.Color;
	background->AutoSizeAsBackground = true;

	background->ContourColor = ActiveButtonColor;
	background->ContourSize = { .x = ContourX, .y = ContourY, .IsVirtualCoordinates = true,.ratioMode = KeepRatioAxis::KeepY };

	text->Init(*manager, GameConfigManager::GetGameConfigManager().GetString(cat.Name), ColorStr::GetContrastColor(cat.Color));

	auto bcg = background;
	but->SetOnClick([bcg, TabsID, tabs]() 
		{
			static ShapePainterWidget* lastActive = nullptr;

			if (lastActive != nullptr)
				lastActive->DrawContour = false;
			lastActive = bcg;

			bcg->DrawContour = true;

			tabs->SetPosition(TabsID); 

		}
	);

	sizeBox->ModifyX = true;
	sizeBox->ModifyY = true;

	sizeBox->Size = { .x = OffsetX, .y = OffsetY, .IsVirtualCoordinates = true };

}

void MaterialCategoryWidget::SetWidth(int width)
{
	text->SetWrapping(width);
}

void MaterialCategoryWidget::MakeClick()
{
	if (but) but->Callback();
}

