#include "ScrollBoxWidget.h"
//
//include "ScrollBoxWidget.h"
//#include "RenderManager.h"
//#include <SDL.h> // Для SDL_Rect и SDL_SetRenderClipRect
//#include <algorithm>

/*
  /*
bool ScrollBoxWidget::ProcessEvent(const ScreenEvent& event) {
    // 1. Обработка прокрутки колёсика мыши (Затычка/Логика)
    // TODO: Интегрируйте ваши типы событий ScreenEvent (например, event.type == EventType::MouseWheel)
  
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
    /*
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

    SDL_Renderer* sdlRenderer = renderer.GetSDLRenderer(); // Метод получения SDL_Renderer* из вашего менеджера
    PrimitivePoint mySize = GetSize();

    // 1. Сохраняем текущий ClipRect, чтобы восстановить его в конце
    SDL_Rect oldClipRect;
    SDL_bool hasOldClip = SDL_RenderGetClipRect(sdlRenderer, &oldClipRect);

    // 2. Устанавливаем новый ClipRect по границам самого ScrollBoxWidget
    SDL_Rect newClipRect = {
        .x = Position.x,
        .y = Position.y,
        .w = mySize.x,
        .h = mySize.y
    };
    SDL_RenderSetClipRect(sdlRenderer, &newClipRect);

    // 3. Вычисляем позицию рендера дочернего элемента с учетом ScrollOffset
    PrimitivePoint childPosition = Position;
    if (Direction == ScrollDirection::Vertical) {
        childPosition.y += ScrollOffset;
    }
    else {
        childPosition.x += ScrollOffset;
    }

    // 4. Рендерим дочерний виджет
    Children[0]->Render(renderer, childPosition);

    // 5. Восстанавливаем старый ClipRect
    SDL_RenderSetClipRect(sdlRenderer, hasOldClip ? &oldClipRect : nullptr);
}

PrimitivePoint ScrollBoxWidget::GetSize() {
    // Возвращает размер, заданный через MaxPossibleSize
    return MaxPossibleSize.GetNormalizedPoint();
}

void ScrollBoxWidget::SetDirection(ScrollDirection dir) {
    if (Direction != dir) {
        Direction = dir;
        ScrollOffset = 0; // Сбрасываем скролл при смене ориентации
    }
}

ScrollDirection ScrollBoxWidget::GetDirection() const {
    return Direction;
}

int ScrollBoxWidget::GetMaxScrollOffset() {
    if (Children.empty() || !Children[0]) return 0;

    PrimitivePoint mySize = GetSize();
    PrimitivePoint childSize = Children[0]->GetSize();

    if (Direction == ScrollDirection::Vertical) {
        // Если контент меньше контейнера, скроллить нельзя (0)
        return std::min(0, mySize.y - childSize.y);
    }
    else {
        return std::min(0, mySize.x - childSize.x);
    }
}
*/