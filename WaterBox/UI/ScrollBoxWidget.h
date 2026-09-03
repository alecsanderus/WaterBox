#pragma once
#include "VerticalBoxWidget.h"

//class VerticalBoxWidget;
//class GridBoxWidget;
//class ScrollBoxWidget;

class ScrollBoxWidget : public VerticalBoxWidget
{


//#pragma once
//#include "BaseWidget.h"
//#include "ScreenPositionContainers.h" // Предполагается, что ScreenPoint/PrimitivePoint здесь
/*
enum class ScrollDirection {
    Vertical,
    Horizontal
};

class ScrollBoxWidget : public BaseWidget {
public:
    ScrollBoxWidget() = default;
    virtual ~ScrollBoxWidget() = default;

    // Переопределения базового виджета
    virtual bool ProcessEvent(const ScreenEvent& event) override;
    virtual void Render(RenderManager& renderer, const PrimitivePoint& Position) override;
    virtual PrimitivePoint GetSize() override;

    // Управление направлением скролла
    void SetDirection(ScrollDirection dir);
    ScrollDirection GetDirection() const;

    // Размеры контейнера скролла (задаются извне, например, в MaterialsUIWidget)
    ScreenPoint MaxPossibleSize;

protected:
    ScrollDirection Direction = ScrollDirection::Vertical;
    
    // Текущее смещение скролла в пикселях (всегда <= 0)
    int ScrollOffset = 0;

    // Вспомогательный метод для получения максимального прокручиваемого расстояния
    int GetMaxScrollOffset();
};
*/ 
};