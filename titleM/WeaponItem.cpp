#include "WeaponItem.h"
#include "GameSystem.h"
#include "Stage.h"
#include "Map.h"

#include "Equip_item.h"
#include "Charcter.h"

WeaponItem::WeaponItem(std::wstring name, LPCWSTR scriptName, LPCWSTR textureFilename) : Item(name, scriptName, textureFilename)
{
	
}
void WeaponItem::ReceiveMessage(const sComponentMsgParam msgParam)
{
	if (L"use" == msgParam.message)
	{
		Component * _sender = msgParam.sender;

		Map* map = GameSystem::GetInstance()->getStage()->getMap();
		map->ResetTileComponent(_tileX, _tileY, this);

		isLive = false;
		EquipItem equipItem;
		equipItem.atk =7 ;
		equipItem.attSpeed = 0.2f;
		equipItem.Durability = 10;
		
		((Charcter*)_sender)->EquipWeapon(equipItem);

	}
}
