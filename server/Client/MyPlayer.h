#pragma once
#include "Player.h"

class MyPlayer : public Player
{
public:
	explicit MyPlayer(int nx, int ny, int nWidth, int nHeight);
	virtual ~MyPlayer();
	void Move(SDL_Keycode code);
};
