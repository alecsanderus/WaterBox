#include "ToolsUIWidget.h"
#include "VerticalBoxWidget.h"
#include "ToolWidget.h"
#include "ChangeViewWidget.h"

void ToolsUIWidget::Init()
{
	MainVerticalBox = AddChild <VerticalBoxWidget>();



	PaintButton = MainVerticalBox->AddChild <ToolWidget>();
	ThrowButton = MainVerticalBox->AddChild <ToolWidget>();
	ChangeViewButton = MainVerticalBox->AddChild <ChangeViewWidget>();

	PaintButton->Init(0, "Tool_Brush.png");
	ThrowButton->Init(1, "Tool_Brush.png");
	ChangeViewButton->Init("Tool_Brush.png");

	PaintButton->MakeClick();
}
