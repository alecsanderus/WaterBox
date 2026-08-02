#include "BaseWidget.h"

class HorizontalBoxWidget : public BaseWidget
{
public:

	virtual void Render(RenderManager& renderer, const PrimitivePoint& Position) override;
	virtual PrimitivePoint GetSize() override;

protected:
	PrimitivePoint CachedSize = { -1,-1 };

};