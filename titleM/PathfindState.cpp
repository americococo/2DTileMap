#include "PathfindState.h"
#include "GameSystem.h"
#include "Map.h"
#include "Stage.h"
#include "Charcter.h"
#include "tileCell.h"
#include "GlobalType.h"
PathfindState::PathfindState()
{

}

PathfindState::~PathfindState()
{

}

void PathfindState::Init(Charcter * charcter)
{
	State::Init(charcter);
}
void PathfindState::Update(float deltaTime)
{
	State::Update(deltaTime);

	//큐에 들어가있는 셀 "하나씩"! 탐색

	if (eStateType::ET_NONE != _nextState)
	{
		_charcter->ChangeState(_nextState);
		return;
	}

	switch (_updateState)
	{
	case eUpdateState::PATHFINDING:
		UpdatePathfinding(); break;
	case eUpdateState::BUILD_PATH:
		UpdateBuildPath(); break;
	}
}

void PathfindState::UpdatePathfinding()
{
	if (0 != _pathfingTileQueue.size())
	{
		//큐에 처음 값을 빼 검사
		tileCell * tilecell = _pathfingTileQueue.top();
		_pathfingTileQueue.pop();

		if (false == tilecell->IsPathfindMark())
		{
			tilecell->PathFinded();

			wchar_t  tileCheck[256];
			swprintf(tileCheck, L"find TileCell X:%d Y:%d\n Target TileCell X:%d Y:%d\n", tilecell->GetTileX(), tilecell->GetTileY(), _charcter->getTargetTileCell()->GetTileX(), _charcter->getTargetTileCell()->GetTileY());
			OutputDebugString(tileCheck);


			//목표타일 -> 종료
			if (tilecell->GetTileX() == _targetTileCell->GetTileX() && tilecell->GetTileY() == _targetTileCell->GetTileY())
			{
				std::list<Component*> com = _targetTileCell->GetComponentList();
				for (std::list<Component*>::iterator itr = com.begin(); itr != com.end(); itr++)
				{

					if (eComponentType::CT_MONSTER == (*itr)->GetType())
					{
						Charcter * monster = (Charcter*)(*itr);
						tileCell * prev = tilecell->GetPrevPathfindingCell();

						if (tilecell->GetTileX() < prev->GetTileX())
							monster->SetDirection(eDirection::RIGHT);
						else if (prev->GetTileX() < tilecell->GetTileX())
							monster->SetDirection(eDirection::LEFT);
						else if (prev->GetTileY() < tilecell->GetTileY())
							monster->SetDirection(eDirection::UP);
						else if (tilecell->GetTileY() < prev->GetTileY())
							monster->SetDirection(eDirection::DOWN);
					}
				}
				OutputDebugString(L"Find Goal\n");

				_updateState = eUpdateState::BUILD_PATH;
				_reverseTilecell = _targetTileCell;
				return;
			}
			for (int direction = 0; direction < eDirection::NONE; direction++)
			{
				TilePosition currentTilePos;
				currentTilePos.x = tilecell->GetTileX();
				currentTilePos.y = tilecell->GetTileY();
				TilePosition nextTilePos = GetNextTilePostion(currentTilePos, (eDirection)direction);

				Map * map = GameSystem::GetInstance()->getStage()->getMap();
				tileCell * nextTileCell = map->getTileCell(nextTilePos);

				//장애물 체크 탐색한 길인지 체크
				if ((true == map->CanMoveTileMap(nextTilePos) && false == nextTileCell->IsPathfindMark()) ||
					(nextTileCell->GetTileX() == _targetTileCell->GetTileX() && nextTileCell->GetTileY() == _targetTileCell->GetTileY()))
				{
					float distanceFromStart = tilecell->getDistanceFromStart()  + tilecell->getDistanceWeight();

					if (NULL == nextTileCell->GetPrevPathfindingCell())
					{
						nextTileCell->SetDistanceFromStart(distanceFromStart);
						nextTileCell->SetPrevPathfindingCell(tilecell);
						_pathfingTileQueue.push(nextTileCell);


						//탐색범위 탐색
						if ((nextTileCell->GetTileX() != _targetTileCell->GetTileX() || nextTileCell->GetTileY() != _targetTileCell->GetTileY())
							&& (nextTileCell->GetTileX() != _charcter->getTileX() || nextTileCell->GetTileY() != _charcter->getTileY()))
						{
							GameSystem::GetInstance()->getStage()->CreatePathfinderNPC(nextTileCell);
						}
					}
					else
					{
						if (distanceFromStart < nextTileCell->getDistanceFromStart())
						{
							//다시검사
							nextTileCell->SetDistanceFromStart(distanceFromStart);
							nextTileCell->SetPrevPathfindingCell(tilecell);
							_pathfingTileQueue.push(nextTileCell);
						}
					}
				}
			}
		}

	}
	else
		_nextState = eStateType::ET_IDLE;
	
}
void PathfindState::UpdateBuildPath()
{
	if (NULL != _reverseTilecell)
	{
		if (_reverseTilecell->GetTileX() != _targetTileCell->GetTileX()
		|| _reverseTilecell->GetTileY() != _targetTileCell->GetTileY())
		{
			GameSystem::GetInstance()->getStage()->CreatePathfindingMark(_reverseTilecell);
			_charcter->PushTileCell(_reverseTilecell);
		}
		_reverseTilecell = _reverseTilecell->GetPrevPathfindingCell();
		//_charcter->PushTileCell(_reverseTilecell);
	}
	else
	{
		_nextState = eStateType::ET_MOVE;
	}
	
}
void PathfindState::Start()
{
	State::Start();
	Statename = L"PathFind AI";

	_targetTileCell = _charcter->getTargetTileCell();

	//모든 타일셀 길찾기 관련 속성 초기화
	//맵에 규모 클시 특정사정거리까지만 초기화

	Map * map = GameSystem::GetInstance()->getStage()->getMap();
	int height = map->Getheight();
	int width = map->Getwidth();
	for (int y = 0; y < height; y++)
	{
		for (int x = width; x < width; x++)
		{
			TilePosition TileCellPostion;
			TileCellPostion.x = x;
			TileCellPostion.y = y;
			tileCell * tilecell = map->getTileCell(TileCellPostion);
			tilecell->initPathfinding();
		}
	}

	TilePosition CharcterPosition;
	CharcterPosition.x = _charcter->getTileX();
	CharcterPosition.y = _charcter->getTileY();


	tileCell * startTileCell = map->getTileCell(CharcterPosition);

	_pathfingTileQueue.push(startTileCell);

	_updateState = eUpdateState::PATHFINDING;
}
void PathfindState::Stop()
{
	State::Stop();

	for (int i = 0; i < _pathfingTileQueue.size(); i++)
	{
		_pathfingTileQueue.pop();
	}

}