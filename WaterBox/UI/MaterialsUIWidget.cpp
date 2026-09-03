#include "MaterialsUIWidget.h"

#include "RenderManager.h"
#include "VerticalBoxWidget.h"
#include "GridBoxWidget.h"
#include "ScrollBoxWidget.h"

void MaterialsUIWidget::Init()
{
    Children.clear();

    Children.emplace_back(std::make_unique<VerticalBoxWidget>());
    MainVerticalBox = static_cast<VerticalBoxWidget*>(Children.back().get());

    MainVerticalBox->Children.emplace_back(std::make_unique<GridBoxWidget>());
    TopGridBox = static_cast<GridBoxWidget*>(MainVerticalBox->Children.back().get());

    MainVerticalBox->Children.emplace_back(std::make_unique<ScrollBoxWidget>());
    ScrollBox = static_cast<ScrollBoxWidget*>(MainVerticalBox->Children.back().get());

    ScrollBox->Children.emplace_back(std::make_unique<GridBoxWidget>());
    BottomGridBox = static_cast<GridBoxWidget*>(ScrollBox->Children.back().get());
}

void MaterialsUIWidget::CheckSize(const PrimitivePoint& Position)
{
    // Получаем информацию об экране для адаптивного расчета размеров
    auto ScreenInfo = RenderManager::GetScreenInfo();

    // Пример логики адаптации размеров (настройте формулы под ваши нужды):
    if (MainVerticalBox && TopGridBox && ScrollBox)
    {
        // Вычисляем доступную высоту для ScrollBox (Вся высота экрана минус то, что занял верхний грид)
        int availableHeight = ScreenInfo->ScreenSizeY - TopGridBox->GetSize().y;

        // Ограничиваем максимальный размер скролл-бокса
        //ScrollBox->MaxPossibleSize = ScreenPoint{
        //    .x = ScreenInfo->ScreenSizeX, // или нужная вам ширина
        //    .y = std::max(0, availableHeight),
        //    .IsVirtualCoordinates = false
        //};
    }

    // Вызываем базовый рендер, который отрисует всю иерархию (MainVerticalBox и его Children)
  //  BaseWidget::Render(renderer, Position);
}