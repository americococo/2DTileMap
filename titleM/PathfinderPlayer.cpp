#include"Stage.h"
#include "Map.h"

#include "GameSystem.h"
#include "State.h"
#include "IdileState.h"

#include "PathfindState.h"
#include "PathfinderPlayer.h"
#include "PathfindingMovingState.h"
#include "PathfindImmediateState.h"

PathfinderPlayer::PathfinderPlayer(std::wstring name, std::wstring  scriptName, std::wstring  texutureName):player(name,scriptName,texutureName)
{
	_attackedpoint = 1;
}

PathfinderPlayer::~PathfinderPlayer()
{
}

void PathfinderPlayer::UpdateAi(float deltTime)
{
	//mouse input ó��l
	if(GameSystem::GetInstance()->IsMouseDown())
	{
		int mouseX = GameSystem::GetInstance()->GetMouseX();
		int mouseY = GameSystem::GetInstance()->GetMouseY();
		tileCell * targetTilecell = GameSystem::GetInstance()->getStage()->getMap()->FindTileCellWithMousePostion(mouseX, mouseY);

		if ((targetTilecell->GetTileX() == _tileX) && (targetTilecell->GetTileY() == _tileY))
			targetTilecell = NULL;

		if (NULL != targetTilecell)
		{
			SetTargetTileCell(targetTilecell);
		}
	}
}
void PathfinderPlayer::InitState()
{
	player::InitState();
	ReplaceState(eStateType::ET_MOVE, new PathfindingMovingState());
	ReplaceState(eStateType::ET_PATHFINDING, new PathfindImmediateState());
}
