#include "ComponentSystem.h"

#include "Monster.h"
#include "MoveState.h"


#include "GameSystem.h"
#include "Stage.h"
#include "Map.h"

#include "GlobalType.h"
Monster::Monster(std::wstring name, std::wstring  scriptName, std::wstring  textureName) :Charcter(name, scriptName, textureName)
{
	componentType = eComponentType::CT_MONSTER;

	int speed = (rand() % 1) + 300;
	_moveTime = (float)speed / 1000.0f;

	_attackpoint = 1;
	_hp = 5;
}

Monster::~Monster()
{

}
void Monster::UpdateAi(float deltaTime)
{

	{
		std::vector<eComponentType> compareTpyeList;
		compareTpyeList.push_back(eComponentType::CT_NPC);
		compareTpyeList.push_back(eComponentType::CT_PLAYER);
		Map* map = GameSystem::GetInstance()->getStage()->getMap();
		Component * findEnemy = ComponentSystem::GetInstance()->FindComponentInRange(map, this, 5, compareTpyeList);



		if (NULL != findEnemy)
		{
			//적을 찾았즘 추격& 방향 설정
			eDirection direction = eDirection::NONE;
			if (findEnemy->getTileX() < _tileX)
			{
				direction = eDirection::LEFT;
			}
			else if (findEnemy->getTileX() > _tileX)
			{
				direction = eDirection::RIGHT;
			}
			else if (findEnemy->getTileY() < _tileY)
			{
				direction = eDirection::UP;
			}
			else if (findEnemy->getTileY() > _tileY)
			{
				direction = eDirection::DOWN;
			}

			if (eDirection::NONE != direction)
			{
				_currentDirtion = direction;
				_state->NextState(eStateType::ET_MOVE);
			}
		}
		else
		{
			Charcter::UpdateAi(deltaTime);
		}

	}

}

Component * Monster::Colision(std::list<Component*>& colisionList)
{
	for (std::list<Component*>::iterator itr = colisionList.begin(); itr != colisionList.end(); itr++)
	{
		Component * com = (*itr);
		if (com->GetType() == eComponentType::CT_NPC || com->GetType() == eComponentType::CT_PLAYER)
		{
			return  (*itr);
		}
	}
	return NULL;
}