#include "PathfindImmediateState.h"
PathfindImmediateState::PathfindImmediateState() {}
PathfindImmediateState::~PathfindImmediateState() {}

void PathfindImmediateState::Start()
{
	PathfindState::Start();
	
	while (0 != _pathfingTileQueue.size())
	{
		if (eUpdateState::BUILD_PATH == _updateState)
			break;
		UpdatePathfinding();
	}

	while (_reverseTilecell)
	{
		UpdateBuildPath();
	}
}