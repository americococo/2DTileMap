#include "tileCell.h"
#include "Sprite.h"
#include "Component.h"
#include "TileObject.h"

tileCell::tileCell(int tileX,int tileY)
{
	_posX = _posY = 0.0f;
	_componentList.clear();
	_renderList.clear();

	_tileX = tileX;
	_tileY = tileY;

	//path √ ±‚»≠
	initPathfinding();

	_distanceWeigth = 1.0f;
}
tileCell::~tileCell() {}

void tileCell::deInit()
{

}


void tileCell::Release()
{

}

void tileCell::render()
{
	for (std::list<Component*>::iterator itr = _renderList.begin(); itr != _renderList.end(); itr++)
	{
		(*itr)->render();
	}
}

void tileCell::Reset()
{
	
}

void tileCell::setPostition(float posX,float posY)
{
	_posX = posX;
	_posY = posY;
	for (std::list<Component*>::iterator itr = _componentList.begin(); itr != _componentList.end(); itr++)
	{
		(*itr)->setPostition(posX,posY);
	}
}


void tileCell::Update(float deltaTime)
{	
	for (std::list<Component*>::iterator itr = _renderList.begin(); itr != _renderList.end(); itr++)
	{
		(*itr)->Update(deltaTime);
	}
}

float tileCell::GetPositionX()
{
	return _posX;
}

float tileCell::GetPositionY()
{
	return _posY;
}
void tileCell::AddComponent(Component * com,bool isrender)
{
	_componentList.push_back(com);

	if (eComponentType::CT_TILE_OBJECT == com->GetType())
	{
		_distanceWeigth = ((TileObject*)com)->GetDistanceWeigth();
	}

	if (isrender)
	{
		_renderList.push_back(com);
	}
}

void tileCell::RemoveAllComponets(Component * com)
{
	_componentList.remove(com);
	_renderList.remove(com);
}
void tileCell::moveDeltaPotion(float _deltaX,float _deltaY)
{
	_posX += _deltaX;
	_posY += _deltaY;

	for (std::list<Component*>::iterator itr = _componentList.begin(); itr != _componentList.end(); itr++)
	{
		(*itr)->MoveDeltaPotion(_deltaX, _deltaY);
	}
}

bool tileCell::canMove()
{
	for (std::list<Component*>::iterator itr = _componentList.begin(); itr != _componentList.end(); itr++)
	{
		if (false == (*itr)->canMove())
			return false;
	}

	return true;
}

bool tileCell::GetcolisonList(std::list<Component*>& colisonList)
{
	colisonList.clear();

	for (std::list<Component*>::iterator itr = _componentList.begin(); itr != _componentList.end(); itr++)
	{
		if (false == (*itr)->canMove())
		{
			colisonList.push_back(*itr);
		}
	}

	if (0 == colisonList.size())
		return true;

	return false;
}

std::list<Component*> tileCell::GetComponentList()
{
	return _componentList;
}