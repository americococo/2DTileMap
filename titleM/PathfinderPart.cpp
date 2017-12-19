#include "PathfinderPlayer.h"
#include "PathfinderMonster.h"
#include "PathfinderPart.h"

#include "LifeNPC.h"
#include "LifePlayer.h"

#include "Map.h"
#include "Stage.h"

#include "player.h"
#include "NPC.h"
#include "Monster.h"



PathfinderPart::PathfinderPart(Stage  * stage):StagePart(stage)
{

}
PathfinderPart::~PathfinderPart()
{

}
void PathfinderPart::CreateComponents(std::wstring mapName)
{
	StagePart::CreateComponents(mapName);

	//1개의 몬스터 생성
	//for (int i = 0; i < 1; i++)
	
		WCHAR name[256];
		wsprintf(name, L"Pathfindermonster_%d", 1);
		PathfinderMonster * _monster = new PathfinderMonster(name, L"monster", L"monster");
		_stage->AddStageComponent(_monster);
		
		_monster->initTilePostion(23, 23);

	//1개의 길찾기 전용 플레이어 생성
	player * _player = new PathfinderPlayer(L"player", L"player", L"player");
	_stage->AddStageComponent(_player);
	//_player->initTilePostion(2, 2);

	TilePosition monsterPosition;
	monsterPosition.x =_monster->getTileX();
	monsterPosition.y = _monster->getTileY();

	/*tileCell * targetCell = _stage->getMap()->getTileCell(monsterPosition);
	_player->SetTargetTileCell(targetCell);*/
	//뷰어 map 중간 타일로 지정

	int midTileX = _stage->getMap()->Getwidth() / 2;
	int midTileY = _stage->getMap()->Getheight() / 2;

	std::list<Component*> comList = _stage->getMap()->getTileComponentList(midTileX, midTileY);
	//_stage->getMap()->initViewer();

	_map->initViewer(comList.front());
}