#pragma once
#include "State.h"
class Charcter;

//�����ൿ������ ����

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
