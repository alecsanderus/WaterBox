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

    virtual ~BaseWidget();

    std::vector <BaseWidget*> Children;
    ScreenPoint Size = {300,300, true, false , 0, 0, KeepRatioAxis::KeepY};
};