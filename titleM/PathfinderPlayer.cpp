#include "PathfinderPlayer.h"

#include "State.h"
#include "IdileState.h"
#include "PathfindState.h"
#include "PathfindingMovingState.h"
PathfinderPlayer::PathfinderPlayer(std::wstring name, std::wstring  scriptName, std::wstring  texutureName):player(name,scriptName,texutureName)
{
}

PathfinderPlayer::~PathfinderPlayer()
{
}

void PathfinderPlayer::UpdateAi(float deltTime)
{

}
void PathfinderPlayer::InitState()
{
	player::InitState();
	ReplaceState(eStateType::ET_MOVE, new PathfindingMovingState());
	//ReplaceState(eStateType::ET_ATTACK, new IdleState());
	ReplaceState(eStateType::ET_PATHFINDING, new PathfindState());
}
