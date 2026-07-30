#pragma once
#include "WaterBox.h"

class RenderManager;
struct ScreenEvent;

class BaseWidget
{
public:

    virtual bool ProcessEvent(const ScreenEvent& event);
    virtual void Render(RenderManager& renderer);
    virtual ~BaseWidget();

    std::vector <BaseWidget*> Children;
};