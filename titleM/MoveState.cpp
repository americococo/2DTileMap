#include "MoveState.h"
#include "Map.h"
#include "ComponentSystem.h"
#include "Charcter.h"
#include "GameSystem.h"
#include "Stage.h"
#include "GlobalType.h"
MoveState::MoveState() {}
MoveState::~MoveState() {}


void MoveState::Init(Charcter * charcter)
{
	State::Init(charcter);
	_movingDurtion = 0.0f;

}
void MoveState::Stop()
{
	State::Stop();
}

void MoveState::Start()
{
	
	State::Start();
	Statename = L"Move";
	if (true == _charcter->IsMoving())
	{
		return;
	}

	_nextState = eStateType::ET_NONE;
	//Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"TestMap");
	Map* map = GameSystem::GetInstance()->getStage()->getMap();

	int newTiltleX = _charcter->getTileX();
	int newTiltleY = _charcter->getTileY();

	switch (_charcter->getDirection())
	{
	case eDirection::LEFT:
		newTiltleX--;
		break;
	case eDirection::RIGHT:
		newTiltleX++;
		break;
	case eDirection::UP:
		newTiltleY--;
		break;
	case eDirection::DOWN:
		newTiltleY++;
		break;
	}

	std::list<Component*> colisionList;
	bool canMove = map->getTileColisonList(newTiltleX, newTiltleY, colisionList);
	if (false == canMove)
	{
		Component * target = _charcter->Colision(colisionList);
		if (NULL != target && _charcter->IsCoolDown())
		{
			_charcter->ResetCoolDown();
			_charcter->SetTarget(target);
			_nextState = eStateType::ET_ATTACK;
		}
		else
		{
			_nextState = eStateType::ET_IDLE;
		}
	}
	else
	{
		_charcter->MoveStart(newTiltleX, newTiltleY);
		_charcter->MoveStop();
		_movingDurtion = 0.0f;
	}
}

void MoveState::Update(float deltaTime)
{
	State::Update(deltaTime);

	if (_nextState != eStateType::ET_NONE)
	{
		_charcter->ChangeState(_nextState);
		return;
	}

	//UpdateAi

	//if (_charcter->getMoveTime() <= _movingDurtion)
	//{
	//	_movingDurtion = 0.0f;
	//	_charcter->MoveStop();
	//	_charcter->ChangeState(eStateType::ET_IDLE);
	//}

	//else
	//{
	//	_movingDurtion += deltaTime;
	//	_charcter->Moving(deltaTime);
	//}

	if (_charcter->getMoveTime() <= _movingDurtion)
	{
		_nextState = eStateType::ET_IDLE;
	}
	else
	{
		_movingDurtion += deltaTime;
	}
}