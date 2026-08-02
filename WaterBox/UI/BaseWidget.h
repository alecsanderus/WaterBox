#pragma once
#include "WaterBox.h"
#include "ScreenPositionContainers.h"

class RenderManager;
struct ScreenEvent;
struct WidgetSize;

class BaseWidget
{
public:

    virtual bool ProcessEvent(const ScreenEvent& event);
    virtual void Render(RenderManager& renderer, const PrimitivePoint & Position);
    virtual PrimitivePoint GetSize();
   

    std::vector <std::unique_ptr <BaseWidget>> Children;

    virtual ~BaseWidget() = default;
};