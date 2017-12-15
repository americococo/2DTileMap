#pragma once
#include "State.h"
class Charcter;
class Sprite;

class DeffensState:public State 
{
public:
	DeffensState();
	~DeffensState();


public:

	void Init(Charcter * charcter);
	void Start();
	void Stop();
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();

};
