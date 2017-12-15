#include "GlobalType.h"

TilePosition GetNextTilePostion(TilePosition currentTilePos,eDirection direction)
{
	TilePosition tilePostion = currentTilePos;
	switch (direction)
	{
	case eDirection::LEFT:
		tilePostion.x--;
		break;
	case eDirection::RIGHT:
		tilePostion.x++;
		break;
	case eDirection::UP:
		tilePostion.y--;
		break;
	case eDirection::DOWN:
		tilePostion.y++;
		break;
	}
	return tilePostion;
}
eDirection GetDirection(TilePosition to, TilePosition from)
{
	eDirection direction;

	direction = eDirection::NONE;

	if (to.x > from.x)
		direction = eDirection::RIGHT;
	else if (to.x < from.x)
		direction = eDirection::LEFT;

	else if (to.y > from.y)
		direction = eDirection::DOWN;
	else if ( to.y < from.y)
		direction =eDirection::UP;

	return direction;

}