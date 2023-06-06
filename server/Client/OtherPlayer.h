#pragma once
#include "Player.h"

class OtherPlayer : public Player
{
public:
	explicit OtherPlayer(int nx, int ny, int nWidth, int nHeight);
	virtual ~OtherPlayer();
};

