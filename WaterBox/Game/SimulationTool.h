#pragma once
#include "WaterBox.h"

struct SimulationKeyEvent
{
	enum class SimulationKeyEventSymbol : uint8_t
	{
		SYMBOL,
		SPACE,
		SHIFT,
		CONTROL,
		ALT
	};

	SimulationKeyEventSymbol Type;
	char Symbol;
	bool State = false;
};
struct SimulationMouseEvent
{
	enum class SimulationMouseEventButton : uint8_t
	{
		NO,
		LMB,
		RMB,
		MMB
	};

	size_t X = 0, Y = 0;
	SimulationMouseEventButton Type;
	bool State = false;
};

class SimulationTool
{
public:
		void ProcessKeyEvent(SimulationKeyEvent event);
		void ProcessMouseEvent(SimulationMouseEvent event);
		void SetSimulation(class GameSimulation* Simulation);

private:
	enum class TecToolType :uint8_t
	{
		Paint
	};

	TecToolType TecTool = TecToolType::Paint;
	bool StateLMB = false;
	class GameSimulation* Sim;
};