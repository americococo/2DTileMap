#pragma once
#include "TileObject.h"

class Sprite;

class LifeTileObject : public TileObject
{
public:
	LifeTileObject (int tileX,int tileY, std::wstring name, Sprite * sprite);
	~LifeTileObject();
	


private:
	Sprite * _sprite;
	float _posX;
	float _posY;



public:
	void Update(float deltaTime);
};