#include "RecoveryItem.h"
#include "Map.h"
#include "ComponentSystem.h"
#include "Charcter.h"
#include "Sprite.h"
#include "GameSystem.h"
#include "Stage.h"



RecoveryItem::RecoveryItem(std::wstring name, LPCWSTR scriptName, LPCWSTR textureFilename): Item(name,scriptName,textureFilename)
{

}

void RecoveryItem::ReceiveMessage(const sComponentMsgParam msgParam)
{
	if (L"use" == msgParam.message)
	{
		Component * _sender = msgParam.sender;
		switch (_sender->GetType())
		{
		case eComponentType::CT_MONSTER:
			break;
		case eComponentType::CT_NPC:
			break;
		case eComponentType::CT_PLAYER:
			((Charcter*)_sender)->IncreaseHP(100);
			Map* map = GameSystem::GetInstance()->getStage()->getMap();
			map->ResetTileComponent(_tileX, _tileY, this);
			isLive = false;
			
			break;
		}

	}
}