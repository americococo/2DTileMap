#pragma once
#include "Charcter.h"

class Monster:public Charcter
{
public:
	Monster(std::wstring name, std::wstring  scriptName, std::wstring  textureName);
	~Monster();


public:
	//¿Á¡§¿«
	void UpdateAi(float deltaTime);

	Component * Colision(std::list<Component*>& colisionList);
};