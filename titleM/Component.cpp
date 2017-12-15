#include "Component.h"
#include "ComponentSystem.h"
#include <string>
Component::Component(std::wstring name)
{
	_name = name;
	_canMove = false;
	ComponentSystem::GetInstance()->AddComponent(name, this);

	_moveDistancePerTimeX = 0.0f;
	_moveDistancePerTimeY = 0.0f;

	componentType = eComponentType::CT_NONE;
	isLive = true;
}
Component::~Component()
{
	 
}

void Component::ReceiveMessage(const sComponentMsgParam msgParam)
{
	if (L"Colison" == msgParam.message)
	{
		
	}

}