#include "TextInstance.h"
#include "RenderManager.h"
#include "SDL3_ttf/SDL_ttf.h"



void TextInstance::Init(RenderManager& manager, const std::string text, const ColorStr color)
{
    TextTtf = TTF_CreateText(manager.TextEngine, manager.TextFont, text.c_str(), 0);
    TTF_SetTextColor(TextTtf, color.r, color.g, color.b, color.a);
}

void TextInstance::Draw(RenderManager& manager, const PrimitivePoint point)
{
    TTF_DrawRendererText(TextTtf, point.x, point.y);
}

void TextInstance::ChangeColor(const ColorStr color)
{
    TTF_SetTextColor(TextTtf, color.r, color.g, color.b, color.a);
}
void TextInstance::ChangeText(const std::string text)
{
    TTF_SetTextString(TextTtf, text.c_str(), 0);
}

void TextInstance::SetWrapping(int width)
{
    TTF_SetTextWrapWidth(TextTtf, width);
}

PrimitivePoint TextInstance::getSize()
{
    PrimitivePoint res;
    TTF_GetTextSize(TextTtf, &res.x, &res.y);
    return res;
}

TextInstance::~TextInstance()
{
    if (TextTtf) TTF_DestroyText(TextTtf);
}
