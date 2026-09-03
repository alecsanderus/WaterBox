#include "TabsBoxWidget.h"


bool TabsBoxWidget::ProcessEvent(const ScreenEvent& event) {
    if (TecPosition >= 0 && TecPosition < static_cast<int>(Children.size())) {
        if (Children[TecPosition]->ProcessEvent(event)) {
            return true;
        }
    }
    return false;
}

void TabsBoxWidget::Render(RenderManager& renderer, const PrimitivePoint& Position) {
    if (TecPosition >= 0 && TecPosition < static_cast<int>(Children.size())) {
        Children[TecPosition]->Render(renderer, Position);
    }
}

PrimitivePoint TabsBoxWidget::GetSize() {
    if (TecPosition >= 0 && TecPosition < static_cast<int>(Children.size())) {
        return Children[TecPosition]->GetSize();
    }
    return PrimitivePoint(0, 0);
}

void TabsBoxWidget::SetPosition(int pos) {
    if (pos >= 0 && pos < static_cast<int>(Children.size())) {
        TecPosition = pos;
    }
}

int TabsBoxWidget::GetPosition() {
    return TecPosition;
}