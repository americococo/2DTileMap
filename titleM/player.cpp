#include "player.h"
#include "GameSystem.h"
#include "ComponentSystem.h"
#include "Map.h"
#include "MoveState.h"
#include "IdileState.h"
#include "AttackState.h"
#include "DeffensState.h"
#include "DeadState.h"
#include "Stage.h"
#include "GlobalType.h"
player::player(std::wstring name, std::wstring  scriptName, std::wstring  texutureName):Charcter(name,scriptName,texutureName)
{
	componentType = eComponentType::CT_PLAYER;
	_attackpoint = 1;
	_hp = 5;

	_moveTime = 0.1;
}
player::~player() 
{

}
void player::UpdateAi(float deltaTime)
{
	{
		eDirection direction = eDirection::NONE;

		if (GameSystem::GetInstance()->IsKeyDown(VK_UP))
		{
			direction = UP;
		}
		if (GameSystem::GetInstance()->IsKeyDown(VK_DOWN))
		{
			direction = DOWN;
		}
		if (GameSystem::GetInstance()->IsKeyDown(VK_LEFT))
		{
			direction = LEFT;
		}
		if (GameSystem::GetInstance()->IsKeyDown(VK_RIGHT))
		{
			direction = RIGHT;
		}
		if (direction != eDirection::NONE)
		{
			_currentDirtion = direction;
			_state->NextState(eStateType::ET_MOVE);
		}

		//스페이스 -> 아이템 
		if (GameSystem::GetInstance()->IsKeyDown(VK_SPACE))
		{
			Map* map = GameSystem::GetInstance()->getStage()->getMap();
			std::list<Component*> componentList = map->getTileComponentList(_tileX, _tileY);
			for (std::list<Component*>::iterator itr = componentList.begin(); itr != componentList.end(); itr++)
			{
				Component * component = (*itr);
				if (eComponentType::CT_ITEM == component->GetType())
				{
					sComponentMsgParam msgParam;
					msgParam.sender = this;
					msgParam.message = L"use";
					msgParam.reciver = component;
					ComponentSystem::GetInstance()->SendMsg(msgParam);
				}
			}

			//내가 있는 타일에 아이템 검사
			//아이템 있으면 맵에서 제거
			//체력충전


			//내가 있는 타일에 아이템 검사
			//아이템 있으면 
			//아이템에 사용 메세지 보냄

		}


	}
}
Component * player::Colision(std::list<Component*>& colisionList)
{
	for (std::list<Component*>::iterator itr = colisionList.begin(); itr != colisionList.end(); itr++)
	{
		Component* component = (*itr);

		if (component->GetType() == eComponentType::CT_MONSTER || component->GetType() == eComponentType::CT_NPC)
		{
			return (*itr);
		}
	}
	return NULL;
}

void player::InitState()
{
	ReplaceState(eStateType::ET_IDLE, new IdleState());
	ReplaceState(eStateType::ET_MOVE, new MoveState());
	ReplaceState(eStateType::ET_ATTACK, new AttackState());
	ReplaceState(eStateType::ET_DEFFENS, new DeffensState());
	ReplaceState(eStateType::ET_DEAD, new DeadState());
}