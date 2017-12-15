#pragma once
#include "State.h"
class Charcter;

class MoveState : public State
{
public:
	MoveState();
	~MoveState();


private:
	float _movingDurtion;

public:

	void Init(Charcter * charcter);
	void Start();
	void Stop();
	void Update(float deltaTime);
	

};
