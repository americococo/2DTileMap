#pragma once
#include <map>
#include <Windows.h>
#include <list>
#include <string>

class Component;
class Map;
class StagePart;
class tileCell;

class Stage
{
private:
	std::list<Component*> _compoentList;
	Map * _map;
public:
	Stage();
	~Stage();
	
public:
	void Init(std::wstring mapName);
	void Update(float deltaTime);
	void render();
	void Release();
	void Reset();

public:
	Map * getMap(){	return _map;}
	void SetMap(Map *map) { _map = map; }

private:
	std::list<Component*> _removeComponentList;
	std::list<Component*> _createBaseComponentList;

public:
	void createLifeNPC(Component * com);
	void destoryLifeNPC(int _tileX,int  _tileY,Component * tileCharcter);


public:
	void UpdateCreateCompoentList();
	void UdateRemoveCompentList();


public:
	void CheckDestoryLifeNPC(Component * tileCharcter);

private:
	StagePart * _loader;

	std::map<std::wstring,StagePart*> _partMap;
public:
	StagePart * GetStageParts(std::wstring mapName);


public:
	void AddStageComponent(Component * component);
	void CreatePathfinderNPC(tileCell * tilecell);

	void CreatePathfindingMark(tileCell * tilecell);
};
