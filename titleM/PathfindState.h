#pragma once
#include "State.h"
#include <queue>
#include "tileCell.h"
//class tileCell;


class PathfindState : public State
{
public:
	PathfindState();
	~PathfindState();

public:
	void Init(Charcter * charcter);
	void Update(float deltaTime);

	void Start();
	void Stop();

public:
	enum eUpdateState
	{
		PATHFINDING,
		BUILD_PATH
	};

	typedef struct _sPathCommand
	{
		float heuristic;
		tileCell * tilecell;
	}sPathCommand;

	//pathFinding
	struct  compare
	{
		bool operator()(sPathCommand&  a, sPathCommand&  b)
		{
			//return a->getDistanceFromStart() > b->getDistanceFromStart();
			return a.heuristic > b.heuristic;
		}
	};


protected:
	//std::queue<tileCell*> _pathfingTileQueue;
	std::priority_queue<sPathCommand,std::vector<sPathCommand>,compare> _pathfingTileQueue;
	tileCell * _targetTileCell;
	
	eUpdateState _updateState;

protected:
	tileCell * _reverseTilecell;

public:
	void UpdatePathfinding();
	void UpdateBuildPath();



	float CalcSimpleHeyristic(tileCell* tilecell, tileCell* nextTileCell, tileCell* _targetTileCell);//방향만 검사 현재 타일에서 목적지까지 방향
	float CalcComplexcHeuristic(tileCell * nextTilecell,tileCell * targetTileCell); //목적지까지 거리
	float CalcAStarHeuristic(float distanceFromStart, tileCell * nextTilecell, tileCell * targetTileCell);
};