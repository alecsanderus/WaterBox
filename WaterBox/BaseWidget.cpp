#include "BaseWidget.h"
#include "RenderManager.h"

bool BaseWidget::ProcessEvent(const ScreenEvent& event)
{
	for (auto& tec : Children)
	{
		if (tec->ProcessEvent(event))
			return 1;
	}
}

void BaseWidget::Render(RenderManager& renderer)
{
	for (auto& tec : Children)
	{
		tec->Render(renderer);
	}
}

BaseWidget::~BaseWidget()
{
	for (auto& tec : Children)
	{
		delete tec;
	}
	Children.clear();
}
