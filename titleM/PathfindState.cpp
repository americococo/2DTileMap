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

	//ť�� ���ִ� �� "�ϳ���"! Ž��

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
		//ť�� ó�� ���� �� �˻�
		//tileCell * tilecell = _pathfingTileQueue.top();
		sPathCommand command = _pathfingTileQueue.top();
		_pathfingTileQueue.pop();

		if (false == command.tilecell->IsPathfindMark())
		{
			command.tilecell->PathFinded();

			wchar_t  tileCheck[256];
			swprintf(tileCheck, L"find TileCell X:%d Y:%d\n Target TileCell X:%d Y:%d\n", command.tilecell->GetTileX(), command.tilecell->GetTileY(), _charcter->getTargetTileCell()->GetTileX(), _charcter->getTargetTileCell()->GetTileY());
			OutputDebugString(tileCheck);


			//��ǥŸ�� -> ����
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

				//��ֹ� üũ Ž���� ������ üũ
				if ((true == map->CanMoveTileMap(nextTilePos) && false == nextTileCell->IsPathfindMark()) ||
					(nextTileCell->GetTileX() == _targetTileCell->GetTileX() && nextTileCell->GetTileY() == _targetTileCell->GetTileY()))
				{
					float distanceFromStart = command.tilecell->getDistanceFromStart()  + command.tilecell->getDistanceWeight();

					//float heuristic = CalcSimpleHeyristic(tilecell,nextTileCell,_targetTileCell);
					//float heuristic = CalcComplexcHeuristic(nextTileCell, _targetTileCell);
					float heuristic = CalcAStarHeuristic(distanceFromStart, nextTileCell, _targetTileCell);

					if (NULL == nextTileCell->GetPrevPathfindingCell())
					{
						//�Ÿ��켱 Ž�� - �ִܰŸ� d ��� Ÿ�� Ž��
						nextTileCell->SetDistanceFromStart(distanceFromStart);

						//�߰��� Ž�� - ���������� �Ÿ� Ž�� d ������������ (����� �Ÿ�) �߿�� x
						nextTileCell->SetHeyrstic(heuristic);

						//Ž���� ��ε��� �Ÿ� ��

						nextTileCell->SetPrevPathfindingCell(command.tilecell);

						//_pathfingTileQueue.push(nextTileCell);
						sPathCommand newCommand;
						newCommand.heuristic = heuristic;
						newCommand.tilecell = nextTileCell;
						_pathfingTileQueue.push(newCommand);

						//Ž������ Ž��
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
							//�ٽð˻�
							nextTileCell->SetDistanceFromStart(distanceFromStart);
							nextTileCell->SetPrevPathfindingCell(command.tilecell);
							//nextTileCell->SetHeyrstic(new ff); <- ����Ʈ�� ����, �����Ϳ��� �� �ϴ� �� ����, ť ����

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
		/*
		if (_reverseTilecell->GetTileX() != _targetTileCell->GetTileX()
		|| _reverseTilecell->GetTileY() != _targetTileCell->GetTileY())
		{
			GameSystem::GetInstance()->getStage()->CreatePathfindingMark(_reverseTilecell);
			_charcter->PushTileCell(_reverseTilecell);
		}
		*/

		//GameSystem::GetInstance()->getStage()->CreatePathfindingMark(_reverseTilecell);
		_charcter->PushTileCell(_reverseTilecell);
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
void PathfindState::Stop()
{
	State::Stop();

	//for (int i = 0; i < _pathfingTileQueue.size(); i++)
	//{
	//	_pathfingTileQueue.pop();
	//}

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

	//x :�߰����� ����
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
	
	//y :�߰����� ���� ����
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
	//distance = nextTilecell->getDistanceWeight();Ÿ���� ����ġ + �Ÿ� ����ġ

	return distance; 
}
float PathfindState::CalcAStarHeuristic(float distanceFromStart, tileCell * nextTilecell, tileCell * targetTileCell)
{
	return distanceFromStart + CalcComplexcHeuristic(nextTilecell, targetTileCell);
}