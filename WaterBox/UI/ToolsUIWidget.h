#pragma once
#include "BaseWidget.h"

//class VerticalBoxWidget;
//class GridBoxWidget;
//class ScrollBoxWidget;
class ToolWidget;

class ToolsUIWidget : public BaseWidget
{
public:
    void Init();

protected:

    class VerticalBoxWidget* MainVerticalBox = nullptr;
    ToolWidget* PaintButton;
    ToolWidget* ThrowButton;
    class ChangeViewWidget *ChangeViewButton;
};