#pragma once
#include <Windows.h>
#include "Component.h"

class Sprite;

class TileObject: public Component
{
public:
	TileObject(std::wstring name,Sprite * sprite,int tileX,int tileY);
	virtual ~TileObject();

	void init();
	void DeInit();
	void Update(float deltaTime);
	void render();
	void Release();
	void Reset();

	void setPostition(float posX, float posY);
	void MoveDeltaPotion(float _deltaX, float _deltaY);

private:
	Sprite * _sprite;
	float _posX;
	float _posY;
};