#pragma once
#include "BaseWidget.h"

//class VerticalBoxWidget;
//class GridBoxWidget;
//class ScrollBoxWidget;

class ToolsUIWidget : public BaseWidget
{
public:
    void Init();

protected:

    class VerticalBoxWidget* MainVerticalBox = nullptr;
   
};