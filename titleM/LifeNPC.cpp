#include "LifeNPC.h"
#include "ComponentSystem.h"
#include "State.h"
LifeNPC::LifeNPC(std::wstring name, std::wstring  scriptName, std::wstring  textureName):Charcter(name,scriptName,textureName)
{
	componentType = eComponentType::CT_NPC;
}
LifeNPC::~LifeNPC()
{

}
void LifeNPC::UpdateAi(float deltaTime)
{

}
void LifeNPC::render()
{
	_state->Render();

}