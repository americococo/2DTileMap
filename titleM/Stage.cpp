#include "tileCell.h"
#include "RecoveryItem.h"
#include "poisonItem.h"
#include "NPC.h"
#include "LifeNPC.h"
#include "player.h"
#include "LifePlayer.h"
#include "Monster.h"
#include "ComponentSystem.h"
#include "PathfinderPart.h"
#include "Stage.h"
#include "StagePart.h"
#include "LifeStagePart.h"
#include "DeafultPart.h"
#include "Map.h"
#include "GameSystem.h"

Stage::Stage() 
{
	_loader = NULL;
	_partMap.clear();
}

Stage::~Stage()
{
	ComponentSystem::GetInstance()->RemoveAllComponets();

	for (std::map<std::wstring, StagePart*>::iterator itr = _partMap.begin(); itr != _partMap.end(); itr++)
	{
		if (NULL != itr->second)
			delete itr->second;
	}
	_partMap.clear();
}

void Stage::Init(std::wstring mapName)
{
	_partMap[L"deafult"] = new DeafultPart(this);
	_partMap[L"lifeGame"] = new LifeStagePart(this);
	_partMap[L"pathFind"] = new PathfinderPart(this);

	_compoentList.clear();

	_loader = GetStageParts(mapName);
	_loader->CreateComponents(mapName);
		
	GameSystem::GetInstance()->InitInput();
}
StagePart* Stage::GetStageParts(std::wstring mapName)
{
	std::map<std::wstring, StagePart*>::iterator itr = _partMap.find(mapName);
	if (itr != _partMap.end())
		return _partMap[mapName];
	else
		return _partMap[L"deafult"];
}
void Stage::AddStageComponent(Component* component)
{
	component->init();
	_compoentList.push_back(component);
}

void Stage::Update(float deltaTime)
{
	UpdateCreateCompoentList();
	UdateRemoveCompentList();

	for (std::list<Component*>::iterator itr = _compoentList.begin(); itr != _compoentList.end(); itr++)
	{
		(*itr)->Update(deltaTime);
	}
}

void Stage::render()
{
	for (std::list<Component*>::iterator itr = _compoentList.begin(); itr != _compoentList.end(); itr++)
	{
		(*itr)->render();
	}
}
void Stage::Release()
{
	for (std::list<Component*>::iterator itr = _compoentList.begin(); itr != _compoentList.end(); itr++)
	{
		(*itr)->Release();
	}
}
void Stage::Reset()
{
	for (std::list<Component*>::iterator itr = _compoentList.begin(); itr != _compoentList.end(); itr++)
	{
		(*itr)->Reset();
	}
}

void Stage::createLifeNPC(Component * com)
{
	com->getTileX();
	com->getTileY();
	_createBaseComponentList.push_back(com);
}

void Stage::CheckDestoryLifeNPC(Component * tileCharcter)
{
	_removeComponentList.push_back(tileCharcter);
}

void Stage::UpdateCreateCompoentList()
{
	for (std::list<Component*>::iterator itr = _createBaseComponentList.begin();
		itr != _createBaseComponentList.end(); itr++)
	{
		Component * baseComponent=(*itr);

		LifeNPC * npc = (LifeNPC*)(_loader->CreateLifeNPC(L"npc", L"character_sprite2"));

		npc->initTilePostion(baseComponent->getTileX(), baseComponent->getTileY());
		
	}
	_createBaseComponentList.clear();
}
void Stage::UdateRemoveCompentList()
{

	for (std::list<Component*>::iterator itr = _removeComponentList.begin(); itr != _removeComponentList.end(); itr++)
	{
		Component * com = (*itr);
		destoryLifeNPC(com->getTileX(), com->getTileY(), com);
	}
	_removeComponentList.clear();
}

void Stage::destoryLifeNPC(int _tileX,int _tileY,Component * tileCharcter)
{

	_map->ResetTileComponent(_tileX, _tileY, tileCharcter);
	_compoentList.remove(tileCharcter);
	ComponentSystem::GetInstance()->removeComponent(tileCharcter);
}
void Stage::CreatePathfinderNPC(tileCell * tilecell)
{
	
	StagePart * load;
	load = GetStageParts(L"lifeGame");

	LifeNPC * npc = (LifeNPC*)(load->CreateLifeNPC(L"npc", L"character_sprite2"));
	npc->initTilePostion(tilecell->GetTileX(), tilecell->GetTileY());
	npc->setCanMove(true);

	_compoentList.remove(npc);
	tilecell->AddComponent(npc, true);

	tileCell * prev = tilecell->GetPrevPathfindingCell(); //ÀÌÀü Å¸ÀÏ¼¿

	if (tilecell->GetTileX() < prev->GetTileX())
		npc->SetDirection(eDirection::RIGHT);

	else if ( prev->GetTileX() < tilecell->GetTileX())
		npc->SetDirection(eDirection::LEFT);

	else if (prev->GetTileY() < tilecell->GetTileY())
		npc->SetDirection(eDirection::UP);
	else if (  tilecell->GetTileY() < prev->GetTileY())
		npc->SetDirection(eDirection::DOWN);

}


void Stage::CreatePathfindingMark(tileCell * tilecell)
{
	StagePart * load;
	load = GetStageParts(L"lifeGame");

	LifeNPC * npc = (LifeNPC*)(load->CreateLifeNPC(L"monster", L"character_sprite2"));
	npc->initTilePostion(tilecell->GetTileX(), tilecell->GetTileY());
	npc->setCanMove(true);
	_compoentList.remove(npc);
	tilecell->AddComponent(npc, true);

	if (NULL != tilecell->GetPrevPathfindingCell())
	{
		
		tileCell * prev = tilecell->GetPrevPathfindingCell(); //ÀÌÀü Å¸ÀÏ¼¿

		if (tilecell->GetTileX() < prev->GetTileX())
			npc->SetDirection(eDirection::LEFT);

		else if (prev->GetTileX() < tilecell->GetTileX())
			npc->SetDirection(eDirection::RIGHT);

		else if (prev->GetTileY() < tilecell->GetTileY())
			npc->SetDirection(eDirection::DOWN);
		else if (tilecell->GetTileY() < prev->GetTileY())
			npc->SetDirection(eDirection::UP);
	}
}