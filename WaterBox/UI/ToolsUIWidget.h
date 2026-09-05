#pragma once
#include "BaseWidget.h"

//class VerticalBoxWidget;
//class GridBoxWidget;
//class ScrollBoxWidget;

class ToolsUIWidget : public BaseWidget
{
public:
    void Init();
    void CheckSize(const PrimitivePoint& Position);

protected:

    class VerticalBoxWidget* MainVerticalBox = nullptr;
    class GridBoxWidget* TopGridBox = nullptr;
    class ScrollBoxWidget* ScrollBox = nullptr;
    class GridBoxWidget* BottomGridBox = nullptr;
};