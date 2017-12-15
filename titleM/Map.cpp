#include "Map.h"
#include "Sprite.h"
#include "tileCell.h"
#include "TileObject.h"
#include "LifeTileObject.h"
#include "GameSystem.h"
#include <fstream>

Map::Map(std::wstring name) :Component(name)
{
	_deltaY = _startX = _startY = _deltaX = 0.0f;

	_tilesize = 32;
	_spriteList.clear();
}
Map::~Map()
{

}

void Map::DeInit()
{
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			//_testTiltleMap[x][y]->deInit();
			_tileMap[y][x]->deInit();
			delete _tileMap[y][x];
		}
	}
}
void Map::init()
{
	/*
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			Sprite * sprite;
			int randValue = rand() % 4;
			switch (randValue)
			{
			case 0:
				sprite = new Sprite(L"character_sprite.png", L"character_sprite_01.json"); break;
			case 1:
				sprite = new Sprite(L"character_sprite.png", L"character_sprite_02.json"); break;
			case 2:
				sprite = new Sprite(L"character_sprite.png", L"character_sprite_03.json"); break;
			case 3:
				sprite = new Sprite(L"character_sprite.png", L"character_sprite_04.json"); break;
			default:
				break;
			}
			sprite->Init();
			_testTiltleMap[x][y] = sprite;
		}
	}
	*/
	//맵용 스프트라이트 리스트 작업

	//16x16 개의 타일 생성(32x32크기의 타일)
	//찍을 인덱스 순서대로 리스트에 pushback

	int srcX = 0;
	int srcY = 0;

	_height = 16;
	_width = 16;

	int tileSize = 32;


	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			Sprite * SpriteM = new Sprite(L"MapSprite.png", L"MapSprite.json");

			SpriteM->Init(srcX, srcY, 32, 32, 1.0f);
			_spriteList.push_back(SpriteM);

			srcX += tileSize;
		}

		srcX = 0;
		srcY += tileSize;
	}

	std::wstring wName = _name;
	std::string name = "";
	name.assign(wName.begin(), wName.end());

	char layer01Name[256];
	sprintf(layer01Name, "%sMapData_layer1.csv", name.c_str());

	char layer02Name[256];
	sprintf(layer02Name, "%sMapData_layer2.csv", name.c_str());

	//1 layer load
	{
		int line = 0;
		int row=0;
		char record[1024 * 4];
		std::ifstream infile(layer01Name);
		while (!infile.eof())
		{
			infile.getline(record, 1024 * 4);

			char *token = strtok(record, ",");
			switch (line)
			{
			case 0:
				if (NULL != token)
				{
					token = strtok(NULL, ",");
					_width = atoi(token);
					token = strtok(NULL, ",");
					_height = atoi(token);
				}
				break;
			case 1://무시
				break;
			default:
				//맵데이터
				if (NULL != token)
				{
					std::vector<tileCell*> rowList;
					for (int x = 0; x < _width; x++)
					{
						int index = atoi(token);

						tileCell* tilecell = new tileCell(x,row);
						WCHAR componetName[256];
						wsprintf(componetName, L"MapData_layer1_%d_%d", line, x);
						//tileobject가 컴퍼넘프 추가
						TileObject * tileObject = new TileObject(componetName, _spriteList[index],x,row);

						//test
						switch (index)
						{
						case 238: //2
							tileObject->setDistanceWeight(2.0f);
							break;
						case 50: //.5
							tileObject->setDistanceWeight(0.1f);
							break;
						case 23:
							tileObject->setDistanceWeight(1.0f);
							break;
						}

						tileObject->setCanMove(true);
						tilecell->AddComponent(tileObject, true);
						rowList.push_back(tilecell);
						token = strtok(NULL, ",");
					}
					_tileMap.push_back(rowList);
					row++;
				}
				break;
			}
			line++;
		}

	}

	//2nd layer load
	{
		int row = 0;
		int line = 0;
		char record[1024 * 4];
		std::ifstream infile(layer02Name);
		while (!infile.eof())
		{
			infile.getline(record, 1024 * 4);

			char *token = strtok(record, ",");
			switch (line)
			{
			case 0:
				break;
			case 1:
				break;

			default:
				//맵데이터
				if (NULL != token)
				{
					std::vector<tileCell*> rowList = _tileMap[row];
					for (int x = 0; x < _width; x++)
					{
						int index = atoi(token);
						tileCell* tilecell = rowList[x];
						WCHAR componetName[256];
						wsprintf(componetName, L"1MapData_layer2_%d_%d", line, x);

						if (0 <= index)
						{
							if (100100 == index)
							{
								//tileobject가 컴퍼넘프 추가
								LifeTileObject * tileObject = new LifeTileObject(x, row, componetName, _spriteList[20]);
								tileObject->setCanMove(true);
								tilecell->AddComponent(tileObject, true);
							}
							else
							{
								//tileobject가 컴퍼넘프 추가
								TileObject * tileObject = new TileObject(componetName, _spriteList[index],x,row);
								tileObject->setCanMove(false);
								tilecell->AddComponent(tileObject, true);

							}
						}

						token = strtok(NULL, ",");
					}
					row++;
				}
				break;
			}
			line++;
		}

	}

}
void Map::Update(float deltaTime)
{
	int midX = GameSystem::GetInstance()->GetWidth() / 2;
	int midY = GameSystem::GetInstance()->GetHeight() / 2;

	//뷰어의 위치를 기준으로 시작 픽셀 위치를 계산
	_startX = (-_viewer->getTileX()*_tilesize) + midX - _tilesize / 2;
	_startY = (-_viewer->getTileY()*_tilesize) + midY - _tilesize / 2;

	//해당위치에 타일그림
	float posX = _startX;
	float posY = _startY;

	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			posX += _tilesize;
			_tileMap[y][x]->setPostition(posX, posY);
			_tileMap[y][x]->Update(deltaTime);
		}
		posX = _startX;
		posY += _tilesize;
	}
	
}
void Map::render()
{
	int midX = GameSystem::GetInstance()->GetWidth() / 2;
	int midY = GameSystem::GetInstance()->GetHeight() / 2;

	int otter = 5;

	int minX = _viewer->getTileX() - (midX / _tilesize) - otter;
	int maxX = _viewer->getTileX() + (midX / _tilesize) + otter;

	int minY = _viewer->getTileY() - (midY / _tilesize) - otter;
	int maxY = _viewer->getTileY() + (midY / _tilesize) + otter;

	//범위가 벗어날경우 보정
	if (minX < 0)
		minX = 0;

	if (_width <= maxX)
		maxX = _width;

	if (minY < 0)
		minY = 0;

	if (_height <= maxY)
		maxY = _height;

	for (int y = minY; y < maxY; y++)
	{
		for (int x = minX; x < maxX; x++)
		{
			_tileMap[y][x]->render();
		}
	}

}
void Map::Release()
{
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			_tileMap[y][x]->Release();
		}
	}
}

void Map::Reset()
{
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			_tileMap[y][x]->Reset();
		}
	}
}

void Map::Scroll(float deltaX, float deltaY)
{
	_deltaX = deltaX;
	_deltaY = deltaY;
}

int Map::GetPositionX(int tileX, int tileY)
{
	return _tileMap[tileY][tileX]->GetPositionX();
}

int Map::GetPositionY(int tileX, int tileY)
{
	return _tileMap[tileY][tileX]->GetPositionY();
}
void Map::setTileComponent(int tileX, int tileY, Component * com, bool isrender)
{
	_tileMap[tileY][tileX]->AddComponent(com, isrender);
}
void Map::ResetTileComponent(int tileX, int tileY, Component * com)
{
	_tileMap[tileY][tileX]->RemoveAllComponets(com);
}

bool Map::CanMoveTileMap(TilePosition diretion)
{
	if (0 >= diretion.x)
		return false;
	if (_width <= diretion.x)
		return false;

	if (_height <= diretion.y)
		return false;

	if (0 >= diretion.y)
		return false;

	return _tileMap[diretion.y][diretion.x]->canMove();
}

bool Map::getTileColisonList(int newTiltleX, int newTiltleY, std::list<Component*>& colisionList)
{
	if (0 >= newTiltleX)
		return false;
	if (_width <= newTiltleX)
		return false;

	if (_height <= newTiltleY)
		return false;

	if (0 >= newTiltleY)
		return false;

	return _tileMap[newTiltleY][newTiltleX]->GetcolisonList(colisionList);
}

int Map::Getheight()
{
	return _height;
}

int Map::Getwidth()
{
	return _width;
}

void Map::initViewer(Component * viewer)
{
	_viewer = viewer;

	//뷰어를 중심으로 랜더링할 영역을 구함
	//영역
	//최소x=뷰어의 현재 타일 x의 위치-(중심축의x좌표/타일 크기)-1 
	//최소y=뷰어의 현재 타일 y의 위치-(중심축의y좌표/타일 크기)-1
	//최대X=뷰어의 현재 타일 x의 위치+(중심축의x좌표/타일 크기)+1
	//최대y=뷰어의 현재 타일 y의 위치+(중심축의y좌표/타일 크기)+1

	int midX = GameSystem::GetInstance()->GetWidth() / 2;
	int midY = GameSystem::GetInstance()->GetHeight() / 2;

	//뷰어의 위치를 기준으로 시작 픽셀 위치를 계산
	_startX = (-_viewer->getTileX()*_tilesize) + midX - _tilesize / 2;
	_startY = (-_viewer->getTileY()*_tilesize) + midY - _tilesize / 2;

	//해당위치에 타일그림
	float posX = _startX;
	float posY = _startY;

	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			posX += _tilesize;
			_tileMap[y][x]->setPostition(posX, posY);
		}
		posX = _startX;
		posY += _tilesize;
	}

}


std::list<Component*> Map::getTileComponentList(int tilex, int tiley)
{
	return _tileMap[tiley][tilex]->GetComponentList();
}

//
//tileCell * Map::getTileCell(int tileX, int tileY)
//{
//	return _tileMap[tileY][tileX];
//}
//

tileCell * Map::getTileCell(TilePosition diretion)
{
	return _tileMap[diretion.y][diretion.x];
}
