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
}

void PathfindingMovingState::Start()
{

	State::Start();
	Statename = L"Move";

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

			_charcter->MoveStart(tilecell->GetTileX(), tilecell->GetTileY());
			_charcter->MoveStop();
		}
		else
			_nextState = eStateType::ET_IDLE;

	}
	else
	{
		_movingDurtion += deltaTime;
	}
}