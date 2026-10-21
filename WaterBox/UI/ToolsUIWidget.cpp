#include "ToolsUIWidget.h"
#include "VerticalBoxWidget.h"
#include "ImageWidget.h"
#include "ShapePainterWidget.h"
#include "ButtonWidget.h"

void ToolsUIWidget::Init()
{
	MainVerticalBox = AddChild <VerticalBoxWidget>();
	auto but = MainVerticalBox->AddChild <ButtonWidget>();
	auto cn = but->AddChild <ShapePainterWidget>();
	auto im = cn->AddChild <ImageWidget>();

	but->SetOnClick([]() {LOG_INFO("Pepe shnene watafa"); });

	cn->AutoSizeAsBackground = true;
	cn->DrawContour = true;
	cn->Color = { 255,255,255,150 };
	cn->ContourColor = { 0,0,0,255 };


	im->SetImage("Tool_Brush.png");
	im->SizeAsImage = false;
	im->Size = { .x = 40, .y = 40,.IsVirtualCoordinates = true, .ratioMode = KeepRatioAxis::KeepX };
}
