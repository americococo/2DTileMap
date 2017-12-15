#pragma once
#include "State.h"
#include <queue>
#include "tileCell.h"
//class tileCell;

enum eUpdateState
{
	PATHFINDING,
	BUILD_PATH
};

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
	
	//pathFinding
	struct  compare
	{
		bool operator()(tileCell * a, tileCell * b)
		{
			return a->getDistanceFromStart() > b->getDistanceFromStart();
		}
	};


private:
	//std::queue<tileCell*> _pathfingTileQueue;
	std::priority_queue<tileCell*,std::vector<tileCell*>,compare> _pathfingTileQueue;
	tileCell * _targetTileCell;
	
	eUpdateState _updateState;

private:
	tileCell * _reverseTilecell;

public:
	void UpdatePathfinding();
	void UpdateBuildPath();


};

