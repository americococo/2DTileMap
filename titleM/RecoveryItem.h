#pragma once
#include <Windows.h>
#include "Component.h"

class Sprite;

class RecoveryItem : public Component
{
public:
	RecoveryItem(std::wstring name, LPCWSTR scriptName, LPCWSTR textureFilename);
	~RecoveryItem();

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
	float _posx;
	float _posy;
	
	std::wstring _scriptFilename;
	std::wstring _textureFilename;
	


public:
	void ReceiveMessage(const sComponentMsgParam msgParam);
};