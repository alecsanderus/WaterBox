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
#include "TabsBoxWidget.h"
#include "Game/GameMaterial.h"
#include <unordered_set>
#include "MaterialCategoryWidget.h"
#include "SizeBoxWidget.h"
#include "ShapePainterWidget.h"

void MaterialsUIWidget::Init(RenderManager* rend_manager)
{
    Children.clear();
    MaterialWidgets.clear();

    MainVerticalBox = AddChild<VerticalBoxWidget>();
    TopGridBox = MainVerticalBox->AddChild<GridBoxWidget>();
    Spacer = MainVerticalBox->AddChild <ShapePainterWidget>();
    TabsBox = MainVerticalBox->AddChild<TabsBoxWidget>();

    
    Spacer->Size = SpacerSize;
    Spacer->Color = { 255,150,150,255 };
    Spacer->ContourColor = { 0,0,255,0};
    Spacer->DrawContour = true;
    Spacer->ContourSize = SpacerDrawSize;




    auto& manager = GameConfigManager::GetGameConfigManager();
    auto& Materials = manager.GetMaterials();
    auto& Categories = manager.GetCategories();

    std::vector <const GameMaterial*> MaterialsList;

    for (auto& i : Materials)
        if (i.CanBeShown == 1)        
            MaterialsList.push_back(&i);

        
    std::sort(MaterialsList.begin(), MaterialsList.end(), [](const GameMaterial* a, const GameMaterial* b) {
        if (a->CategoryID != b->CategoryID) {
            return a->CategoryID < b->CategoryID;
        }
        return a->ShowPriority > b->ShowPriority;
        });


    std::unordered_map<int, GridBoxWidget*> CategoryScrollBoxes;


    bool First = true;
    for (size_t i = 0; i < Categories.size(); i++) {
        int CategoryID = Categories[i].ID;

        auto* CategoryScrollBox = TabsBox->AddChild<ScrollBoxWidget>();

        auto ScrollBox = CategoryScrollBox->AddChild<ScrollBoxWidget>();
        auto BottomGridBox = ScrollBox->AddChild<GridBoxWidget>();

        ScrollsWidgets.push_back(ScrollBox);
        GridsWidgets.push_back(BottomGridBox);

        CategoryScrollBoxes[CategoryID] = BottomGridBox;
      
        auto* CategoryButton = TopGridBox->AddChild<MaterialCategoryWidget>();
        CategoryButton->Init(rend_manager, CategoryID, TabsBox, i);
        if (First) { CategoryButton->MakeClick(); First = false;}
    }

    MaterialWidgets.reserve(Materials.size());
    First = true;

    for (const auto* mat : MaterialsList) {
        auto it = CategoryScrollBoxes.find(mat->CategoryID);
        if (it == CategoryScrollBoxes.end()) continue;

        auto box = it->second;

        auto* MaterialCard = box->AddChild<MaterialCardWidget>();
        MaterialCard->Init(rend_manager, mat->ID);

        MaterialWidgets.push_back(MaterialCard);

        if (First) {MaterialCard->MakeClick(); First = false; }

    }      

    TabsBox->SetPosition(0);

}

void MaterialsUIWidget::CheckSize(const PrimitivePoint& Size)
{
    if (LastSize == Size) return;
    else LastSize = Size;

    TopGridBox->MaxPossibleSize = { .x = Size.x, .y = Size.y, .IsVirtualCoordinates = false};
    auto sizY = Size.y - TopGridBox->GetSize().y;
    ScreenPoint Scrolls = { .x = Size.x, .y = sizY, .IsVirtualCoordinates = false };
    ScreenPoint Grids = { .x = Size.x, .y = INT32_MAX, .IsVirtualCoordinates = false };

    for (auto i : GridsWidgets)
        i->MaxPossibleSize = Grids;

    for (auto i : ScrollsWidgets)
        i->MaxPossibleSize = Scrolls;
   
    for (auto i : MaterialWidgets)    
        i->SetWidth(sizY);
    
}