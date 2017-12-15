#include "RecoveryItem.h"
#include "Map.h"
#include "ComponentSystem.h"
#include "Charcter.h"
#include "Sprite.h"
#include "GameSystem.h"
#include "Stage.h"
RecoveryItem::RecoveryItem(std::wstring name, LPCWSTR scriptName, LPCWSTR textureFilename) :Component(name)
{
	componentType = eComponentType::CT_ITEM;
	_sprite = NULL;
	_scriptFilename = scriptName;
	_textureFilename = textureFilename;
}

RecoveryItem::~RecoveryItem()
{

}

void RecoveryItem::init()
{
	{
		//Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"TestMap");
		Map* map = GameSystem::GetInstance()->getStage()->getMap();

		while (1)
		{
			_tileX = rand() % (map->Getwidth() - 2) + 1;
			_tileY = rand() % (map->Getheight() - 2) + 1;

			TilePosition CharcterNewPosition;
			CharcterNewPosition.x = _tileX;
			CharcterNewPosition.y = _tileY;

			if (true == map->CanMoveTileMap(CharcterNewPosition))
				break;
		}

		_posx = map->GetPositionX(_tileX, _tileY);
		_posy = map->GetPositionY(_tileX, _tileY);

		map->setTileComponent(_tileX, _tileY, this, false);
	}

	{
		WCHAR textureFileName[256];
		WCHAR scriptFileName[256];

		wsprintf(textureFileName, L"%s.png", _textureFilename.c_str());
		wsprintf(scriptFileName, L"%s.json", _scriptFilename.c_str());

		_sprite = new Sprite(textureFileName, scriptFileName);
		_sprite->Init();
	}


	_canMove = true;
}

void RecoveryItem::DeInit()
{
	_sprite->deInit();
}
void RecoveryItem::Update(float deltaTime)
{
	if (isLive == false)
		return;
	_sprite->Update(deltaTime);
}
void RecoveryItem::render()
{
	if (isLive == false)
		return;
	_sprite->setPostition(_posx, _posy);
	_sprite->render();
}
void RecoveryItem::Release()
{
	_sprite->Release();
}
void RecoveryItem::Reset()
{
	_sprite->Reset();
}

void RecoveryItem::setPostition(float posX, float posY)
{
	_posx = posX;
	_posy = posY;
}

void RecoveryItem::MoveDeltaPotion(float _deltaX, float _deltaY)
{
	_posx += _deltaX;
	_posy += _deltaY;

	_sprite->setPostition(_posx, _posy);
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