#include "LifeTileObject.h"
#include "Sprite.h"
#include "Stage.h"
#include "GameSystem.h"
#include "Map.h"
LifeTileObject::LifeTileObject(int tileX, int tileY, std::wstring name, Sprite * sprite) : TileObject(name, sprite,tileX,tileY)
{
	_sprite = sprite;
	_tileX = tileX;
	_tileY = tileY;

	componentType = eComponentType::CT_TILE_OBJECT;
}

LifeTileObject::~LifeTileObject()
{

}
void LifeTileObject::Update(float deltaTime)
{
	TileObject::Update(deltaTime);

	//주변 8칸 탐색 캐릭터 몇마리 있는지 
	Map* map = GameSystem::GetInstance()->getStage()->getMap();

	int range = 1;

	int MinTileX = _tileX - range;
	int MaxTileX = _tileX+ range;
	int MinTileY = _tileY - range;
	int MaxTileY = _tileY + range;

	if (MinTileX < 0) MinTileX = 0;

	if (MaxTileX >= map->Getwidth())	MaxTileX = map->Getwidth() - 1;

	if (MinTileY < 0) MinTileY = 0;

	if (MinTileY >= map->Getheight()) MinTileY = map->Getheight() - 1;


	int LifeGamecount = 0;
	//bool isTileCharcter;
	Component * tileCharcter=NULL;

	//탐색거리에 적이있는지 검사
	
		for (int y = MinTileY; y <= MaxTileY; y++)
		{
			for (int x = MinTileX; x <= MaxTileX; x++)
			{
				if (x != _tileX || y != _tileY)
				{
					std::list<Component*> compoentList;
					if (false == map->getTileColisonList(x, y, compoentList))
					{
						for (std::list<Component*>::iterator itr = compoentList.begin(); itr != compoentList.end(); itr++)
						{
							Component * compoent = (*itr);
							switch (compoent->GetType())
							{
							case eComponentType::CT_NPC:
							case eComponentType::CT_PLAYER:
							//	isTileCharcter = true;
								LifeGamecount++;
								break;
							}
						}
					}
				}
				else
				{
					std::list<Component*> compoentList;
					if (false == map->getTileColisonList(x, y, compoentList))
					{
						for (std::list<Component*>::iterator itr = compoentList.begin(); itr != compoentList.end(); itr++)
						{
							Component * compoent = (*itr);
							switch (compoent->GetType())
							{
							case eComponentType::CT_NPC:
							case eComponentType::CT_PLAYER:
								//	isTileCharcter = true;
								tileCharcter = compoent;
								break;
							}
						}
					}
				}
				
			}
		}
	
		if (3 == LifeGamecount)
		{
			if (NULL == tileCharcter)
			{
				//GameSystem::GetInstance()->getStage()->creatLifeNPC(_tileX, _tileY);
				GameSystem::GetInstance()->getStage()->createLifeNPC(this);
			}
		}
		else if(2==LifeGamecount)
		{
			//skip
		}
		else
		{
			if (NULL != tileCharcter)
			{
				if (eComponentType::CT_PLAYER != tileCharcter->GetType())
				{
					//GameSystem::GetInstance()->getStage()->destoryLifeNPC(_tileX, _tileY,tileCharcter);
					GameSystem::GetInstance()->getStage()->CheckDestoryLifeNPC(tileCharcter);
					tileCharcter = NULL;
				}
			}
		}
}