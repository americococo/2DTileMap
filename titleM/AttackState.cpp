#include "Sprite.h"
#include "Charcter.h"
#include "AttackState.h"
#include "ComponentMessage.h"
#include "ComponentSystem.h"

AttackState::AttackState() {}
AttackState::~AttackState() {}


void AttackState::Init(Charcter * charcter)
{
	State::Init(charcter);
}
void AttackState::Start()
{
	State::Start();
	Statename = L"Attack";
	sComponentMsgParam msgParam;
	msgParam.sender = _charcter;
	msgParam.attackpoint = _charcter->getattackpoint();
	msgParam.message = L"Attack";
	msgParam.reciver = _charcter->getTarget();
	ComponentSystem::GetInstance()->SendMsg(msgParam);

	_charcter->durabilityReduction();

	_nextState = eStateType::ET_IDLE;
}
void AttackState::Stop()
{
	State::Stop();
}
void AttackState::Update(float deltaTime)
{
	State::Update(deltaTime);
	
	if (eStateType::ET_NONE != _nextState)
	{
		_charcter->ResetTarget();
		_charcter->ChangeState(_nextState);
		return;
	}
}

void AttackState::Render()
{
	State::Render();
}
void AttackState::Release()
{
	State::Release();
}
void AttackState::Reset()
{
	State::Reset();
}