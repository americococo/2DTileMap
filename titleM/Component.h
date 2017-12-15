#pragma once
#include <Windows.h>
#include <string>
#include "ComponentMessage.h"

enum eComponentType
{
	CT_PLAYER,
	CT_MONSTER,
	CT_NPC,
	CT_TILE_OBJECT,
	CT_ITEM,
	CT_NONE
};

class Component
{
protected:
	eComponentType componentType;
	int _tileX;
	int _tileY;
	std::wstring _name;
	bool _canMove;

	float _moveDistancePerTimeX;
	float _moveDistancePerTimeY;


public:
	Component() 
	{

	}
	Component(std::wstring name);
	virtual ~Component();

	virtual void init()=0;
	virtual void DeInit()=0;
	virtual void Update(float deltaTime)=0;
	virtual void render()=0;
	virtual void Release()=0;
	virtual void Reset()=0;

	virtual void MoveDeltaPotion(float _deltaX,float _deltaY) {}
	virtual void setPostition(float posX, float posY) {}

	void setCanMove(bool canMove){_canMove = canMove; }

	bool canMove() { return _canMove; }

	int getTileX() { return _tileX; }
	int getTileY() { return _tileY; }

	float GetMoveDeltaX() { return _moveDistancePerTimeX; }
	float GetMoveDeltaY() { return _moveDistancePerTimeY; }

	eComponentType GetType() { return componentType; }
	void setLive(bool live) { isLive = live; }
	//message
public:
	//virtual void ReceiveMessage(Component * sender, std::wstring message);
	virtual void ReceiveMessage(const sComponentMsgParam msgParam);


protected:
	bool isLive;

public:
	bool getIsLive() { return isLive; };


	std::wstring getName() { return _name; }

};