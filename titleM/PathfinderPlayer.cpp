#include"Stage.h"
#include "Map.h"
#include "PathfinderPlayer.h"
#include "GameSystem.h"
#include "State.h"
#include "IdileState.h"
#include "PathfindState.h"
#include "PathfindingMovingState.h"
#include "PathfindImmediateState.h"

PathfinderPlayer::PathfinderPlayer(std::wstring name, std::wstring  scriptName, std::wstring  texutureName):player(name,scriptName,texutureName)
{
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

		//std::list<tileCell*>::insert itr=

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
	//ReplaceState(eStateType::ET_ATTACK, new IdleState());
	ReplaceState(eStateType::ET_PATHFINDING, new PathfindImmediateState());
}
