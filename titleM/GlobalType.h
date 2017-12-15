#pragma once

enum eDirection
{
	LEFT, RIGHT, UP, DOWN, NONE
};

typedef struct TilePosition
{
	 int x;
	 int y;
};
TilePosition  GetNextTilePostion(TilePosition currentTilePos, eDirection direction);
eDirection GetDirection(TilePosition to, TilePosition from);