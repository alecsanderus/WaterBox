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
    class ScrollBoxWidget* ScrollBox = nullptr;
    class GridBoxWidget* BottomGridBox = nullptr;

    std::vector <class MaterialCardWidget*> MaterialWidgets;
};