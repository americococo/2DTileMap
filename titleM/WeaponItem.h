#pragma once
#include <Windows.h>
#include "Item.h"

class Sprite;

class WeaponItem : public Item
{
public:
	WeaponItem(std::wstring name, LPCWSTR scriptName, LPCWSTR textureFilename);

public:
	void ReceiveMessage(const sComponentMsgParam msgParam);


};