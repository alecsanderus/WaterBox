#include "ScrollBoxWidget.h"
#include "RenderManager.h"
#include "InputEvent.h"



bool ScrollBoxWidget::ProcessEvent(const in::InputEvent& event) {
    if (event.isMouseScroll())
    {
        ScrollOffset += std::get <in::MouseScrollEvent>(event.data).deltaY * ScreenPoint{ .x = 30, .IsVirtualCoordinates = true }.GetNormalizedPoint().x;

        int maxOffset = GetMaxScrollOffset();
        ScrollOffset = std::clamp(ScrollOffset, -maxOffset, 0);
        return 1;
    } 

    return BaseWidget::ProcessEvent(event);
}




void ScrollBoxWidget::Render(RenderManager& renderer, const PrimitivePoint& Position) {
    if (Children.empty() || !Children[0]) return;

  
    PrimitivePoint mySize = GetSize();

    PrimitiveRect oldClipRect;
    renderer.GetClipRect(oldClipRect);


    PrimitiveRect newClipRect = {
        .pos = Position,
        .size = mySize       
    };
    renderer.SetClipRect(&newClipRect);  

    PrimitivePoint childPosition = Position;
    if (Direction == ScrollDirection::Vertical) {
        childPosition.y += ScrollOffset;
    }
    else {
        childPosition.x += ScrollOffset;
    }

    Children[0]->Render(renderer, childPosition);

    renderer.SetClipRect(&oldClipRect);
}



PrimitivePoint ScrollBoxWidget::GetSize() {
    return MaxPossibleSize.GetNormalizedPoint();
}



int ScrollBoxWidget::GetMaxScrollOffset() {
    if (Children.empty() || !Children[0]) return 0;

    PrimitivePoint mySize = GetSize();
    PrimitivePoint childSize = Children[0]->GetSize();

    if (Direction == ScrollDirection::Vertical) {
        int res = std::max(0, childSize.y - mySize.y);
        if (res > 0) res += mySize.y * 0.2;
        return  res;
    }
    else {
        int res = std::max(0, childSize.x - mySize.x);
        if (res > 0) res += mySize.x * 0.2;
        return res;
    }
}
