#pragma once
#include <string>
#include <Windows.h>
#include "StagePart.h"

class Component;

class Stage;

class PathfinderPart : public StagePart
{
public:
	PathfinderPart(Stage * stage);
	~PathfinderPart();


public:
	void CreateComponents(std::wstring mapName);
};
