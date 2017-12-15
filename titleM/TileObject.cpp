#include "TileObject.h"
#include "Sprite.h"
TileObject::TileObject(std::wstring name, Sprite * sprite,int tileX,int tileY) :Component(name)
{
	_sprite = sprite;
	componentType = eComponentType::CT_TILE_OBJECT;
	_tileX = tileX;
	_tileY = tileY;
}

TileObject::~TileObject()
{

}

void TileObject::init()
{
	_sprite->Init();
}
void TileObject::DeInit()
{
	_sprite->deInit();
}
void TileObject::Update(float deltaTime)
{
	_sprite->Update(deltaTime);
}
void TileObject::render()
{
	_sprite->setPostition(_posX, _posY);
	_sprite->render();
}
void TileObject::Release()
{
	_sprite->Release();
}
void TileObject::Reset()
{
	_sprite->Reset();
}

void TileObject::setPostition(float posX, float posY)
{
	_posX = posX;
	_posY = posY;
}

void TileObject::MoveDeltaPotion(float _deltaX, float _deltaY)
{
	_posX += _deltaX;
	_posY += _deltaY;
}