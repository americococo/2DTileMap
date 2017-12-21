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


	void UpdatePathfinding();
	void UpdateBuildPath();
	void Start();

private:
	std::queue<sPathCommand> _pathfingTileQueue;


};