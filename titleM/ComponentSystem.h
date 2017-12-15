#pragma once

#include "Component.h"
#include <queue>
#include <Windows.h>
#include <string>
#include <vector>
#include <map>
//╫л╠шео

struct sComponentMsgParam;
class ComponentSystem
{
private:
	ComponentSystem();
	static ComponentSystem * instance;

public:
	static ComponentSystem * GetInstance();

public:
	~ComponentSystem();

private:
	std::map<std::wstring, Component*> _componentMap;


public:
	void RemoveAllComponets();
	void ComponentSystem::removeComponent(Component * tileCharcter);
	void AddComponent(std::wstring name, Component * com);
	Component * FindComponent(std::wstring name);
public:
	Component * FindComponentInRange(Component* mapComp, Component *  chaser, int range, std::vector<eComponentType> compareTpye);

private:
	std::queue<sComponentMsgParam> _msgQueue;
public:
	void clearMessageQueue();



public:
	//void sendMessage(Component * sender, Component * reciver, std::wstring message);
	void SendMsg(const sComponentMsgParam & msgParam);
	void ProcessMessageQueue();
	void Update(float deltaTime);

};