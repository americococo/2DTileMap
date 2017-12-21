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

	//��� Ÿ�ϼ� ��ã�� ���� �Ӽ� �ʱ�ȭ
	//�ʿ� �Ը� Ŭ�� Ư�������Ÿ������� �ʱ�ȭ

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
		//ť�� ó�� ���� �� �˻�
		//tileCell * tilecell = _pathfingTileQueue.top();
		sPathCommand command = _pathfingTileQueue.front();
		_pathfingTileQueue.pop();

		if (false == command.tilecell->IsPathfindMark())
		{
			command.tilecell->PathFinded();
			
			//��ǥŸ�� -> ����

			for (int direction = 0; direction < eDirection::NONE; direction++)
			{
				TilePosition currentTilePos;
				currentTilePos.x = command.tilecell->GetTileX();
				currentTilePos.y = command.tilecell->GetTileY();
				TilePosition nextTilePos = GetNextTilePostion(currentTilePos, (eDirection)direction);

				Map * map = GameSystem::GetInstance()->getStage()->getMap();
				tileCell * nextTileCell = map->getTileCell(nextTilePos);

				//��ֹ� üũ Ž���� ������ üũ
				if ((true == map->CanMoveTileMap(nextTilePos) && false == nextTileCell->IsPathfindMark()) ||
					(nextTileCell->GetTileX() == _targetTileCell->GetTileX() && nextTileCell->GetTileY() == _targetTileCell->GetTileY()))
				{
					float distanceFromStart = command.tilecell->getDistanceFromStart();

					if (distanceFromStart >= 10)
						return;

					if (NULL == nextTileCell->GetPrevPathfindingCell())
					{
						//�Ÿ��켱 Ž�� - �ִܰŸ� d ��� Ÿ�� Ž��
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