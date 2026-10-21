#include "MaterialCardWidget.h"
#include "Game/GameConfigManager.h"
#include "ButtonWidget.h"
#include "TextWidget.h"
#include "Game/GameManager.h"
#include "Game/SimulationTool.h"
#include "RenderManager.h"
#include "ShapePainterWidget.h"
#include "SizeBoxWidget.h"

void MaterialCardWidget::Init(class RenderManager* manager, int ID)
{
	auto& mat = GameConfigManager::GetGameConfigManager().Materials.GetElement(ID);
	mat.ThisMaterialCardWidget = this;

	Children.clear();

	but = AddChild <ButtonWidget>();
	background = but->AddChild <ShapePainterWidget>();
	sizeBox = background->AddChild <SizeBoxWidget>();
	text = sizeBox->AddChild <TextWidget>();
	

	

	auto BackgroundColor = ColorStr::GetAverageColor(mat.MinColor, mat.MaxColor);

	background->Color = BackgroundColor;
	background->AutoSizeAsBackground = true;

	background->ContourColor = ActiveButtonColor;
	background->ContourSize = { .x = ContourX, .y = ContourY, .IsVirtualCoordinates = true,.ratioMode = KeepRatioAxis::KeepY};

	text->Init(*manager, GameConfigManager::GetGameConfigManager().GetString(mat.Name), ColorStr::GetContrastColor(BackgroundColor));

	auto bcg = background;
	but->SetOnClick([bcg, ID]() 
		{
			static ShapePainterWidget* lastActive = nullptr;

			if (lastActive != nullptr)
				lastActive->DrawContour = false;
			lastActive = bcg;

			bcg->DrawContour = true;
			GameManager::GetGameManager().GetSimulationTool().SetMaterial(ID); 
		}
	);

	sizeBox->ModifyX = true;
	sizeBox->ModifyY = true;

	sizeBox->Size = { .x = OffsetX, .y = OffsetY, .IsVirtualCoordinates = true};
	
}

void MaterialCardWidget::SetWidth(int width)
{
	text->SetWrapping(width);
}

void MaterialCardWidget::MakeClick()
{
	if (but) but->Callback();
}
