#pragma once
#include <string>
#include <Windows.h>

class Component;
class Stage;
class Map;

class StagePart
{
protected:
	Stage* _stage;
	Map* _map;

public:
	StagePart(Stage* stage);
	~StagePart();

public:
	virtual void CreateComponents(std::wstring mapName);
	virtual Component* CreateLifeNPC(std::wstring scriptName, std::wstring spriteName);
};