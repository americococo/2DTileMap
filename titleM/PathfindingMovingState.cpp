#include "PathfindingMovingState.h"
#include "Map.h"
#include "ComponentSystem.h"
#include "Charcter.h"
#include "GameSystem.h"
#include "Stage.h"
#include "GlobalType.h"
#include "tileCell.h"
PathfindingMovingState::PathfindingMovingState() {}
PathfindingMovingState::~PathfindingMovingState() {}


void PathfindingMovingState::Init(Charcter * charcter)
{
	State::Init(charcter);
	_movingDurtion = 0.0f;

}
void PathfindingMovingState::Stop()
{
	State::Stop();
	_charcter->ClearPathTileCellStack();
}

void PathfindingMovingState::Start()
{

	State::Start();
	Statename = L"AI_Move";

	_nextState = eStateType::ET_NONE;
	_movingDurtion = 0.0f;

	_pathtileCellStack = _charcter->getPathTileCellStack();
	_pathtileCellStack.pop();
}

void PathfindingMovingState::Update(float deltaTime)
{
	State::Update(deltaTime);

	if (_nextState != eStateType::ET_NONE)
	{
		_charcter->ChangeState(_nextState);
		return;
	}


	if (_charcter->getMoveTime() <= _movingDurtion)
	{
		_movingDurtion = 0.0f;

		if (0 != _pathtileCellStack.size())
		{
			tileCell * tilecell = _pathtileCellStack.top();
			_pathtileCellStack.pop();

			TilePosition to;
			to.x = tilecell->GetTileX();
			to.y = tilecell->GetTileY();

			TilePosition from;
			from.x = _charcter->getTileX();
			from.y = _charcter->getTileY();

			eDirection dirtion = GetDirection(to, from);

			if (eDirection::NONE != dirtion)
				_charcter->SetDirection(dirtion);

			Map* map = GameSystem::GetInstance()->getStage()->getMap();

			std::list<Component*> colisionList;
			bool canMove = map->getTileColisonList(tilecell->GetTileX(), tilecell->GetTileY(), colisionList);
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
				_charcter->MoveStart(tilecell->GetTileX(), tilecell->GetTileY());
				_charcter->MoveStop();
				_movingDurtion = 0.0f;
			}


		}
		else
			_nextState = eStateType::ET_IDLE;

	}
	else
	{
		_movingDurtion += deltaTime;
	}
}