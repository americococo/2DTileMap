#pragma once
#include <vector>
#include <string>
class Charcter;
enum eStateType;

class Sprite;

class State
{
public:
	State();
	~State();

protected:
	Charcter * _charcter;
	std::vector<Sprite*> _spriteVector;
	eStateType _nextState;

	std::wstring Statename;
public:

	virtual void Init(Charcter * charcter);
	virtual void Start();
	virtual void Stop();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void Release();
	virtual void Reset();
	virtual void CreateSprite();
	void NextState(eStateType type);


	eStateType getState() { return _nextState; }

	std::wstring getStateName()
	{
		return Statename;
	}
};
