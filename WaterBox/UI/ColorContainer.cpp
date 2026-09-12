#include "ColorContainer.h"
#include <random>

ColorStr ColorStr::GetRandomColor(const ColorStr& a, const ColorStr& b, const bool KeepProportions)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    auto [minR, maxR] = std::minmax(a.r, b.r);
    auto [minG, maxG] = std::minmax(a.g, b.g);
    auto [minB, maxB] = std::minmax(a.b, b.b);

    if (KeepProportions)
    {
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);
        float factor = dist(gen);

        uint8_t finalR = static_cast<uint8_t>(minR + factor * (maxR - minR));
        uint8_t finalG = static_cast<uint8_t>(minG + factor * (maxG - minG));
        uint8_t finalB = static_cast<uint8_t>(minB + factor * (maxB - minB));

        return ColorStr{ finalR, finalG, finalB };
    }
    else
    {
        std::uniform_int_distribution<int> distR(minR, maxR);
        std::uniform_int_distribution<int> distG(minG, maxG);
        std::uniform_int_distribution<int> distB(minB, maxB);

        return ColorStr{
            static_cast<uint8_t>(distR(gen)),
            static_cast<uint8_t>(distG(gen)),
            static_cast<uint8_t>(distB(gen))
        };
    }
}


ColorStr ColorStr::GetAverageColor(const ColorStr& c1, const ColorStr& c2)
{
    return ColorStr{
        .r = static_cast<uint8_t>((c1.r + c2.r) / 2),
        .g = static_cast<uint8_t>((c1.g + c2.g) / 2),
        .b = static_cast<uint8_t>((c1.b + c2.b) / 2),
        .a = static_cast<uint8_t>((c1.a + c2.a) / 2)
    };
}

ColorStr ColorStr::GetContrastColor(const ColorStr& background) {
    double brightness = 0.299 * background.r + 0.587 * background.g + 0.114 * background.b;

    if (brightness < 128) 
        return ColorStr{ 255, 255, 255, 255 };
    
    else 
        return ColorStr{ 0, 0, 0, 255 };
    
}