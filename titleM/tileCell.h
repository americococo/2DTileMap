#pragma once
#include <list>


class Component;

class tileCell
{
private:
	float _posX;
	float _posY;

	std::list<Component*> _componentList;
	std::list<Component*>	_renderList;

	int _tileX;
	int _tileY;

public:
	tileCell(int tileX,int tileY);
	~tileCell();

	void setPostition(float posX, float Y);
	float GetPositionX();
	float GetPositionY();

	void render();
	void Update(float deltaTime);
	
	void Release();
	void Reset();
	void deInit();

	void AddComponent(Component *com, bool isrender);
	void RemoveAllComponets(Component * com);
	void moveDeltaPotion(float _deltaX, float _deltaY);

	bool canMove();

	bool GetcolisonList(std::list<Component*>& colisonList);


	std::list<Component*> GetComponentList();


public:
	int GetTileX() { return _tileX; }
	int GetTileY() { return _tileY; }
//paathfinding
private:

	//�˻�� Ÿ������ �ƴ���
	bool _isPathfinderMark;
	//���� Ÿ�� ���
	tileCell * _prevPathfindingCell;
	float _distanceWeigth; //Ÿ�� ���ٰ����� �� �ʷε��� ����
	float _distanceFromStart;//���� �Ÿ��� �����ϱ����� ����

public:
	void initPathfinding() { _isPathfinderMark = false; _prevPathfindingCell = NULL; _distanceFromStart = 0.0f; _heuryStic = 0.0f; }
	bool IsPathfindMark() { return _isPathfinderMark; }
	void PathFinded() { _isPathfinderMark = true; }


	tileCell *  GetPrevPathfindingCell() { return _prevPathfindingCell; }
	void SetPrevPathfindingCell(tileCell * tilecell) { _prevPathfindingCell = tilecell; }

	float getDistanceFromStart() { return _distanceFromStart; }
	void SetDistanceFromStart(float distanceFromStart) { _distanceFromStart = distanceFromStart; }
	float getDistanceWeight() { return _distanceWeigth; }


private:
	float _heuryStic;
public:
	void SetHeyrstic(float Heurstic) { _heuryStic = Heurstic; }
	float getHeuriStic() { return _heuryStic; }
	
};