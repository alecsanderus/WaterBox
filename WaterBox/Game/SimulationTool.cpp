#include "SimulationTool.h"
#include "GameManager.h"
#include "GameSimulation.h"
#include "GameMaterial.h"
#include "GameConfigManager.h"
#include "InputEvent.h"


void SimulationTool::ProcessEvent(in::InputEvent event)
{
	if (event.isMouseScroll())
		ProcessScrollEvent(std::get <in::MouseScrollEvent> (event.data).FullY);

	if (event.isMouseButton())
		ProcessMouseButtonEvent(std::get <in::MouseButtonEvent>(event.data));
	

	ProcessMouseMoveEvent(event.x, event.y);

	
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

void SimulationTool::ProcessMouseButtonEvent(in::MouseButtonEvent event)
{
	bool state = event.action != in::InputAction::Release;

	if (event.button == in::MouseButton::Left)
		LMB_State = state;
	if (event.button == in::MouseButton::Right)
		RMB_State = state;
	if (event.button == in::MouseButton::Middle)
		MMB_State = state;
}

void SimulationTool::ProcessMouseMoveEvent(int x, int y)
{
	if (x >= Sim->GameSizeX || y >= Sim->GameSizeY) return;

	if (LMB_State && RMB_State)
	{
		// Super secret
	}
	else if (LMB_State)
	{
		auto& Field = Sim->GameField;
		auto& Mater = SelectedMaterial;


		UseSquareTool(x, y, [&Field, &Mater](int x, int y) {
			Field(x, y).Create(Mater);
			});

		auto& brr = Sim->GameField(x, y);
		brr.Create(0);


	}
	else if (RMB_State)
	{


	}
	else if (MMB_State)
	{

	}
}

void SimulationTool::ProcessScrollEvent(int val)
{
	if (val > 0)
		Diameter = std::min (20, val + Diameter);
	else if (val < 0 && Diameter > 0)
		Diameter = std::max(0, (int) Diameter + val);

}

template <typename Func>
void SimulationTool::UseSquareTool (int centerX, int centerY, Func Tool) {


	int radius = Diameter / 2;

	int startY = std::max(0, centerY - radius);
	int endY = std::min((int)Sim->GameSizeY - 1, centerY + radius + Diameter%2);
	int startX = std::max(0, centerX - radius);
	int endX = std::min((int)Sim->GameSizeX - 1, centerX + radius + Diameter%2);

	for (int y = startY; y <= endY; ++y) {
		for (int x = startX; x <= endX; ++x) {
			Tool(x, y);
		}
	}
}