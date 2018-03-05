#pragma once
#include <d3dx9.h>
#include <vector>
#include <list>

#include "Component.h"
#include "GlobalType.h"
class Sprite;
class tileCell;


class Map : public Component
{
public:
	Map(std::wstring mapName);
	~Map();

	void init();
	void DeInit();
	void Update(float deltaTime);
	void render();
	void Release();
	void Reset();
	void Scroll(float deltaX,float deltaY);

private:
	std::vector<std::vector<tileCell*>> _tileMap;
	int _width;
	int _height;

	float _startX;
	float _startY;

	float _deltaX;
	float _deltaY;

	std::vector<Sprite*> _spriteList;

	int _tilesize = 32;

public:
	int GetPositionX(int tileX, int tileY);
	int GetPositionY(int tileX, int tileY);
	void setTileComponent(int tileX, int tileY, Component * com, bool isrender);

	std::list<Component*> getTileComponentList(int tilex, int tiley);
	void ResetTileComponent(int tileX, int tileY, Component * com);


	//bool CanMoveTileMap(int newTiltleX,int newTiltleY);
	bool CanMoveTileMap(TilePosition nextTilePos);


private:
	Component * _viewer;

public:
	void initViewer(Component * viewer);


	bool getTileColisonList(int newTiltleX,int newTiltleY,std::list<Component*>& colisionList);


	int Getheight();
	int Getwidth();



	//tileCell * getTileCell(int tileX, int tileY);
	tileCell * getTileCell(TilePosition diretion);

	tileCell * FindTileCellWithMousePostion(int mouseX,int mouseY);


private:
	void createMap();
	
};
