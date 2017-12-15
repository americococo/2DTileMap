#include "DeffensState.h"
#include "Charcter.h"

DeffensState::DeffensState() {}
DeffensState::~DeffensState() {}

void DeffensState::Init(Charcter * charcter)
{
	State::Init(charcter);
}
void DeffensState::Start()
{
	State::Start();
	Statename = L"Deffens";

	int attackpoint = _charcter->getattackedpoint();

	_charcter->DecreaseHP(attackpoint);

	if (false == _charcter->getIsLive())
	{
		//dead
		_charcter->setCanMove(true);
		_charcter->MoveStop();
		_nextState = eStateType::ET_DEAD;
	}
	else
	{
 		_nextState = eStateType::ET_MOVE;
	}

}
void DeffensState::Stop()
{
	State::Stop();
}

void DeffensState::Update(float deltaTime)
{
	State::Update(deltaTime);

	if (_nextState != eStateType::ET_NONE)
	{
		_charcter->ChangeState(_nextState);
		return;
	}
}

void DeffensState::Render()
{
	State::Render();
}
void DeffensState::Release()
{
	State::Release();
}
void DeffensState::Reset()
{
	State::Reset();
}