#pragma once
#include "BaseWidget.h"
#include "TextInstance.h"

class TextWidget : public BaseWidget, protected TextInstance
{
public:
	
	virtual void Render(RenderManager& renderer, const PrimitivePoint& Position) override;
	virtual PrimitivePoint GetSize() override;
	using TextInstance::Init;
	using TextInstance::ChangeColor;
	using TextInstance::ChangeText;
	using TextInstance::SetWrapping;

};
