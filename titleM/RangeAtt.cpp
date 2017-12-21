#include "RangeAtt.h"
#include "Monster.h"
#include "Charcter.h"
#include "Map.h"
#include "Stage.h"
#include "GameSystem.h"
RangeAtt::RangeAtt() {}
RangeAtt::~RangeAtt() {}
void RangeAtt::Start()
{
	State::Start();
	Statename = L"PathFind AI";

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

void RangeAtt::UpdatePathfinding()
{
	if (0 != _pathfingTileQueue.size())
	{
		//큐에 처음 값을 빼 검사
		//tileCell * tilecell = _pathfingTileQueue.top();
		sPathCommand command = _pathfingTileQueue.front();
		_pathfingTileQueue.pop();

		if (false == command.tilecell->IsPathfindMark())
		{
			command.tilecell->PathFinded();
			
			//목표타일 -> 종료

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
					float distanceFromStart = command.tilecell->getDistanceFromStart();

					if (distanceFromStart >= 10)
						return;

					if (NULL == nextTileCell->GetPrevPathfindingCell())
					{
						//거리우선 탐색 - 최단거리 d 모든 타일 탐색
						nextTileCell->SetDistanceFromStart(distanceFromStart);

						nextTileCell->SetPrevPathfindingCell(command.tilecell);

						sPathCommand newCommand;
						newCommand.tilecell = nextTileCell;
						_pathfingTileQueue.push(newCommand);

					}

				}
			}
		}

	}
	else
		_nextState = eStateType::ET_IDLE;

}
void RangeAtt::UpdateBuildPath()
{
	if (NULL != _reverseTilecell)
	{
		GameSystem::GetInstance()->getStage()->CreatePathfindingMark(_reverseTilecell);
		_charcter->PushTileCell(_reverseTilecell);
		_reverseTilecell = _reverseTilecell->GetPrevPathfindingCell();

		if (false == _reverseTilecell->canMove())
			return;
	}
}