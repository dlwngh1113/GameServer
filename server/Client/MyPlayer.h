#pragma once
#include "Player.h"

class MyPlayer : public Player
{
private:
	MyPlayer();

public:
	virtual ~MyPlayer();
	void Move(SDL_Keycode code);

	virtual void Move(int nX, int nY) override;
	void Init(int nId);

public:
	static MyPlayer* Create(int nId);
};
