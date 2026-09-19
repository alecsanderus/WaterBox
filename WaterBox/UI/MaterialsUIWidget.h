#pragma once
#include "BaseWidget.h"

//class VerticalBoxWidget;
//class GridBoxWidget;
//class ScrollBoxWidget;

class MaterialsUIWidget : public BaseWidget 
{
public:
    void Init(RenderManager* manager);
    void CheckSize(const PrimitivePoint& Size);

protected:

    class VerticalBoxWidget* MainVerticalBox = nullptr;
    class GridBoxWidget* TopGridBox = nullptr;
    class TabsBoxWidget* TabsBox = nullptr;
    class ShapePainterWidget* Spacer;

    std::vector <class MaterialCardWidget*> MaterialWidgets;
    std::vector <class ScrollBoxWidget*> ScrollsWidgets;
    std::vector <class GridBoxWidget*> GridsWidgets;

    ScreenPoint SpacerSize = {.x = 1000, .y = 22, .IsVirtualCoordinates = true };
    ScreenPoint SpacerDrawSize = { .x = 0, .y = 16, .IsVirtualCoordinates = true };

    PrimitivePoint LastSize = { 1,1 };

};