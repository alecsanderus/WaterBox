#pragma once
#include "BaseWidget.h"

class RenderManager;

class ButtonWidget : public BaseWidget
{
public:

	virtual void Render(RenderManager& renderer) override;

};