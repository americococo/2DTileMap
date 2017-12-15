#pragma once
#include "player.h"
class PathfinderPlayer:public player
{
public:
	PathfinderPlayer(std::wstring name, std::wstring  scriptName, std::wstring  texutureName);
	~PathfinderPlayer();



	//Ai
public:
	void UpdateAi(float deltaTime);


	//State
public:
	void InitState();
};

