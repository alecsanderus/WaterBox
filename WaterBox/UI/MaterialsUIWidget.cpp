#include "MaterialsUIWidget.h"

#include "RenderManager.h"
#include "VerticalBoxWidget.h"
#include "GridBoxWidget.h"
#include "ScrollBoxWidget.h"
#include "ButtonWidget.h"
#include "Game/GameConfigManager.h"
#include "Game/GameManager.h"
#include "Game/SimulationTool.h"
#include "MaterialCardWidget.h"

void MaterialsUIWidget::Init(RenderManager* rend_manager)
{
    Children.clear();

    MainVerticalBox = AddChild<VerticalBoxWidget>();
    TopGridBox = MainVerticalBox->AddChild<GridBoxWidget>();
    ScrollBox = MainVerticalBox->AddChild<ScrollBoxWidget>();
    BottomGridBox = ScrollBox->AddChild<GridBoxWidget>();

    auto& manager = GameConfigManager::GetGameConfigManager();
    auto& Materials = manager.GetMaterials();
    auto& Categories = manager.GetCategories();


    for (size_t i = 0; i < 2; i++)
    {
        auto but = TopGridBox->AddChild<ButtonWidget>();
      //  but->r = 90;
       // but->SetOnClick([but]() { but->r = ~but->r; });
    }

    MaterialWidgets.reserve(Materials.size());

    for (size_t i = 0; i < Materials.size(); i++)
    {
        
        auto but = BottomGridBox->AddChild<MaterialCardWidget>();
        int SigmaID = Materials[i].ID;
        but->Init(rend_manager, SigmaID);
        MaterialWidgets.push_back(but);
    }


}

void MaterialsUIWidget::CheckSize(const PrimitivePoint& Size)
{
    TopGridBox->MaxPossibleSize = { .x = Size.x, .y = Size.y, .IsVirtualCoordinates = false};
    auto sizY = Size.y - TopGridBox->GetSize().y;
    ScrollBox->MaxPossibleSize = { .x = Size.x, .y = sizY, .IsVirtualCoordinates = false };
    BottomGridBox->MaxPossibleSize = { .x = Size.x, .y = INT32_MAX, .IsVirtualCoordinates = false };

    for (auto i : MaterialWidgets)
    {
        i->SetWidth(sizY);
    }
}