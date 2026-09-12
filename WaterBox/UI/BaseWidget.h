#pragma once
#include "WaterBox.h"
#include "ScreenPositionContainers.h"

class RenderManager;
struct WidgetSize;
namespace in {struct InputEvent;}


class BaseWidget
{
public:

    virtual bool ProcessEvent(const in::InputEvent& event);
    virtual void Render(RenderManager& renderer, const PrimitivePoint & Position);
    virtual PrimitivePoint GetSize();
    template <typename T>
    T* AddChild ();
   

    std::vector <std::unique_ptr <BaseWidget>> Children;

    virtual ~BaseWidget() = default;

protected:
    BaseWidget* Owner = nullptr;
    virtual void OnChildAdded(BaseWidget* widget); 
};


template<typename T>
inline T* BaseWidget::AddChild()
{
    Children.emplace_back(std::make_unique <T>());
    auto Widget = Children.back().get();
    T* TypedWidget = static_cast  <T*> (Widget);
    Widget->Owner = this;
    OnChildAdded(Widget);

    return TypedWidget;
}