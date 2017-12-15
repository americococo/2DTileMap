#include "DeafultPart.h"

#include "RecoveryItem.h"
#include "poisonItem.h"
#include "NPC.h"
#include "player.h"
#include "Monster.h"
#include "Stage.h"
#include "Map.h"
DeafultPart::DeafultPart(Stage * stage):StagePart(stage)
{
	
}
DeafultPart::~DeafultPart()
{

}

void DeafultPart::CreateComponents(std::wstring mapName)
{
	StagePart::CreateComponents(mapName);

	for (int i = 0; i < 3; i++)
	{
		WCHAR name[256];
		wsprintf(name, L"recovery_item%d", i);
		RecoveryItem * item = new RecoveryItem(name, L"recovery_item", L"item_sprites");
		_stage->AddStageComponent(item);
	}

	for (int i = 0; i < 3; i++)
	{
		WCHAR name[256];
		wsprintf(name, L"posion_item%d", i);
		posionItem * item = new posionItem(name, L"recovery_item", L"item_sprites");
		_stage->AddStageComponent(item);
	}

	for (int i = 0; i < 3; i++)
	{
		WCHAR name[256];
		wsprintf(name, L"npc_%d", i);
		Charcter * _npc = new NPC(name, L"npc", L"character_sprite2");
		_stage->AddStageComponent(_npc);
	}


	for (int i = 0; i < 3; i++)
	{
		WCHAR name[256];
		wsprintf(name, L"monster_%d", i);
		Charcter * _monster = new Monster(name, L"monster", L"character_sprite2");
		_stage->AddStageComponent(_monster);
	}

	player * _player = new player(L"player", L"player", L"player");
	_stage->AddStageComponent(_player);

	_map->initViewer(_player);
}