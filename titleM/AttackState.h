#pragma once
#include <vector>
#include "State.h"
class Charcter;
class Sprite;


class AttackState:public State
{
public:
	AttackState();
	~AttackState();

public:

	void Init(Charcter * charcter);
	void Start();
	void Stop();
	void Update(float deltaTime);

	void Render();
	void Release();
	void Reset();

};
