#include "ButtonWidget.h"
#include "RenderManager.h"

void ButtonWidget::Render(RenderManager& renderer)
{
	BaseWidget::Render(renderer);

	renderer.DrawRect();
}
