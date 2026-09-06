#pragma once
#include "WaterBox.h"
namespace in { 
	struct InputEvent;
	struct MouseButtonEvent;

}


class SimulationTool
{
public:

	enum class ToolType : uint8_t {
		Draw,
		Heat,
		Move
	};


	void ProcessEvent(in::InputEvent event);
	void SetSimulation(class GameSimulation* Simulation);

	void SetMaterial(int ID);
	void SetTool(ToolType Type);

	

private:

	void ProcessMouseButtonEvent(in::MouseButtonEvent event);
	void ProcessMouseMoveEvent(int x, int y);
	void ProcessScrollEvent(int val);


	int SelectedMaterial;
	uint8_t Diameter = 0;

	ToolType TecTool = ToolType::Draw;
	class GameSimulation* Sim;


	template <typename Func>
	void UseSquareTool(int centerX, int centerY, Func Tool);


	bool LMB_State = false;
	bool RMB_State = false;
	bool MMB_State = false;
};