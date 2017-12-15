#pragma once
#include <string>
#include <Windows.h>
#include "StagePart.h"

class DeafultPart : public StagePart
{
public:
	DeafultPart(Stage * stage);
	~DeafultPart();


public:
	void CreateComponents(std::wstring mapName);
};
