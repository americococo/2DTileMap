#pragma once
#include "State.h"
class Charcter;

class DeadState : public State
{
public:
	DeadState();
	~DeadState();

public:

	void Init(Charcter * charcter);
	void Start();
	void Stop();
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();
	void CreateSprite();
};
