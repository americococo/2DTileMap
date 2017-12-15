#include "LifePlayer.h"
#include "State.h"
#include "IdileState.h"
#include "AttackState.h"
#include "DeffensState.h"
#include "DeadState.h"
#include "Component.h"

LifePlayer::LifePlayer(std::wstring name, std::wstring  scriptName, std::wstring  textureName) :player(name, scriptName, textureName)
{
	_hp = 1;
	_attackCoolDown = 0.0f;
}
LifePlayer::~LifePlayer()
{

}
void LifePlayer::InitState()
{
	player::InitState();
	ReplaceState(eStateType::ET_ATTACK, new IdleState());

}

void LifePlayer::ReplaceState(eStateType changeType, State * replaceState)
{
	std::map<eStateType, State*>::iterator itr = _stateMap.find(changeType);
	if (itr != _stateMap.end())
	{
		delete _stateMap[changeType];
		_stateMap.erase(changeType);

	}

	State * state = replaceState;
	state->Init(this);
	_stateMap[changeType] = state;
}