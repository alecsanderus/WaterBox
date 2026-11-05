#include "ChangeViewWidget.h"
#include "ImageWidget.h"
#include "ShapePainterWidget.h"
#include "ButtonWidget.h"
#include "Game/SimulationTool.h"
#include "Game/GameManager.h"

void ChangeViewWidget::Init(const std::string &ImageName)
{
    but = AddChild <ButtonWidget>();
    background = but->AddChild <ShapePainterWidget>();
    img = background->AddChild <ImageWidget>();
    auto* bcg = background;
    but->SetOnClick([]() {
        GameManager::GetGameManager().GetSimulationTool().IncreaseGameViewType();
        });

    background->AutoSizeAsBackground = true;
    background->DrawContour = false;
    background->Color = { 255,255,255,150 };
    background->ContourColor = { 0,0,0,255 };


    img->SetImage(ImageName);
    img->SizeAsImage = false;
    img->Size = { .x = 40, .y = 40,.IsVirtualCoordinates = true, .ratioMode = KeepRatioAxis::KeepX };
}


void ChangeViewWidget::MakeClick() const {
    but->Callback();
}
