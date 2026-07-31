#pragma once
#include "WaterBox.h"
#include "ScreenPositionContainers.h"

class RenderManager;
struct ScreenEvent;

class BaseWidget
{
public:

    virtual bool ProcessEvent(const ScreenEvent& event);
    virtual void Render(RenderManager& renderer);
    virtual ~BaseWidget();

    std::vector <BaseWidget*> Children;
    ScreenPoint Size = {300,300, true, false , 0, 0, KeepRatioAxis::KeepY};
};