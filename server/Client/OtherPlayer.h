#pragma once
#include "Player.h"

class OtherPlayer : public Player
{
private:
	OtherPlayer();
public:
	virtual ~OtherPlayer();
	void Init(int nId);

public:
	static OtherPlayer* Create(int nId);
};

