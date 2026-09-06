#include "BaseWidget.h"
#include "RenderManager.h"

bool BaseWidget::ProcessEvent(const in::InputEvent& event)
{
	for (auto& tec : Children)
	{
		if (tec->ProcessEvent(event))
			return 1;
	}
	return 0;
}

void BaseWidget::Render(RenderManager& renderer, const PrimitivePoint& Position)
{
	for (auto& tec : Children)
	{
		tec->Render(renderer, Position);
	}
}

PrimitivePoint BaseWidget::GetSize()
{
	return PrimitivePoint(0,0);
}
