#include "IdileState.h"
#include "Charcter.h"
#include "Sprite.h"
IdleState::IdleState() {}
IdleState::~IdleState() {}

void IdleState::Init(Charcter * charcter)
{
	State::Init(charcter);
}
void IdleState::Start()
{
	State::Start();
	Statename = L"Idle";
	_nextState = eStateType::ET_NONE;
}
void IdleState::Stop()
{
	State::Stop();
}
void IdleState::Update(float deltaTime)
{
	State::Update(deltaTime);

	// check : 버그 수정
	if (eStateType::ET_NONE != _nextState)
	{
		_charcter->ChangeState(_nextState);
		return;
	}

	if (false == _charcter->getIsLive())
		return;

	if (false == _charcter->IsMoving())
	{
		_charcter->UpdateAi(deltaTime);
	}

}