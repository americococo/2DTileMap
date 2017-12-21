#include "PathfinderMonster.h"
#include "IdileState.h"
PathfinderMonster::PathfinderMonster(std::wstring name, std::wstring  scriptName, std::wstring  texutureName):Monster(name,scriptName,texutureName)
{
	_hp = 3;
	_attackedpoint = 1;

	componentType = eComponentType::CT_MONSTER;
}

PathfinderMonster::~PathfinderMonster()
{
}
void PathfinderMonster::UpdateAi(float DeltaTime)
{

}
