#include "State.h"
#include "Sprite.h"
#include "Charcter.h"
#include "GlobalType.h"

State::State() 
{
	
}

State::~State() 
{
	for (int i = 0; i < _spriteVector.size(); i++)
	{
	_spriteVector[i]->deInit();
	delete _spriteVector[i];
	}
	_spriteVector.clear();

}


void State::Init(Charcter * charcter)
{
	_charcter = charcter;
	CreateSprite();
}
void State::Start()
{
	_nextState = eStateType::ET_NONE;
	Statename = L"none";
}
void State::Stop()
{

}
void State::Update(float deltaTime)
{
	_spriteVector[(int)_charcter->getDirection()]->Update(deltaTime);
}
void State::Render()
{
	_spriteVector[(int)_charcter->getDirection()]->setPostition(_charcter->GetX(),_charcter->GetY());
	_spriteVector[(int)_charcter->getDirection()]->render();
}
void State::Release()
{
	for (int i = 0; i < _spriteVector.size(); i++)
	{
		_spriteVector[i]->Release();
	}
	_spriteVector.clear();
}
void State::Reset()
{
	for (int i = 0; i < _spriteVector.size(); i++)
	{
		_spriteVector[i]->Reset();
	}
	_spriteVector.clear();
}
void State::CreateSprite()
{
	_spriteVector.clear();

	WCHAR textureFileName[256];
	WCHAR scriptFileName[256];

	wsprintf(textureFileName, L"%s.png", _charcter->GetTextureFiFName().c_str());

	//left
	{
		wsprintf(scriptFileName, L"%s_Left.json", _charcter->GetScriptFileName().c_str());
		Sprite * _sprite = new Sprite(textureFileName, scriptFileName);
		_sprite->Init();
		_spriteVector.push_back(_sprite);
	}

	//right
	{
		wsprintf(scriptFileName, L"%s_Right.json", _charcter->GetScriptFileName().c_str());
		Sprite * _sprite = new Sprite(textureFileName, scriptFileName);
		_sprite->Init();
		_spriteVector.push_back(_sprite);
	}

	//up
	{
		wsprintf(scriptFileName, L"%s_Up.json", _charcter->GetScriptFileName().c_str());
		Sprite * _sprite = new Sprite(textureFileName, scriptFileName);
		_sprite->Init();
		_spriteVector.push_back(_sprite);
	}

	//down
	{
		wsprintf(scriptFileName, L"%s_Down.json", _charcter->GetScriptFileName().c_str());
		Sprite * _sprite = new Sprite(textureFileName, scriptFileName);
		_sprite->Init();
		_spriteVector.push_back(_sprite);
	}
}
void State::NextState(eStateType type)
{
	_nextState = type;
}