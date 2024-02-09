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
