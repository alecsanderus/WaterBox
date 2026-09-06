#pragma once
#include "BaseWidget.h"

//class VerticalBoxWidget;
//class GridBoxWidget;
//class ScrollBoxWidget;

class ScrollBoxWidget : public BaseWidget
{
public:

    enum class ScrollDirection : uint8_t{Vertical, Horizontal};

    virtual bool ProcessEvent(const in::InputEvent& event) override;
    virtual void Render(RenderManager& renderer, const PrimitivePoint& Position) override;
    virtual PrimitivePoint GetSize() override;

    ScrollDirection Direction = ScrollDirection::Vertical;

    ScreenPoint MaxPossibleSize;

protected:
    int ScrollOffset = 0;

    int GetMaxScrollOffset();
};