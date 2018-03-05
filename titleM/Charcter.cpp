#include "ComponentMessage.h"
#include "ComponentSystem.h"
#include "Font.h"
#include "MoveState.h"
#include "IdileState.h"
#include "AttackState.h"
#include "DeffensState.h"
#include "DeadState.h"
#include "Charcter.h"
#include "Sprite.h"
#include "tileCell.h"
#include "Stage.h"
#include "Map.h"
#include "GameSystem.h"

Charcter::Charcter(std::wstring name, std::wstring  scriptName, std::wstring  texture) : Component(name)
{
	_moveTime = 1.0f;
	_state = NULL;

	//_spriteVector.clear();
	_textureName = texture;
	_scriptName = scriptName;
	componentType = eComponentType::CT_NONE;

	_attackpoint = 1;
	_hp = 1;

	_attackCoolDownDuration = 0.0f;
	_attackCoolDown = 1.0f;

	

}
Charcter::~Charcter()
{
	delete _font;
}

void Charcter::init()
{
	{
		//Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent();

		Map* map = GameSystem::GetInstance()->getStage()->getMap();

		while (1)
		{
			_tileX = rand() % (map->Getwidth() - 2) + 1;
			_tileY = rand() % (map->Getheight() - 2) + 1;

			TilePosition CharcterNewPosition;
			CharcterNewPosition.x = _tileX;
			CharcterNewPosition.y = _tileY;

			if (true == map->CanMoveTileMap(CharcterNewPosition))
				break;
		}

		_x = map->GetPositionX(_tileX, _tileY);
		_y = map->GetPositionY(_tileX, _tileY);

		map->setTileComponent(_tileX, _tileY, this, false);
	}

	InitMove();

	InitState();

	ChangeState(eStateType::ET_IDLE);


	D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255);
	_font = new Font(L"Arial", 15, color);


	_font->SetRect(100, 100, 400, 100);
	UpdateText();

	level = 1;
}
void Charcter::InitState()
{
	ReplaceState(eStateType::ET_IDLE, new IdleState());
	ReplaceState(eStateType::ET_MOVE, new MoveState());
	ReplaceState(eStateType::ET_ATTACK, new AttackState());
	ReplaceState(eStateType::ET_DEFFENS, new DeffensState());
	ReplaceState(eStateType::ET_DEAD, new DeadState());
}
void Charcter::init(int tilex, int tiley)
{
	{
		Map* map = GameSystem::GetInstance()->getStage()->getMap();

		_tileX = tilex;
		_tileY = tiley;


		_x = map->GetPositionX(_tileX, _tileY);
		_y = map->GetPositionY(_tileX, _tileY);

		map->setTileComponent(_tileX, _tileY, this, false);
	}

	InitMove();

	InitState();

	ChangeState(eStateType::ET_IDLE);


	D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255);
	_font = new Font(L"Arial", 12, color);


	_font->SetRect(100, 100, 400, 100);
	UpdateText();
}
void Charcter::initTilePostion(int tilex, int tiley)
{
	Map* map = GameSystem::GetInstance()->getStage()->getMap();

	map->ResetTileComponent(_tileX, _tileY,this);

	_tileX = tilex;
	_tileY = tiley;


	_x = map->GetPositionX(_tileX, _tileY);
	_y = map->GetPositionY(_tileX, _tileY);

	map->setTileComponent(_tileX, _tileY, this, false);


}
void Charcter::DeInit()
{
	std::map<eStateType, State*>::iterator itr = _stateMap.begin();

	for (itr; itr != _stateMap.end(); itr++)
	{
		State * state = itr->second;
		delete state;
	}
	_stateMap.clear();
}
void Charcter::Update(float deltaTime)
{
	UpdateText();
	_state->Update(deltaTime);
	UpdateAttackCoolDown(deltaTime);
}
void Charcter::render()
{
	/*if (false == isLive)
	return;*/

	_state->Render();

	_font->setPosition(_x - 200, _y);
	_font->render();
}
void Charcter::Release()
{
	_state->Release();
}
void Charcter::Reset()
{
	_state->Reset();
}

void Charcter::UpdateAi(float deltaTime)
{
	_currentDirtion = (eDirection)(rand() % 4);
	ChangeState(eStateType::ET_MOVE);
}
void Charcter::ChangeState(eStateType stateTye)
{
	if (NULL != _state)
	{
		_state->Stop();
	}

	_state = _stateMap[stateTye];
	_state->Start();

}
void Charcter::ReplaceState(eStateType changeType, State * replaceState)
{
	std::map<eStateType, State*>::iterator itr = _stateMap.find(changeType);
	if (itr != _stateMap.end())
	{
		delete _stateMap[changeType];
		_stateMap.erase(changeType);
	}

	State * state = replaceState;
	state->Init(this);
	_stateMap[changeType] = state;
}
void Charcter::InitMove()
{
	_currentDirtion = eDirection::RIGHT;
	_isMoving = false;
	//이동 좌표
	_targetX = 0.0f;
	_targetY = 0.0f;

	//시간당 이동거리
	_moveDistancePerTimeX = 0.0f;
	_moveDistancePerTimeY = 0.0f;
}

Component * Charcter::Colision(std::list<Component*>& colisionList)
{
	//충돌
	for (std::list<Component*>::iterator itr = colisionList.begin(); itr != colisionList.end(); itr++)
	{
		sComponentMsgParam msgParam;
		msgParam.sender = this;
		msgParam.message = L"Colison";
		msgParam.reciver = (*itr);
		ComponentSystem::GetInstance()->SendMsg(msgParam);
	}
	return NULL;
}


void Charcter::MoveStart(int newTileX, int newTileY)
{
	//Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"TestMap");

	Map* map = GameSystem::GetInstance()->getStage()->getMap();

	//현재 컴퍼넌트에서 캐릭터 삭제
	map->ResetTileComponent(_tileX, _tileY, this);

	_tileX = newTileX;
	_tileY = newTileY;

	map->setTileComponent(_tileX, _tileY, this, false);

	//자연스러운 이동을 위한 보간
	{

		//이동겨리(방향가지고있음)
		_targetX = map->GetPositionX(_tileX, _tileY);
		_targetY = map->GetPositionY(_tileX, _tileY);

		float distanceX = _targetX - _x;
		float distanceY = _targetY - _y;

		//한번의 단위당 이동거리
		_moveDistancePerTimeX = distanceX / _moveTime;
		_moveDistancePerTimeY = distanceY / _moveTime;
	}
	_isMoving = true;
}

void Charcter::setPostition(float posX, float posY)
{
	_x = posX;
	_y = posY;
}

eDirection Charcter::getDirection()
{
	return _currentDirtion;
}

void Charcter::SetDirection(eDirection dirtion)
{
	_currentDirtion = dirtion;
}

float Charcter::getMoveTime()
{
	return _moveTime;
}

void Charcter::MoveStop()
{
	_isMoving = false;

	Map* map = GameSystem::GetInstance()->getStage()->getMap();
	_x = map->GetPositionX(_tileX, _tileY);
	_y = map->GetPositionY(_tileX, _tileY);

	_moveDistancePerTimeY = 0.0f;
	_moveDistancePerTimeX = 0.0f;
}
void Charcter::Moving(float deltaTime)
{
	float moveDistanceX = _moveDistancePerTimeX * deltaTime;
	float moveDistanceY = _moveDistancePerTimeY * deltaTime;

	_x += moveDistanceX;
	_y += moveDistanceY;
}

void Charcter::MoveDeltaPotion(float _deltaX, float _deltaY)
{
	_x += _deltaX;
	_y += _deltaY;
}

void Charcter::DecreaseHP(int decreasePoint)
{
	_hp -= decreasePoint;
	if (_hp <= 0)
	{
		isLive = false;
		_state->NextState(eStateType::ET_DEAD);
	}
}

void Charcter::ReceiveMessage(const sComponentMsgParam msgParam)
{
	if (L"Attack" == msgParam.message)
	{
		_attackedpoint = msgParam.attackpoint;
		_state->NextState(eStateType::ET_DEFFENS);
	}
}
int Charcter::getattackpoint()
{
	return _attackpoint;
}
Component * Charcter::getTarget()
{
	return _target;
}
void Charcter::ResetTarget()
{
	_target = NULL;
}
bool Charcter::IsCoolDown()
{
	if (_attackCoolDown <= _attackCoolDownDuration)
	{
		return true;
	}

	return false;
}
void Charcter::ResetCoolDown()
{
	_attackCoolDownDuration = 0.0f;
}
void Charcter::UpdateAttackCoolDown(float deltaTime)
{
	if (_attackCoolDownDuration < _attackCoolDown)
	{
		_attackCoolDownDuration += deltaTime;
	}
	else
	{
		_attackCoolDownDuration = _attackCoolDown;
	}
}

void Charcter::UpdateText()
{
	int coolTime = (int)(_attackCoolDownDuration * 1000.0f);
	coolTime -= (int)1000.0f;

	if (coolTime < 0)
		coolTime *= -1;

	WCHAR text[256];
	wsprintf(text, L"HP :%d\nCoolTime:%d\n\n state:%s", _hp, coolTime, _state->getStateName().c_str());
	_font->setText(text);
}

void Charcter::IncreaseHP(int incresepoint)
{
	_hp = _hp + incresepoint;

	if (_hp > 100)
		_hp = 100;
}

void Charcter::SetTargetTileCell(tileCell * tilecell)
{
	_targetTileCell = tilecell;
	_state->NextState(eStateType::ET_PATHFINDING);
}
void Charcter::ClearPathTileCellStack()
{
	while (false == _pathTileCellStack.empty())
	{
		_pathTileCellStack.pop();
	}
}