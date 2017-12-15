#pragma once
#include <string>
#include "Charcter.h"

class LifeNPC : public Charcter
{
public:
	LifeNPC(std::wstring name, std::wstring  scriptName, std::wstring  textureName);
	~LifeNPC();

	void UpdateAi(float deltaTime);
	void render();
};