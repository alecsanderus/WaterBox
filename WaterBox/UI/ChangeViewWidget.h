#pragma once
#include "BaseWidget.h"


class ChangeViewWidget : public BaseWidget
{
public:
    void Init(const std::string &ImageName);


    int OffsetX = 15, OffsetY = 10;
    //	ColorStr ActiveButtonColor = { 93, 232, 230, 255 };
    int ContourX = 8, ContourY = 6;

    void MakeClick() const;

protected:
    class ImageWidget* img = nullptr;
    class ButtonWidget* but = nullptr;
    class ShapePainterWidget* background = nullptr;
    class SizeBoxWidget* sizeBox = nullptr;

    PrimitivePoint CachedSize = { 0,0 };

};


