#include "StagePart.h"
#include "Stage.h"
#include "Map.h"

StagePart::StagePart(Stage* stage)
{
	_stage = stage;
}

StagePart::~StagePart()
{

}

void StagePart::CreateComponents(std::wstring mapName)
{
	_map = new Map(mapName.c_str());
	_stage->SetMap(_map);
	_stage->AddStageComponent(_map);
}

Component* StagePart::CreateLifeNPC(std::wstring sriptName, std::wstring textureFileName)
{
	return NULL;
}