#include "LifeStagePart.h"
#include "LifeNPC.h"
#include "LifePlayer.h"
#include "Stage.h"
#include "Map.h"
LifeStagePart::LifeStagePart(Stage * stage):StagePart(stage)
{
	_lifeNpcCount = 0;
}
LifeStagePart::~LifeStagePart() {}


Component * LifeStagePart::CreateLifeNPC(std::wstring sriptName, std::wstring textureFileName)
{
	WCHAR name[256];
	wsprintf(name, L"%lifeNpc_%d", _lifeNpcCount);
	_lifeNpcCount++;

	Component * component = new LifeNPC(name,sriptName,textureFileName);
	_stage->AddStageComponent(component);

	return component;
}

void LifeStagePart::CreateComponents(std::wstring mapName)
{
	StagePart::CreateComponents(mapName);

	for (int i = 0; i < 50;i++)
	{
		CreateLifeNPC(L"npc", L"npc");
	}
	LifePlayer * _player = new LifePlayer(L"player", L"player", L"player");
	_stage->AddStageComponent(_player);
	
	_map->initViewer(_player);
}