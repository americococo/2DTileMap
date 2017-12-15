#pragma once
#include "Charcter.h"
class player : public Charcter
{
public:
	player(std::wstring name, std::wstring  scriptName, std::wstring  textureName);
	~player();

//Ai
public:
	void UpdateAi(float deltaTime);
	Component * Colision(std::list<Component*>& colisionList);

	virtual void InitState();
};