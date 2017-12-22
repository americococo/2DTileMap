#pragma once
#include "PathfindState.h"
#include <queue>
#include "tileCell.h"
//class tileCell;


class RangeAtt : public PathfindState
{
public:
	RangeAtt();
	~RangeAtt();
	void Init(Charcter * charcter);

	void UpdatePathfinding();
	void UpdateBuildPath();
	void Start();
	void Update(float deltaTime);

private:
	std::queue<sPathCommand> _pathfingTileQueue;

	int range;
};