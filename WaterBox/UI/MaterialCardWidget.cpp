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
	auto& mat = GameConfigManager::GetGameConfigManager().GetMaterial(ID);

	Children.clear();

	but = AddChild <ButtonWidget>();
	background = but->AddChild <ShapePainterWidget>();
	sizeBox = background->AddChild <SizeBoxWidget>();
	text = sizeBox->AddChild <TextWidget>();
	auto button = but;

	but->SetOnClick([button, ID]() {GameManager::GetGameManager().GetSimulationTool().SetMaterial(ID); });

	BackgroundColor = ColorStr::GetAverageColor(mat.MinColor, mat.MaxColor);

	background->Color = BackgroundColor;
	background->AutoSizeAsBackground = true;

	text->Init(*manager, mat.Name, ColorStr::GetContrastColor(BackgroundColor));

	sizeBox->ModifyX = true;
	sizeBox->ModifyY = true;

	sizeBox->Size = { .x = OffsetX, .y = OffsetY, .IsVirtualCoordinates = true };
	
}

void MaterialCardWidget::SetWidth(int width)
{
	text->SetWrapping(width);
}

PrimitivePoint MaterialCardWidget::GetSize()
{
	CachedSize = BaseWidget::GetSize();
	return CachedSize;
}
