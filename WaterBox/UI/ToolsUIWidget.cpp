#include "ToolsUIWidget.h"
#include "VerticalBoxWidget.h"
#include "ToolWidget.h"

void ToolsUIWidget::Init()
{
	MainVerticalBox = AddChild <VerticalBoxWidget>();



	PaintButton = MainVerticalBox->AddChild <ToolWidget>();
	ThrowButton = MainVerticalBox->AddChild <ToolWidget>();

	PaintButton->Init(0, "Tool_Brush.png");
	ThrowButton->Init(1, "Tool_Brush.png");	

	PaintButton->MakeClick();
}
