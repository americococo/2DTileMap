#include "ComponentSystem.h"
#include <stdio.h>
#include <list>
#include "Map.h"

ComponentSystem::ComponentSystem()
{
	_componentMap.clear();
}
ComponentSystem * ComponentSystem::instance = NULL;

ComponentSystem * ComponentSystem::GetInstance()
{
	if (instance == NULL)
		instance = new ComponentSystem();
	return instance;
}

ComponentSystem::~ComponentSystem()
{

}

void ComponentSystem::AddComponent(std::wstring name, Component * com)
{
	if (NULL != com)
	{
		std::map<std::wstring, Component*>::iterator itr = _componentMap.find(name);
		if (itr == _componentMap.end())
		{
			_componentMap[name] = com;
		}
	}
}

Component * ComponentSystem::FindComponent(std::wstring name)
{
	std::map<std::wstring, Component*>::iterator itr = _componentMap.find(name);
	if (itr != _componentMap.end())
	{
		return	itr->second;
	}
	return 0;
}
Component * ComponentSystem::FindComponentInRange(Component* mapComp,Component *  chaser, int range, std::vector<eComponentType>compareTpye)
{
	//Map * map = (Map*)FindComponent(L"TestMap");
	Map * map = (Map*)mapComp;

	int MinTileX = chaser->getTileX() - range;
	int MaxTileX = chaser->getTileX() + range;

	int MinTileY = chaser->getTileY() - range;
	int MaxTileY = chaser->getTileY() + range;

	if (MinTileX < 0)
		MinTileX = 0;

	if (MaxTileX >= map->Getwidth())
		MaxTileX = map->Getwidth() - 1;

	if (MinTileY < 0)
		MinTileY = 0;

	if (MinTileY >= map->Getheight())
		MinTileY = map->Getheight() - 1;


	//Component * findEnemy = 0;


	//탐색거리에 적이있는지 검사
	{
		for (int y = MinTileY; y <= MaxTileY; y++)
		{
			for (int x = MinTileX; x <= MaxTileX; x++)
			{
				std::list<Component*> enemeyList;
				if (false == map->getTileColisonList(x, y, enemeyList))
				{
					for (std::list<Component*>::iterator itr = enemeyList.begin(); itr != enemeyList.end(); itr++)
					{
						Component * component = (*itr);
						if (true == component->getIsLive())
						{
							for (int i = 0; i < compareTpye.size(); i++)
							{
								if (compareTpye[i] == component->GetType())
								{
									return component;
								}
							}
						}
					}

				}

			}

		}

		return NULL;

	}

}

void ComponentSystem::RemoveAllComponets()
{
	for (std::map<std::wstring, Component*>::iterator itr = _componentMap.begin(); itr != _componentMap.end(); itr++)
	{
		delete itr->second;
	}
	_componentMap.clear();
}
void ComponentSystem::removeComponent(Component * tileCharcter)
{
	_componentMap.erase(tileCharcter->getName());
	delete tileCharcter;
	
}
void ComponentSystem::clearMessageQueue()
{
	while (0<_msgQueue.size())
	{
		_msgQueue.pop();
	}
}

void ComponentSystem::SendMsg(const sComponentMsgParam & msgParam)
{
	_msgQueue.push(msgParam);
}

void ComponentSystem::Update(float deltaTime)
{
	ProcessMessageQueue();
}

void ComponentSystem::ProcessMessageQueue()
{
	while (0<_msgQueue.size())
	{
		sComponentMsgParam msgParam = _msgQueue.front();
		_msgQueue.pop();
		msgParam.reciver->ReceiveMessage(msgParam);
	}
}