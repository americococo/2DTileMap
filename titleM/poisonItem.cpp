#include "poisonItem.h"
#include "Map.h"
#include "ComponentSystem.h"
#include "Charcter.h"
#include "Sprite.h"
#include "GameSystem.h"
#include "Stage.h"

posionItem::posionItem(std::wstring name, LPCWSTR scriptName, LPCWSTR textureFilename) : Item(name, scriptName, textureFilename)
{

}
void posionItem::ReceiveMessage(const sComponentMsgParam msgParam)
{
	if (L"use" == msgParam.message)
	{
		Component * _sender = msgParam.sender;
		switch (_sender->GetType())
		{
		case eComponentType::CT_MONSTER:
		case eComponentType::CT_NPC:
		case eComponentType::CT_PLAYER:
			((Charcter*)_sender)->DecreaseHP(30);
			//Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"TestMap");
			Map* map = GameSystem::GetInstance()->getStage()->getMap();
			map->ResetTileComponent(_tileX, _tileY, this);
			isLive = false;
			break;
		}

	}
}