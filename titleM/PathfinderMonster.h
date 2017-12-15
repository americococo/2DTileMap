#pragma once
#include "Monster.h"
class PathfinderMonster :public Monster
{
public:
	PathfinderMonster(std::wstring name, std::wstring  scriptName, std::wstring  texutureName);
	~PathfinderMonster();

	//ai
public:
	void UpdateAi(float deltaTime);

	//State
public:


};
