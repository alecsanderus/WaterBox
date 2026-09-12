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
	PrimitivePoint max = { 0,0 };
	for (auto& el : Children)
	{
		auto tec = el->GetSize();
		max.x = std::max(max.x, tec.x);
		max.y = std::max(max.y, tec.y);

	}
	return max;
}

void BaseWidget::OnChildAdded(BaseWidget* widget)
{
}


