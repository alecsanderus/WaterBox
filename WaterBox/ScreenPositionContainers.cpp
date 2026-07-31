#include "ScreenPositionContainers.h"
#include "RenderManager.h"


std::pair<int, int> ScreenPoint::GetNormalizedPoint() const
{
	const ScreenInfoStruct& ScreenInfo = *RenderManager::GetScreenInfo();

	int NewX = x;
	int NewY = y;

	if (IsVirtualCoordinates)
	{
		NewX = NewX * ScreenInfo.ScreenSizeX / DefaultResolutionX;
		NewY = NewY * ScreenInfo.ScreenSizeY / DefaultResolutionY;
		
	}

	float TargetRatio = static_cast<float>(x) / y;

	if (ratioMode == KeepRatioAxis::KeepX) {
		NewY = static_cast<int>(NewX / TargetRatio);
	}
	else if (ratioMode == KeepRatioAxis::KeepY) {
		NewX = static_cast<int>(NewY * TargetRatio);
	}

	if (UseAnchor)
	{
		if (AnchorX == 1) NewX += ScreenInfo.ScreenSizeX / 2;
		if (AnchorX == 2) NewX += ScreenInfo.ScreenSizeX;

		if (AnchorY == 1) NewY += ScreenInfo.ScreenSizeY / 2;
		if (AnchorY == 2) NewY += ScreenInfo.ScreenSizeY;
	}

	return {NewX, NewY};

}

PrimitiveRect ScreenRect::GetNormalizedRect() const
{	
	return { pos.GetNormalizedPoint(), size.GetNormalizedPoint() };
}

PrimitivePoint::PrimitivePoint(const ScreenPoint& Source)
{
	auto [Nx, Ny] = Source.GetNormalizedPoint();
	x = Nx; y = Ny;
}

PrimitivePoint::PrimitivePoint(std::pair<int, int> pair)
{
	x = pair.first; y = pair.second;
}

































PrimitivePoint operator+(const PrimitivePoint& a, const PrimitivePoint& b)
{
	PrimitivePoint ans = a;
	ans.x += b.x;
	ans.y += b.y;

	return ans;
}

PrimitivePoint operator+(const PrimitivePoint& a, const ScreenPoint& b)
{
	return a + PrimitivePoint (b.GetNormalizedPoint());
}

PrimitivePoint operator-(const PrimitivePoint& a, const PrimitivePoint& b)
{
	PrimitivePoint ans = a;
	ans.x -= b.x;
	ans.y -= b.y;

	return ans;
}

PrimitivePoint operator-(const PrimitivePoint& a, const ScreenPoint& b)
{
	return a - PrimitivePoint(b.GetNormalizedPoint());
}








PrimitiveRect operator+(const PrimitiveRect& a, const PrimitivePoint& b)
{
	PrimitiveRect ans = a;
	ans.pos = ans.pos + b;
	return ans;
}

PrimitiveRect operator-(const PrimitiveRect& a, const PrimitivePoint& b)
{
	PrimitiveRect ans = a;
	ans.pos = ans.pos - b;
	return ans;
}

PrimitiveRect operator+(const PrimitiveRect& a, const PrimitiveRect& b)
{
	PrimitiveRect ans = a;
	ans.pos = ans.pos + b.pos;
	ans.size = ans.size + b.size;
	return ans;
}

PrimitiveRect operator-(const PrimitiveRect& a, const PrimitiveRect& b)
{
	PrimitiveRect ans = a;
	ans.pos = ans.pos - b.pos;
	ans.size = ans.size - b.size;
	return ans;
}







ScreenPoint operator+(const ScreenPoint& a, const ScreenPoint& b)
{
	ScreenPoint ans = a;
	ans.x += b.x;
	ans.y += b.y;

	return ans;
}

ScreenPoint operator-(const ScreenPoint& a, const ScreenPoint& b)
{
	ScreenPoint ans = a;
	ans.x -= b.x;
	ans.y -= b.y;

	return ans;
}







ScreenRect operator+(const ScreenRect& a, const ScreenPoint& b)
{
	ScreenRect ans = a;
	ans.pos = ans.pos + b;
	return ans;
}

ScreenRect operator-(const ScreenRect& a, const ScreenPoint& b)
{
	ScreenRect ans = a;
	ans.pos = ans.pos - b;
	return ans;
}

ScreenRect operator+(const ScreenRect& a, const ScreenRect& b)
{
	ScreenRect ans = a;
	ans.pos = ans.pos + b.pos;
	ans.size = ans.size + b.size;
	return ans;
}
ScreenRect operator-(const ScreenRect& a, const ScreenRect& b)
{
	ScreenRect ans = a;
	ans.pos = ans.pos - b.pos;
	ans.size = ans.size - b.size;
	return ans;

}
