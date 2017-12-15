#pragma once
#include <string>

class Component;

struct sComponentMsgParam
{
	Component * sender;
	int attackpoint;

	Component * reciver;
	std::wstring message;
};
