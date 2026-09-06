#pragma once

#include "BaseWidget.h"


class TabsBoxWidget : public BaseWidget
{
public:

    virtual bool ProcessEvent(const in::InputEvent& event) override;
    virtual void Render(RenderManager& renderer, const PrimitivePoint& Position) override;
    virtual PrimitivePoint GetSize() override;

    void SetPosition(int pos);
    int GetPosition();
protected:
    int TecPosition = 0;
   

};