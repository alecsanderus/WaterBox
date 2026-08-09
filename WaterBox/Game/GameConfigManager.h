#pragma once
#include "WaterBox.h"

struct GameMaterial;

class GameConfigManager
{
public:
	const std::vector <GameMaterial>& GetMaterials ();
	GameMaterial GetMaterial(int ID);
	void LoadMaterials();

protected:
	bool AreMaterialsLoaded = false;
	std::vector<GameMaterial> Materials;
	
};