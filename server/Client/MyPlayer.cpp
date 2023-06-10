#include "pch.h"
#include "MyPlayer.h"
#include "PacketSender.h"

MyPlayer::MyPlayer()
{
}

MyPlayer::~MyPlayer()
{
}

void MyPlayer::Move(SDL_Keycode code)
{
	PacketSender::GetInstance().SendMove(code - 79);
}

void MyPlayer::Move(int nDx, int nDy)
{
	Player::Move(nDx, nDy);
}

void MyPlayer::Init(int nId)
{
	m_nId = nId;
}

MyPlayer* MyPlayer::Create(int nId)
{
	MyPlayer* inst = new MyPlayer();
	inst->Init(nId);
	return inst;
}
