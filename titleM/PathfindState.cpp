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
		//tileCell * tilecell = _pathfingTileQueue.top();
		sPathCommand command = _pathfingTileQueue.top();
		_pathfingTileQueue.pop();

		if (false == command.tilecell->IsPathfindMark())
		{
			command.tilecell->PathFinded();

			wchar_t  tileCheck[256];
			swprintf(tileCheck, L"find TileCell X:%d Y:%d\n Target TileCell X:%d Y:%d\n", command.tilecell->GetTileX(), command.tilecell->GetTileY(), _charcter->getTargetTileCell()->GetTileX(), _charcter->getTargetTileCell()->GetTileY());
			OutputDebugString(tileCheck);


			//목표타일 -> 종료
			if (command.tilecell->GetTileX() == _targetTileCell->GetTileX() && command.tilecell->GetTileY() == _targetTileCell->GetTileY())
			{
				std::list<Component*> com = _targetTileCell->GetComponentList();
				for (std::list<Component*>::iterator itr = com.begin(); itr != com.end(); itr++)
				{

					if (eComponentType::CT_MONSTER == (*itr)->GetType())
					{
						Charcter * monster = (Charcter*)(*itr);
						tileCell * prev = command.tilecell->GetPrevPathfindingCell();

						if (command.tilecell->GetTileX() < prev->GetTileX())
							_charcter->SetDirection(eDirection::RIGHT);
						else if (prev->GetTileX() <command.tilecell->GetTileX())
							_charcter->SetDirection(eDirection::LEFT);
						else if (prev->GetTileY() < command.tilecell->GetTileY())
							_charcter->SetDirection(eDirection::UP);
						else if (command.tilecell->GetTileY() < prev->GetTileY())
							_charcter->SetDirection(eDirection::DOWN);
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
				currentTilePos.x = command.tilecell->GetTileX();
				currentTilePos.y = command.tilecell->GetTileY();
				TilePosition nextTilePos = GetNextTilePostion(currentTilePos, (eDirection)direction);

				Map * map = GameSystem::GetInstance()->getStage()->getMap();
				tileCell * nextTileCell = map->getTileCell(nextTilePos);

				//장애물 체크 탐색한 길인지 체크
				if ((true == map->CanMoveTileMap(nextTilePos) && false == nextTileCell->IsPathfindMark()) ||
					(nextTileCell->GetTileX() == _targetTileCell->GetTileX() && nextTileCell->GetTileY() == _targetTileCell->GetTileY()))
				{
					float distanceFromStart = command.tilecell->getDistanceFromStart()  + command.tilecell->getDistanceWeight();

					//float heuristic = CalcSimpleHeyristic(tilecell,nextTileCell,_targetTileCell);
					//float heuristic = CalcComplexcHeuristic(nextTileCell, _targetTileCell);
					float heuristic = CalcAStarHeuristic(distanceFromStart, nextTileCell, _targetTileCell);

					if (NULL == nextTileCell->GetPrevPathfindingCell())
					{
						//거리우선 탐색 - 최단거리 d 모든 타일 탐색
						nextTileCell->SetDistanceFromStart(distanceFromStart);

						//발견적 탐색 - 목적지까지 거리 탐색 d 목적지까지의 (경로의 거리) 중요시 x
						nextTileCell->SetHeyrstic(heuristic);

						//탐색된 경로들의 거리 비교

						nextTileCell->SetPrevPathfindingCell(command.tilecell);

						//_pathfingTileQueue.push(nextTileCell);
						sPathCommand newCommand;
						newCommand.heuristic = heuristic;
						newCommand.tilecell = nextTileCell;
						_pathfingTileQueue.push(newCommand);

						//탐색범위 탐색
						//if ((nextTileCell->GetTileX() != _targetTileCell->GetTileX() || nextTileCell->GetTileY() != _targetTileCell->GetTileY())
						//	&& (nextTileCell->GetTileX() != _charcter->getTileX() || nextTileCell->GetTileY() != _charcter->getTileY()))
						//{
						//	GameSystem::GetInstance()->getStage()->CreatePathfinderNPC(nextTileCell);
						//}
					}

					else
					{
						if (distanceFromStart < nextTileCell->getDistanceFromStart())
						{
							//다시검사
							nextTileCell->SetDistanceFromStart(distanceFromStart);
							nextTileCell->SetPrevPathfindingCell(command.tilecell);
							//nextTileCell->SetHeyrstic(new ff); <- 포인트가 들어간후, 포인터에서 비교 하는 값 조작, 큐 고장

							sPathCommand newCommand;
							newCommand.heuristic = CalcAStarHeuristic(distanceFromStart,nextTileCell,_targetTileCell);
							newCommand.tilecell = nextTileCell;
							_pathfingTileQueue.push(newCommand);
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
		_charcter->PushTileCell(_reverseTilecell);
		_reverseTilecell = _reverseTilecell->GetPrevPathfindingCell();
		
		if (false == _reverseTilecell->canMove())
			return;
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
		for (int x = 0; x < width; x++)
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

	sPathCommand newCommand;
	newCommand.heuristic = 0.0f;
	newCommand.tilecell = startTileCell;

	_pathfingTileQueue.push(newCommand);

	_updateState = eUpdateState::PATHFINDING;
}
void PathfindState::Stop()
{
	State::Stop();

	while (false == _pathfingTileQueue.empty())
	{
		_pathfingTileQueue.pop();
	}

}

float PathfindState::CalcSimpleHeyristic(tileCell* tilecell, tileCell* nextTileCell, tileCell* _targetTileCell)
{
	float heuristic = 0.0f;

	int diffFromCurrent = 0;
	int diffFromNext = 0;

	//x :발견적값 갱신
	{
		diffFromCurrent= tilecell->GetTileX()-_targetTileCell->GetTileX();
		if (diffFromCurrent < 0) diffFromCurrent = -diffFromCurrent;
		
		diffFromNext =nextTileCell->GetTileX() - _targetTileCell->GetTileX();
		if (diffFromNext < 0)diffFromNext = -diffFromNext;

		if (diffFromNext < diffFromCurrent)
		{
			heuristic -= 1.0f;
		}
		else if (diffFromNext > diffFromCurrent)
		{
			heuristic += 1.0f;
		}

	}
	
	//y :발견적값 누적 갱신
	{
		diffFromCurrent = tilecell->GetTileY() - _targetTileCell->GetTileY();
		if (diffFromCurrent < 0) diffFromCurrent = -diffFromCurrent;

		diffFromNext = nextTileCell->GetTileY() - _targetTileCell->GetTileY();
		if (diffFromNext < 0)diffFromNext = -diffFromNext;

		if (diffFromNext < diffFromCurrent)
		{
			heuristic -= 1.0f;
		}

		else if (diffFromNext > diffFromCurrent)
		{
			heuristic += 1.0f;
		}
	}

	//if (nexttilecell->getdistanceweight() < tilecell->getdistanceweight())
	//{
	//	heuristic -= 1.0f;
	//}
	//else if (nexttilecell->getdistanceweight() > tilecell->getdistanceweight())
	//{
	//	heuristic += 1.0f;
	//}

	heuristic += nextTileCell->getDistanceWeight() - tilecell->getDistanceWeight();

	

	return heuristic;
		
}
float PathfindState::CalcComplexcHeuristic(tileCell * nextTilecell, tileCell * targetTileCell)
{
	int distanceW = nextTilecell->GetTileX() - targetTileCell->GetTileX();
	int distanceH = nextTilecell->GetTileY() - targetTileCell->GetTileY();

	distanceH *= distanceH;
	distanceW *= distanceW;

	float distance = (float)sqrtf((double)distanceH + (double)distanceW);
	//distance = nextTilecell->getDistanceWeight();타일의 가중치 + 거리 가중치

	return distance; 
}
float PathfindState::CalcAStarHeuristic(float distanceFromStart, tileCell * nextTilecell, tileCell * targetTileCell)
{
	return distanceFromStart + CalcComplexcHeuristic(nextTilecell, targetTileCell);
}