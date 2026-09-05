#include "MaterialsUIWidget.h"

#include "RenderManager.h"
#include "VerticalBoxWidget.h"
#include "GridBoxWidget.h"
#include "ScrollBoxWidget.h"
#include "ButtonWidget.h"

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

    for (size_t i = 0; i < 2; i++)
    {
        TopGridBox->Children.emplace_back(std::make_unique<ButtonWidget>());
        auto but = static_cast<ButtonWidget*>(TopGridBox->Children.back().get());
        but->r = 90;
        but->SetOnClick([but]() { but->r = ~but->r; });
    }

    for (size_t i = 0; i < 10; i++)
    {
        BottomGridBox->Children.emplace_back(std::make_unique<ButtonWidget>());
        auto but = static_cast<ButtonWidget*>(BottomGridBox->Children.back().get());
        but->SetOnClick([but]() { but->r = ~but->r; });
    }


}

void MaterialsUIWidget::CheckSize(const PrimitivePoint& Size)
{
    TopGridBox->MaxPossibleSize = { .x = Size.x, .y = Size.y, .IsVirtualCoordinates = false};
    ScrollBox->MaxPossibleSize = { .x = Size.x, .y = Size.y - TopGridBox->GetSize().y, .IsVirtualCoordinates = false };
    BottomGridBox->MaxPossibleSize = { .x = Size.x, .y = INT32_MAX, .IsVirtualCoordinates = false };    
}