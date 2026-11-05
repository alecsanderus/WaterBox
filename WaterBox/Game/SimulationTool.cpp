#include "SimulationTool.h"
#include "GameManager.h"
#include "GameSimulation.h"
#include "GameMaterial.h"
#include "GameConfigManager.h"
#include "InputEvent.h"
#include "UI/MaterialCardWidget.h"
#include "UI/MaterialCategoryWidget.h"


void SimulationTool::ProcessEvent(in::InputEvent event)
{
	ProcessMouseMoveEvent(event.x, event.y);

	if (event.isMouseScroll())
		ProcessScrollEvent(std::get <in::MouseScrollEvent> (event.data).FullY);

	if (event.isMouseButton())
		ProcessMouseButtonEvent(std::get <in::MouseButtonEvent>(event.data));
}

void SimulationTool::SetSimulation(GameSimulation* Simulation){Sim = Simulation;}

void SimulationTool::SetMaterial(int ID)
{
	SelectedMaterial = ID;
}

void SimulationTool::SetTool(ToolType Type)
{
	TecTool = Type;
}

void SimulationTool::SetTool(int ID)
{
	TecTool = static_cast <ToolType> (ID);
}

void SimulationTool::Tick()
{
	if (MPosX == -1 || MPosY == -1) return;
	auto& conf = GameConfigManager::GetGameConfigManager();

	if (LastMPosX == -1 || LastMPosY == -1)
	{
		LastMPosX = MPosX;
		LastMPosY = MPosY;
	}
	auto& Field = Sim->GameField;


	int ActionID = LMB_State + RMB_State * 2 + MMB_State * 4 + static_cast <int> (TecTool) * 10;


	/*
	* 
	0 - no
	1 - LMB
	2 - RMB
	3 - LMB + RMB
	4 - MMB
	7 - MMB + LMB + RMB
	 */




	switch (ActionID)
	{
	case 1:{

		auto& Mater = SelectedMaterial;

		UseLineSquareTool(LastMPosX, LastMPosY, MPosX, MPosY,
			[&Field, &Mater](int x, int y) {
				Field(x, y).Create(Mater);
			});
		
	}break;

	case 2: {

		UseLineSquareTool(LastMPosX, LastMPosY, MPosX, MPosY,
			[&Field](int x, int y) {
				Field(x, y).Destroy();
			});

	}break;	
	case 4: {

		SelectedMaterial = Field(MPosX, MPosY).OriginalMaterialID;
		auto& mat = conf.Materials.GetElement(SelectedMaterial);
		mat.ThisMaterialCardWidget->MakeClick();
		auto& cat = conf.Categories.GetElement(mat.CategoryID);
		cat.ThisMaterialCategoryWidget->MakeClick();

	}break;


		case 3: {

			UseLineSquareTool(LastMPosX, LastMPosY, MPosX, MPosY,
				[&Field](int x, int y) {
					auto& tec = Field(x, y);
					if (auto& mat = GameConfigManager::GetGameConfigManager().Materials.GetElement(tec.OriginalMaterialID);
						tec.Active && mat.StateCategory == StateCategoryEnum::liquid) tec.Pressure += 10.f;
				});

		}break;

	case 11: {

		UseLineSquareTool(LastMPosX, LastMPosY, MPosX, MPosY,
			[&Field](int x, int y) {
				auto& tec = Field(x, y);
				if (tec.Active) tec.VelX -= 3;
			});

	}break;
	case 12: {

		UseLineSquareTool(LastMPosX, LastMPosY, MPosX, MPosY,
			[&Field](int x, int y) {
				auto& tec = Field(x, y);
				if (tec.Active) tec.VelX += 3;
			});

	}break;
	case 14: {

		UseLineSquareTool(LastMPosX, LastMPosY, MPosX, MPosY,
			[&Field](int x, int y) {
				auto& tec = Field(x, y);
				if (tec.Active) tec.VelY -= 3;
			});

	}break;

	default:

		LastMPosX = -1; LastMPosY = -1; MPosX = -1; MPosY = -1;

		break;
	}





	LastMPosX = MPosX;
	LastMPosY = MPosY;

}

int SimulationTool::GetGameViewType() const {
	return GameViewType;
}

void SimulationTool::SetGameViewType(const int Type) {
	GameViewType = std::clamp(Type, 0, MaxGameViewType);
}

void SimulationTool::IncreaseGameViewType() {
	GameViewType++;
	if (GameViewType > MaxGameViewType)
		GameViewType = 0;
}


void SimulationTool::ProcessMouseButtonEvent(in::MouseButtonEvent event)
{
	bool state = event.action != in::InputAction::Release;

	if (event.button == in::MouseButton::Left)
		LMB_State = state;
	if (event.button == in::MouseButton::Right)
		RMB_State = state;
	if (event.button == in::MouseButton::Middle)
		MMB_State = state;


	if (event.action == in::InputAction::Release) {
		LastMPosX = -1; LastMPosY = -1; MPosX = -1; MPosY = -1;
	}
}



void SimulationTool::ProcessMouseMoveEvent(int x, int y)
{
	if (x >= Sim->GameSizeX || y >= Sim->GameSizeY) return;
	MPosX = x;
	MPosY = y;
}

void SimulationTool::ProcessScrollEvent(int val)
{
	if (val > 0)
		Diameter = std::min (20, val + Diameter);
	else if (val < 0 && Diameter > 0)
		Diameter = std::max(0, (int) Diameter + val);

}



template <typename Func>
void SimulationTool::UseLineSquareTool(int xA, int yA, int xB, int yB, Func Tool) {
	auto& Field = Sim->GameField;

	int radius = Diameter / 2;
	int xModifier = Diameter % 2;

	auto ApplyToolSafe = [&](int cx, int cy) {
		int startY = std::max(0, cy - radius);
		int endY = std::min((int)Sim->GameSizeY - 1, cy + radius + xModifier);
		int startX = std::max(0, cx - radius);
		int endX = std::min((int)Sim->GameSizeX - 1, cx + radius + xModifier);

		for (int y = startY; y <= endY; ++y) {
			for (int x = startX; x <= endX; ++x) {
				Tool(x, y);
			}
		}
		};

	auto ApplyNewBoundary = [&](int cx, int cy, int stepX, int stepY) {
		int startY = cy - radius;
		int endY = cy + radius + xModifier;
		int startX = cx - radius;
		int endX = cx + radius + xModifier;

		if (stepX != 0) {
			int newX = (stepX > 0) ? endX : startX;
			if (newX >= 0 && newX < (int)Sim->GameSizeX) {
				int clY1 = std::max(0, startY);
				int clY2 = std::min((int)Sim->GameSizeY - 1, endY);
				for (int y = clY1; y <= clY2; ++y) {
					Tool(newX, y);
				}
			}
		}

		if (stepY != 0) {
			int newY = (stepY > 0) ? endY : startY;
			if (newY >= 0 && newY < (int)Sim->GameSizeY) {           
				int clX1 = (stepX > 0) ? startX : (stepX < 0 ? startX + 1 : startX);
				int clX2 = (stepX > 0) ? endX - 1 : (stepX < 0 ? endX : endX);

				clX1 = std::max(0, clX1);
				clX2 = std::min((int)Sim->GameSizeX - 1, clX2);

				for (int x = clX1; x <= clX2; ++x) {
					Tool(x, newY);
				}
			}
		}
		};

	int dx = std::abs(xB - xA);
	int dy = std::abs(yB - yA);
	int sx = (xA < xB) ? 1 : -1;
	int sy = (yA < yB) ? 1 : -1;
	int err = dx - dy;

	ApplyToolSafe(xA, yA);

	while (xA != xB || yA != yB) {
		int e2 = 2 * err;
		int stepX = 0;
		int stepY = 0;

		if (e2 > -dy) {
			err -= dy;
			xA += sx;
			stepX = sx;
		}
		if (e2 < dx) {
			err += dx;
			yA += sy;
			stepY = sy;
		}
   
		ApplyNewBoundary(xA, yA, stepX, stepY);
	}
}