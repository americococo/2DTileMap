#pragma once
#include "Charcter.h"

class NPC : public Charcter
{
public:
	NPC(std::wstring name, std::wstring  scriptName, std::wstring  textureName);
	~NPC();

	void UpdateAi(float deltaTime);
};