#pragma once
#include "State.h"
class Charcter;

//다음행동을위한 상태

class IdleState:public State
{
public:
	IdleState();
	~IdleState();

public:

	void Init(Charcter * charcter);
	void Start();
	void Stop();
	void Update(float deltaTime);
};
