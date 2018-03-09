#pragma once

#include <Windows.h>
#include "Component.h"

class Sprite;

class Item : public Component
{
public:
	Item(std::wstring name, LPCWSTR scriptName, LPCWSTR textureFilename);
	~Item();

	void init();
	void DeInit();
	void Update(float deltaTime);
	void render();
	void Release();
	void Reset();

	void setPostition(float posX, float posY);
	void MoveDeltaPotion(float _deltaX, float _deltaY);

protected:
	Sprite * _sprite;
	float _posx;
	float _posy;

	std::wstring _scriptFilename;
	std::wstring _textureFilename;



public:
	 void ReceiveMessage(const sComponentMsgParam msgParam);
};