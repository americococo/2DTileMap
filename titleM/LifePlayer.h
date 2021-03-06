#pragma once
#include "player.h"

class LifePlayer : public player
{
public:
	LifePlayer(std::wstring name, std::wstring  scriptName, std::wstring  textureName);
	~LifePlayer();

	void UpdateText() {}


public:
	void InitState();
	void ReplaceState(eStateType changeType, State * replaceState);
};