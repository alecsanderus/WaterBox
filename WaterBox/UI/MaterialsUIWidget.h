#pragma once
#include "BaseWidget.h"

//class VerticalBoxWidget;
//class GridBoxWidget;
//class ScrollBoxWidget;

class MaterialsUIWidget : public BaseWidget 
{
public:
    void Init();
    void CheckSize(const PrimitivePoint& Position);

protected:

    VerticalBoxWidget* MainVerticalBox = nullptr;
    GridBoxWidget* TopGridBox = nullptr;
    ScrollBoxWidget* ScrollBox = nullptr;
    GridBoxWidget* BottomGridBox = nullptr;
};