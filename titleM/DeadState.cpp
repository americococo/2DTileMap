#include "DeadState.h"
#include "Sprite.h"
#include "Charcter.h"
DeadState::DeadState() {}
DeadState::~DeadState() {}


void DeadState::Init(Charcter * charcter) 
{
	State::Init(charcter);
}
void DeadState::Start() 
{
	State::Start();
	Statename = L"Dead";
}
void DeadState::Stop() 
{
	State::Stop();
}

void DeadState::Update(float deltaTime) 
{
	State::Update(deltaTime);
	if (eStateType::ET_NONE != _nextState)
	{
		_charcter->ChangeState(_nextState);
		return;
	}
}
void DeadState::Render() 
{
	State::Render();
}
void DeadState::Release() 
{
	State::Release();
}
void DeadState::Reset() 
{
	State::Reset();
}


void DeadState::CreateSprite()
{

	_spriteVector.clear();

	WCHAR textureFileName[256];
	WCHAR scriptFileName[256];

	wsprintf(textureFileName, L"%s.png", _charcter->GetTextureFileName().c_str());

	//left
	{
		wsprintf(scriptFileName, L"%s_Dead_Left.json", _charcter->GetScriptFileName().c_str());
		Sprite * _sprite = new Sprite(textureFileName, scriptFileName,1.5f);
		_sprite->Init();
		_spriteVector.push_back(_sprite);
	}

	//right
	{
		wsprintf(scriptFileName, L"%s_Dead_Right.json", _charcter->GetScriptFileName().c_str());
		Sprite * _sprite = new Sprite(textureFileName, scriptFileName,1.5f);
		_sprite->Init();
		_spriteVector.push_back(_sprite);
	}

	//up
	{
		wsprintf(scriptFileName, L"%s_Dead_Up.json", _charcter->GetScriptFileName().c_str());
		Sprite * _sprite = new Sprite(textureFileName, scriptFileName,1.5f);
		_sprite->Init();
		_spriteVector.push_back(_sprite);
	}

	//down
	{
		wsprintf(scriptFileName, L"%s_Dead_Down.json", _charcter->GetScriptFileName().c_str());
		Sprite * _sprite = new Sprite(textureFileName, scriptFileName,1.5f);
		_sprite->Init();
		_spriteVector.push_back(_sprite);
	}
}