#pragma once
#include <map>
//#include <d3dx9.h>
#include "Component.h"
#include <vector>
#include <string>
#include <list>
#include <stack>
#include "GlobalType.h"

class Font;
class Sprite;
//class MoveState;
//class IdleState;
class State;
class tileCell;

struct EquipItem;

enum eStateType
{
	ET_IDLE,
	ET_MOVE,
	ET_ATTACK,
	ET_DEFFENS,
	ET_DEAD,
	ET_PATHFINDING,
	ET_NONE
};

class Charcter : public Component
{

public:
	Charcter(std::wstring name, std::wstring  scriptName, std::wstring  texture);
	virtual ~Charcter();

	void init();
	void InitMove();
	void DeInit();
	void Update(float deltaTime);
	void render();
	void Release();
	void Reset();



	std::wstring GetTextureFiFName() { return _textureName; }
	std::wstring GetScriptFileName() { return _scriptName; }

protected:
	float _x;
	float _y;


public:
	float GetX() { return _x; }
	float GetY() { return _y; }

	//캐릭터이동

public:
	//ai
	void MoveStart(int newTileX, int newTileY);
	void setPostition(float posX, float posY);
	eDirection getDirection();
	void SetDirection(eDirection dirtion);
	float getMoveTime();

	void MoveStop();
	void Moving(float deltaTime);
	bool IsMoving() { return _isMoving; }

	void ChangeState(eStateType stateType);
	void ReplaceState(eStateType changeType, State * replaceState);
	virtual void UpdateAi(float deltaTime);
	virtual void MoveDeltaPotion(float _deltaX, float _deltaY);

	//State
protected:
	std::map<eStateType, State*> _stateMap;
public:
	virtual void InitState();


protected:
	std::wstring _textureName;
	std::wstring _scriptName;
	//std::vector<Sprite*> _spriteVector;



	//MoveState * _state;
	//IdleState * _state;

	State * _state;


	float _moveTime;
	/*
	float _movingDurtion;
	*/
	bool _isMoving;
	int _hp;



protected:
	eDirection _currentDirtion;

	float _targetX;
	float _targetY;


public:
	virtual Component * Colision(std::list<Component*>& colisionList);
	void ReceiveMessage(const sComponentMsgParam msgParam);
	void SetTarget(Component * target) { _target = target; }

	//common
public:
	void DecreaseHP(int decreasePoint);
	void IncreaseHP(int incresepoint);


	//attack
protected:
	Component * _target;
	int _attackpoint;

	int level;

public:
	int getattackpoint();
	Component * getTarget();
	void ResetTarget();


	void EquipWeapon(EquipItem equipItem);


	//defens

protected:
	int _attackedpoint;

public:
	void durabilityReduction();

public:
	int getattackedpoint() { return _attackedpoint; }

	//CoolDown
public:
	bool IsCoolDown();
	void ResetCoolDown();
	void UpdateAttackCoolDown(float deltaTime);

protected:
	float _attackCoolDownDuration;
	float _attackCoolDown;

private:
	void CoolTimeReduction(float time);
	int durability_weaponPoint;

public:
	void UpdateText();



	//UI
protected:
	//ID3DXFont * _dxTestFont;
	Font * _font;


public:
	void init(int tilex, int tiley);
	void initTilePostion(int tilex, int tiley);


	//pathfinding
protected:
	tileCell * _targetTileCell;
	std::stack<tileCell*> _pathTileCellStack;
public:
	tileCell * getTargetTileCell() { return _targetTileCell; }
	void SetTargetTileCell(tileCell * tilecell);


	std::stack<tileCell*> getPathTileCellStack() { return _pathTileCellStack; }
	void PushTileCell(tileCell * tilecell) { _pathTileCellStack.push(tilecell); }
	void ClearPathTileCellStack();
};