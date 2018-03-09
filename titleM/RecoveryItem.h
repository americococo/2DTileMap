#pragma once
#include <Windows.h>
#include "Item.h"
class Sprite;

class RecoveryItem : public Item
{
public:
	RecoveryItem(std::wstring name, LPCWSTR scriptName, LPCWSTR textureFilename);

public:
	void ReceiveMessage(const sComponentMsgParam msgParam);
};