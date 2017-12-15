#include "poisonItem.h"
#include "Map.h"
#include "ComponentSystem.h"
#include "Charcter.h"
#include "Sprite.h"
#include "GameSystem.h"
#include "Stage.h"
posionItem::posionItem(std::wstring name, LPCWSTR scriptName, LPCWSTR textureFilename) :Component(name)
{
	componentType = eComponentType::CT_ITEM;
	_sprite = NULL;
	_scriptFilename = scriptName;
	_textureFilename = textureFilename;
}

posionItem::~posionItem()
{

}

void posionItem::init()
{
	{
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

void posionItem::DeInit()
{
	_sprite->deInit();
}
void posionItem::Update(float deltaTime)
{
	if (isLive == false)
		return;
	_sprite->Update(deltaTime);
}
void posionItem::render()
{
	if (isLive == false)
		return;
	_sprite->setPostition(_posx, _posy);
	_sprite->render();
}
void posionItem::Release()
{
	_sprite->Release();
}
void posionItem::Reset()
{
	_sprite->Reset();
}

void posionItem::setPostition(float posX, float posY)
{
	_posx = posX;
	_posy = posY;
}

void posionItem::MoveDeltaPotion(float _deltaX, float _deltaY)
{
	_posx += _deltaX;
	_posy += _deltaY;

	_sprite->setPostition(_posx, _posy);
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