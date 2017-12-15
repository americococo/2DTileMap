#pragma once
#include "StagePart.h"
#include <string>
class LifeStagePart:public StagePart
{
public:
	LifeStagePart(Stage * stage);
	~LifeStagePart();

public:
	Component * CreateLifeNPC(std::wstring sriptName,std::wstring textureFileName);
	//void SetName(LPCWSTR name);
	virtual void CreateComponents(std::wstring mapName);

private:
	int _lifeNpcCount;
};
