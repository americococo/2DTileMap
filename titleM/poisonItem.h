#pragma once
#include <Windows.h>
#include "Item.h"

class posionItem : public Item
{
public:
	posionItem(std::wstring name, LPCWSTR scriptName, LPCWSTR textureFilename);

public:
	void ReceiveMessage(const sComponentMsgParam msgParam);
};