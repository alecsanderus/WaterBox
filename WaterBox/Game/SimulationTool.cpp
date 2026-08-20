#include "SimulationTool.h"
#include "Game/GameManager.h"
#include "Game/GameSimulation.h"

void SimulationTool::ProcessKeyEvent(SimulationKeyEvent event)
{
	


}

void SimulationTool::ProcessMouseEvent(SimulationMouseEvent event)
{
	if (event.Type == SimulationMouseEvent::SimulationMouseEventButton::LMB)
		StateLMB = event.State;
	
	if (StateLMB)
	{
		if (event.X >= Sim->GameSizeX || event.Y >= Sim->GameSizeY) return;

		auto& brr = Sim->GameField(event.X, event.Y).Color = {255,0,0};


	}
}

void SimulationTool::SetSimulation(GameSimulation* Simulation){Sim = Simulation;}
