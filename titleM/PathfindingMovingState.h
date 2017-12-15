#pragma once
#include "State.h"
#include <stack>

class tileCell;
class Charcter;

class PathfindingMovingState : public State
{
public:
	PathfindingMovingState();
	~PathfindingMovingState();


private:
	float _movingDurtion;

public:

	void Init(Charcter * charcter);
	void Start();
	void Stop();
	void Update(float deltaTime);

private:
	std::stack<tileCell*> _pathtileCellStack;
	
};
