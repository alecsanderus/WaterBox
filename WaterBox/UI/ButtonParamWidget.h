#pragma once
#include "ButtonWidget.h"


template<typename T>
class ButtonParamWidget : public ButtonWidget
{
public:
	using ClickCallbackPro = std::function<void(const T&)>;

	virtual void SetOnClick(ClickCallback callback) override{
		OnClickPro = callback;
	}

	void SetValue(const T& value) {
		Value = value;
	};

	
protected:

virtual bool Callback() override
	{
		if (!OnClickPro)
			return false;

		OnClickPro(Value);
		return true;
	}

	T Value;
	ClickCallbackPro OnClickPro;
};

