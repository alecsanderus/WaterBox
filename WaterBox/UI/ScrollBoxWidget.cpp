#include "ScrollBoxWidget.h"
#include "RenderManager.h"



bool ScrollBoxWidget::ProcessEvent(const ScreenEvent& event) {
    // 1. Обработка прокрутки колёсика мыши (Затычка/Логика)
    // TODO: Интегрируйте ваши типы событий ScreenEvent (например, event.type == EventType::MouseWheel)
  /*
    if (event.IsMouseWheel()) {
        int wheelDelta = event.GetWheelDelta(); // Например, +1 или -1
        int speed = 20; // Скорость скролла в пикселях
        
        ScrollOffset += wheelDelta * speed;
        
        // Ограничиваем скролл, чтобы не выходить за рамки содержимого
        int maxOffset = GetMaxScrollOffset();
        ScrollOffset = std::clamp(ScrollOffset, maxOffset, 0);
        
        return true; // Событие перехвачено
    }
    */
    
    // 2. Передача событий дочернему элементу (единственному наследнику)
if (!Children.empty() && Children[0]) {
    // Модифицируем событие с учетом смещения скролла, если это необходимо 
    // (например, если координаты мыши в событии абсолютные, их нужно сместить на ScrollOffset)
    return Children[0]->ProcessEvent(event);
}

return false;
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
        return std::min(0, mySize.y - childSize.y);
    }
    else {
        return std::min(0, mySize.x - childSize.x);
    }
}
