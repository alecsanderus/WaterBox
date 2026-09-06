#pragma once
#include "BaseWidget.h"

class MainUIWidget : public BaseWidget
{
public:
	void Init();
	virtual void Render(RenderManager& renderer, const PrimitivePoint& Position) override;

	virtual bool ProcessEvent(const in::InputEvent& event) override;

protected:

	class HorizontalBoxWidget* MainHorizontalBox = nullptr;

	class ToolsUIWidget* MainToolsBox = nullptr;
	class MaterialsUIWidget* MainMaterialsWidget = nullptr;	
};